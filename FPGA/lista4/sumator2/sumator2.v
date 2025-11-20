module decode_7seg(
	input [3:0] in,
   output reg [6:0] seg);

 always @(*) begin
    case (in)
      4'h0: seg = ~7'b0111111;
      4'h1: seg = ~7'b0000110;
      4'h2: seg = ~7'b1011011;
      4'h3: seg = ~7'b1001111;
      4'h4: seg = ~7'b1100110;
      4'h5: seg = ~7'b1101101;
      4'h6: seg = ~7'b1111101;
      4'h7: seg = ~7'b0000111;
      4'h8: seg = ~7'b1111111;
      4'h9: seg = ~7'b1101111;
      4'hA: seg = ~7'b1110111;
      4'hB: seg = ~7'b1111100;
      4'hC: seg = ~7'b1011000;
      4'hD: seg = ~7'b1011110;
      4'hE: seg = ~7'b1111001;
      4'hF: seg = ~7'b1110001;
      default: seg = 7'b0000000;
    endcase
  end
endmodule

module BCD_digit(
	input wire carry_in,
	input wire [3:0] a,
	input wire [3:0] b,
	output reg [3:0] out,
	output reg carry_out);
	
	reg [4:0] sum;
	always @(*) begin
		sum = a + b + carry_in;
		
		if(sum > 9) begin
			sum = sum + 6;
			carry_out = 1;
		end else begin
			carry_out = 0;
		end
		
		out  = sum[3:0];
	end
endmodule 

module BCD_adder(
	input  wire carry_in,
   input  wire [23:0] a,
   input  wire [23:0] b,
   output wire [23:0] out);
	
	wire [6:0] c;
	assign c[0] = carry_in;
	
	genvar i;
   generate
		for(i=0; i<6; i=i+1) begin : digits
			BCD_digit d(
				c[i],
            a[i*4+3:i*4],
            b[i*4+3:i*4],
            out[i*4+3:i*4],
            c[i+1]
           );
	end
	endgenerate
	
	assign carry_out = c[6];
	
endmodule

module sync2(
    input  wire clk,
    input  wire d,
    output reg  q
);
    reg q1;
    always @(posedge clk) begin
        q1 <= d;
        q  <= q1;
    end
endmodule

module edge_pos(
    input  wire clk,
    input  wire sig,
    output wire pulse
);
    reg sig_d;

    always @(posedge clk)
        sig_d <= sig;

    assign pulse = ~sig & sig_d;
endmodule	 

