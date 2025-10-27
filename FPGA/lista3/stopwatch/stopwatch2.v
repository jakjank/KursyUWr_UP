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
      default: seg = ~7'b0000000;
    endcase
  end
endmodule

module tick_generator(
	input wire clk,
	output reg tick);
	
	reg [20:0] count = 0;
	
	always @(posedge clk) begin
		if(count == 21'd499999) begin
			count <= 0;
			tick <= 1;
		end else begin
			count <= count + 1;
			tick <= 0;
		end
	end
endmodule

module stopwatch2(
	input  wire CLOCK_50,
   input  wire [0:0] SW,
   input  wire [0:0] KEY,
   output wire [6:0] HEX0,
   output wire [6:0] HEX1,
   output wire [6:0] HEX2,
   output wire [6:0] HEX3,
   output wire [6:0] HEX4,
   output wire [6:0] HEX5);
	
	reg [3:0] min_tens, min_ones, sec_tens, sec_ones, hun_tens, hun_ones;
	wire tick10ms;
	
	decode_7seg(hun_ones, HEX0);
	decode_7seg(hun_tens, HEX1);
	decode_7seg(sec_ones, HEX2);
	decode_7seg(sec_tens, HEX3);
	decode_7seg(min_ones, HEX4);
	decode_7seg(min_tens, HEX5);
	
	tick_generator(CLOCK_50, tick10ms); 
	
	always @(posedge tick10ms) begin 
		if(!KEY[0]) begin
			min_tens <= 0;
			min_ones <= 0;
			sec_tens <= 0;
			sec_ones <= 0;
			hun_tens <= 0;
			hun_ones <= 0;
		end
		else if (SW[0] && tick10ms) begin
			if (hun_ones == 9) begin
             hun_ones <= 0;
                if (hun_tens == 9) begin
                    hun_tens <= 0;
                    if (sec_ones == 9) begin
                        sec_ones <= 0;
                        if (sec_tens == 5) begin
                            sec_tens <= 0;
                            if (min_ones == 9) begin
                                min_ones <= 0;
                                if (min_tens == 9)
                                    min_tens <= 0;
                                else
                                    min_tens <= min_tens + 1;
                            end else min_ones <= min_ones + 1;
                        end else sec_tens <= sec_tens + 1;
                    end else sec_ones <= sec_ones + 1;
                end else hun_tens <= hun_tens + 1;
            end else hun_ones <= hun_ones + 1;
		end
	end
endmodule