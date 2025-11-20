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

    assign pulse = ~sig & sig_d;   // 1 clock-wide pulse
endmodule

module sumator1(
	input wire CLOCK_50,
	input wire [9:0] SW,
   input wire [3:0] KEY,
	output wire [9:0] LEDR,
   output wire [6:0] HEX0,
   output wire [6:0] HEX1,
   output wire [6:0] HEX2,
   output wire [6:0] HEX3,
   output wire [6:0] HEX4,
   output wire [6:0] HEX5);
	
	// input
	wire [3:0] KEY_sync;
	wire [3:0] KEY_posedge;

	genvar i;
	generate
		for (i = 0; i < 4; i = i+1) begin : keys
			sync2 u_sync(.clk(CLOCK_50), .d(KEY[i]), .q(KEY_sync[i]));
			edge_pos u_edge(.clk(CLOCK_50), .sig(KEY_sync[i]), .pulse(KEY_posedge[i]));
		end
	endgenerate
	
	wire [3:0] cur_digit;
	assign cur_digit = SW[3:0]; //add ignore 
	// input end
	
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
		for (j = 0; j < 6; j = j+1) begin : displays
			decode_7seg(cur_buff[j*4+3:j*4], hex_arr[j]);
		end
	endgenerate
	// output end
	
	// buffers
	reg [23:0] result;
	reg [23:0] result_prev_cycle;
	reg [23:0] result_prev_cycle_sub;
	wire [23:0] bcd_complement;
	wire [23:0] add_out;
	wire [23:0] sub_out;
	reg [1:0] op; // 0-no op, 1-add, 2-sub
	// buffers end
	
	// adder
	BCD_adder adder(1'b0, result, cur_buff, add_out);
	// adder end
	
	// substractor
	genvar k;
	generate
		 for(k = 0; k < 6; k = k+1) begin : comp
			  assign bcd_complement[k*4+3:k*4] = 4'd9 - cur_buff[k*4+3:k*4];
		 end
	endgenerate
	BCD_adder substractor(1'b1, result, bcd_complement, sub_out);
	// substractor end
	
	always @(posedge CLOCK_50) begin
		result_prev_cycle <= add_out;
		result_prev_cycle_sub <= sub_out;
		
		if(SW[9]) begin
			result  <= 24'd0;
			cur_buff <= 24'd0;
			op <= 2'b00; 
		end else begin
			if (KEY_posedge[0]) begin
				cur_buff <= {cur_buff[19:0], cur_digit};
			end else if (KEY_posedge[1]) begin
				if (SW[4])
					op <= 2'b01;
				else
					op <= 2'b10;
				case (op)
					2'b00 : begin
						result <= cur_buff;
						end
					2'b01 : begin
						result <= result_prev_cycle;
						end
					2'b10 : begin
						result <= result_prev_cycle_sub;
						end
					2'b11 : begin
						result <= cur_buff;
						end
				endcase
				cur_buff <= 24'd0;
			end else if (KEY_posedge[2]) begin
				case (op)
					2'b00 : begin
						cur_buff <= cur_buff;
						end
					2'b01 : begin
						cur_buff <= result_prev_cycle;
						end
					2'b10 : begin
						cur_buff <= result_prev_cycle_sub;
						end
					2'b11 : begin
						cur_buff <= cur_buff;
						end
				endcase
				result  <= 24'd0;
				op <= 2'b00;
			end
		end
	end
endmodule