module sumator2(
    input wire CLOCK_50,
    input wire [9:0] SW,
    input wire [3:0] KEY,
    output wire [9:0] LEDR,
    output wire [6:0] HEX0,
    output wire [6:0] HEX1,
    output wire [6:0] HEX2,
    output wire [6:0] HEX3,
    output wire [6:0] HEX4,
    output wire [6:0] HEX5
);

    // input
    wire [3:0] KEY_sync;
    wire [3:0] KEY_posedge;
    genvar gi;
    generate
        for (gi = 0; gi < 4; gi = gi + 1) begin : KSYNC
            sync2 u_sync(.clk(CLOCK_50), .d(KEY[gi]), .q(KEY_sync[gi]));
            edge_pos u_edge(.clk(CLOCK_50), .sig(KEY_sync[gi]), .pulse(KEY_posedge[gi]));
        end
    endgenerate

    wire [3:0] cur_digit = SW[3:0];

    // output
    reg [23:0] cur_buff;
    wire [6:0] hex_arr[5:0];
    assign HEX0 = hex_arr[0];
    assign HEX1 = hex_arr[1];
    assign HEX2 = hex_arr[2];
    assign HEX3 = hex_arr[3];
    assign HEX4 = hex_arr[4];
    assign HEX5 = hex_arr[5];

    genvar j;
    generate
        for (j = 0; j < 6; j = j + 1) begin : displays
            decode_7seg u_dec(.in(cur_buff[j*4 +: 4]), .seg(hex_arr[j]));
        end
    endgenerate

    // buffers
    reg [23:0] result;
    wire [23:0] add_out;
    reg  [23:0] adder_b;
    reg  [1:0] op;
    // MULTIPLY buffers:
    reg [19:0] mult_counter;
    reg [23:0] multiplicand_bcd;
    reg mul_busy;
    reg mul_show_result;

    BCD_adder adder(1'b0, result, adder_b, add_out);

    // 9 complement
    wire [23:0] bcd_complement;
    genvar k;
    generate
        for (k = 0; k < 6; k = k + 1) begin : comp
            assign bcd_complement[k*4 +: 4] = 4'd9 - cur_buff[k*4 +: 4];
        end
    endgenerate
    wire [23:0] sub_out;
    BCD_adder sub_adder(1'b1, result, bcd_complement, sub_out);

    // BCD -> integer 
    function [19:0] bcd_to_int;
        input [23:0] b;
        reg [3:0] d0, d1, d2, d3, d4, d5;
        begin
            d0 = b[ 3: 0];
            d1 = b[ 7: 4];
            d2 = b[11: 8];
            d3 = b[15:12];
            d4 = b[19:16];
            d5 = b[23:20];
            bcd_to_int = d0 + d1*10 + d2*100 + d3*1000 + d4*10000 + d5*100000;
        end
    endfunction

    always @(posedge CLOCK_50) begin
        if (!mul_busy) adder_b <= cur_buff;

        if (mul_busy) begin
            result <= add_out;
				if (mult_counter > 0) begin
                mult_counter <= mult_counter - 1;
            end
            if (mult_counter == 0) begin
                mul_busy <= 1'b0;
                if (mul_show_result) begin
                    cur_buff <= result;
                    mul_show_result <= 1'b0;
                end
            end
        end else begin
            // normal non-mul behavior
            if (SW[9]) begin
                // reset
                result   <= 24'd0;
                cur_buff <= 24'd0;
                op       <= 2'b00;
                mul_busy <= 1'b0;
                mult_counter <= 20'd0;
                multiplicand_bcd <= 24'd0;
                adder_b <= 24'd0;
            end else begin
                if (KEY_posedge[0]) begin
                    if (cur_digit <= 4'd9) cur_buff <= { cur_buff[19:0], cur_digit };
                end
                if (KEY_posedge[1]) begin
                    case (SW[5:4])
                        2'b00: op <= 2'b10; // -
                        2'b01: op <= 2'b01; // +
                        2'b10: op <= 2'b11; // *
                        default: op <= 2'b00;
                    endcase

                    case (op)
                        2'b00: begin
                            result <= cur_buff;
                        end
                        2'b01: begin
                            result <= add_out;
                        end
                        2'b10: begin
                            result <= sub_out;
                        end
                        2'b11: begin
                            multiplicand_bcd <= result;
                            mult_counter <= bcd_to_int(cur_buff);
                            adder_b <= result;
                            result <= 24'd0;
                            mul_busy <= 1'b1;
                            mul_show_result <= 1'b0;
                        end
                    endcase

                    cur_buff <= 24'd0;
                end

                if (KEY_posedge[2]) begin
                    case (op)
                        2'b00: begin
                        end
                        2'b01: begin
                            result <= add_out;
                            cur_buff <= add_out;
                        end
                        2'b10: begin
                            result <= sub_out;
                            cur_buff <= sub_out;
                        end
                        2'b11: begin
                            multiplicand_bcd <= result;
                            mult_counter <= bcd_to_int(cur_buff);
                            adder_b <= result;
                            result <= 24'd0;
                            mul_busy <= 1'b1;
                            mul_show_result <= 1'b1;
                        end
                    endcase
                    op <= 2'b00;
                end
            end
        end
    end
endmodule
