module get_modulo_pq (
    input  wire         clk,
    input  wire         rst,
    input  wire         start,
    input  wire [255:0] a,
    output reg  [63:0]  result,
    output reg          done
);

    // Blum-Blum-Shub parameters
    localparam [31:0] p = 32'd2147483647;
    localparam [31:0] q = 32'd2147483629;
    localparam [63:0] n = p * q;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            result <= 64'd0;
            done   <= 1'b0;
        end else begin
            done <= 1'b0;

            if (start) begin
                result <= a % n;  // modulo reduction
                done   <= 1'b1;
            end
        end
    end

endmodule

`timescale 1ns/1ps

module tb_get_modulo_pq;

    reg         clk;
    reg         rst;
    reg         start;
    reg [255:0] a;
    wire [63:0] result;
    wire        done;

    // DUT
    get_modulo_pq dut (
        .clk(clk),
        .rst(rst),
        .start(start),
        .a(a),
        .result(result),
        .done(done)
    );

    // Clock: 100 MHz
    initial clk = 0;
    always #5 clk = ~clk;

    // Reference parameters (same as DUT)
    localparam [31:0] p = 32'd2147483647;
    localparam [31:0] q = 32'd2147483629;
    localparam [63:0] n = p * q;

    // Reference calculation
    reg [255:0] ref_a;
    reg [63:0]  ref_mod;

    task run_test(input [255:0] value);
        begin
            ref_a   = value;
            ref_mod = value % n;

            @(posedge clk);
            a     <= value;
            start <= 1'b1;

            @(posedge clk);
            start <= 1'b0;

            wait(done);

            if (result !== ref_mod) begin
                $display("❌ FAIL: a = %h", ref_a);
                $display("   Expected = %h", ref_mod);
                $display("   Got      = %h", result);
            end else begin
                $display("✅ PASS: a = %h, mod n = %h", ref_a, result);
            end

            @(posedge clk);
        end
    endtask

    initial begin
        $dumpfile("get_modulo_pq.vcd");
        $dumpvars(0, tb_get_modulo_pq);

        // Reset
        rst   = 1;
        start = 0;
        a     = 0;

        repeat (2) @(posedge clk);
        rst = 0;

        // ----------------------------
        // Test cases
        // ----------------------------

        // Small value
        run_test(256'd3);

        // Medium value
        run_test(256'd12345);

        // Exactly n
        run_test(n);

        // n + 1
        run_test(n + 1);

        // Large random-looking value
        run_test(256'h123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0);

        // All ones
        run_test({256{1'b1}});

        $display("All tests completed.");
        #50;
        $finish;
    end

endmodule
