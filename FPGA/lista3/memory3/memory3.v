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

// :((
module read_keys(
	input wire clk,
	input wire [3:0] physical,
	output reg [3:0] logical);
	
	reg [22:0] counter;
	integer i;

	always @(posedge clk) begin
		counter <= counter + 1;
		for(i = 0; i < 4; i = i+1) begin
			if(counter == 0)
				logical[i] <= physical[i];
		   else 
				logical[i] <= 1'b1;
		end
	end
endmodule

module memory(
	input wire clk,
	input wire [9:0] addr,
	input wire option,
	input wire [7:0] val_in,
	output reg [7:0] val_out);
	
	reg [7:0] mem [0:1023];
	
	always @(posedge clk) begin
		case(option)
			1'b0: val_out <= mem[addr];
			1'b1: begin
				mem[addr] <= val_in;
				val_out <= mem[addr];
			end
		endcase
	end
endmodule

module memory3(
	input wire CLOCK_50,
	input wire [9:0] SW,
   input wire [3:0] KEY,
	output reg [9:0] LEDR,
   output wire [6:0] HEX0,
   output wire [6:0] HEX1,
   output wire [6:0] HEX2,
   output wire [6:0] HEX3,
   output wire [6:0] HEX4,
   output wire [6:0] HEX5);
	
	
	reg [9:0] cur_addr;
	reg option;
	wire [3:0] keys;
	wire [7:0] mem_val;
	wire [7:0] val_in;
	
	assign val_in = SW[7:0];
	
	// print address
	decode_7seg(cur_addr[3:0], HEX0);
	decode_7seg(cur_addr[7:4], HEX1);
	
	// show switches
	decode_7seg(SW[7:4], HEX5);
	decode_7seg(SW[3:0], HEX4);
	
	// show mem value
	decode_7seg(mem_val[7:4], HEX3);
	decode_7seg(mem_val[3:0], HEX2);
	
	// read buttons
	read_keys(CLOCK_50, KEY, keys);
	
	// mem read/write
	memory(CLOCK_50, cur_addr, option, val_in, mem_val);
	
	always @(posedge CLOCK_50) begin
		option <= 0;
		LEDR[9:8] <= cur_addr[9:8];
		if (~keys[0]) begin
			cur_addr <= cur_addr + 1;
		end
		else if (~keys[1]) begin
			cur_addr <= cur_addr - 1;
		end
		else if (~keys[2]) begin
			cur_addr <= SW;
		end
		else if (~keys[3]) begin
			option <= 1;
		end
		
		LEDR[7:0] <= mem_val;
	end
	
endmodule
	
	
