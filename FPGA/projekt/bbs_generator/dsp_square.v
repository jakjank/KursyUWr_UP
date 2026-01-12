module square_pipe (
    input  wire        clk,
    input  wire        rst,
    input  wire        start,
    input  wire [127:0] a,
    output reg  [255:0] square,
    output reg         done
);

    reg [127:0] stage0_reg;
    reg         stage0_valid;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            stage0_reg   <= 128'd0;
            stage0_valid <= 1'b0;
        end else begin
            stage0_reg   <= a;
            stage0_valid <= start;
        end
    end

    wire [63:0] a_high = stage0_reg[127:64];
    wire [63:0] a_low  = stage0_reg[63:0];

    (* use_dsp = "yes" *) wire [127:0] p0 = a_low  * a_low;
    (* use_dsp = "yes" *) wire [127:0] p1 = a_low  * a_high;
    (* use_dsp = "yes" *) wire [127:0] p2 = a_high * a_high;

    wire [255:0] sum_mid = {64'd0, p1} + {64'd0, p1};
    wire [255:0] stage1_sum = ({p2, 128'd0}) + sum_mid + {128'd0, p0};

    reg [255:0] stage1_reg;
    reg         stage1_valid;

    always @(posedge clk or posedge rst) begin
        if (rst) begin
            stage1_reg   <= 256'd0;
            stage1_valid <= 1'b0;
            square       <= 256'd0;
            done         <= 1'b0;
        end else begin
            stage1_reg   <= stage1_sum;
            stage1_valid <= stage0_valid;
            square       <= stage1_reg;
            done         <= stage1_valid;
        end
    end

endmodule