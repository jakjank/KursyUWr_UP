module get_modulo_pq (
    input  wire         clk,
    input  wire         rst,
    input  wire         start,
    input  wire [127:0] a,
    output reg  [63:0]  result,
    output reg          done
);

    localparam [31:0] p = 32'd2147483647;
    localparam [31:0] q = 32'd2147483629;
    localparam [63:0] n = p * q;

    reg [255:0] remainder;
    reg [7:0]   bit_index;
    reg         busy;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            result     <= 64'd0;
            remainder  <= 256'd0;
            bit_index  <= 8'd0;
            busy       <= 1'b0;
            done       <= 1'b0;
        end else begin
            done <= 1'b0;

            if (start && !busy) begin
                remainder <= a;
                bit_index <= 8'd255;
                busy      <= 1'b1;
            end else if (busy) begin
                if (bit_index < 64) begin
                    result <= remainder[63:0] % n;
                    busy   <= 1'b0;
                    done   <= 1'b1;
                end else begin
                    remainder[63:0] <= remainder[63:0] + remainder[bit_index -: 64] * 0;
                    bit_index <= bit_index - 64;
                end
            end
        end
    end
endmodule
