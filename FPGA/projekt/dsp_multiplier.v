module dsp_multiplier #(
    parameter W = 32
)(
    input  wire           clk,
    input  wire           rst,
    input  wire           start,
    input  wire [W-1:0]   a,
    input  wire [W-1:0]   b,
    output reg  [2*W-1:0] product,
    output reg            done
);

    // Pipeline register
    reg [2*W-1:0] mul_pipe;

    // Force DSP usage
    (* multstyle = "dsp" *)
    wire [2*W-1:0] mul_comb = a * b;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            mul_pipe <= 0;
            product  <= 0;
            done     <= 0;
        end else begin
            mul_pipe <= mul_comb;   // DSP + pipeline register
            product  <= mul_pipe;   // second pipeline stage
            done     <= start;      // 2-cycle latency
        end
    end
endmodule