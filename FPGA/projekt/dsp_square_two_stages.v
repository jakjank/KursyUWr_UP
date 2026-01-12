module square_pipe (
    input  wire         clk,
    input  wire         rst,
    input  wire         start,
    input  wire [127:0] a,
    output reg  [255:0] square,
    output reg          done
);

    // Stage 1
    reg [127:0] stage1_reg;
    reg         stage1_valid;

    // Stage 2
    reg [255:0] stage2_reg;
    reg         stage2_valid;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            stage1_reg   <= 0;
            stage1_valid <= 0;
            stage2_reg   <= 0;
            stage2_valid <= 0;
            square       <= 0;
            done         <= 0;
        end else begin
            // Stage 1
            stage1_reg   <= a;
            stage1_valid <= start;

            // Stage 2
            stage2_reg   <= stage1_reg * stage1_reg;
            stage2_valid <= stage1_valid;

            // Outputs aligned with stage 2
            square <= stage2_reg;
            done   <= stage2_valid;
        end
    end

endmodule

`timescale 1ns/1ps

module tb_square_pipe();

    reg clk, rst, start;
    reg [127:0] a;
    wire [255:0] square;
    wire done;

    square_pipe uut (
        .clk(clk),
        .rst(rst),
        .start(start),
        .a(a),
        .square(square),
        .done(done)
    );

    // Clock
    initial clk = 0;
    always #5 clk = ~clk;

    initial begin
        $dumpfile("square_pipe.vcd");
        $dumpvars(0, tb_square_pipe);

        rst = 1; start = 0; a = 0;
        #20 rst = 0;

        // Test 1
        a = 128'd3; start = 1; #10; start = 0;
        wait(done); #10;
        $display("Test 1: a=%d, a^2=%d", a, square);

        // Test 2
        a = 128'd12345; start = 1; #10; start = 0;
        wait(done); #10;
        $display("Test 2: a=%d, a^2=%d", a, square);

        // Test 3
        a = 128'h123456789ABCDEF0123456789ABCDEF0;
        start = 1; #10; start = 0;
        wait(done); #10;
        $display("Test 3: a=%h, a^2=%h", a, square);

        // wolfram alpha approves
        #50 $finish;
    end

endmodule
