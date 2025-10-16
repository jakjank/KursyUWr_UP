module fib_counter(output reg [31:0] out, input clk, rst);
	reg [31:0] f1;
	reg [31:0] f2;
	
	always @(posedge clk or posedge  rst)
		begin
			if (rst) begin
				f1 <= 0;
				f2 <= 1;
				out <= 0;
			end
			else begin
				out <= f1 + f2;
				f1 <= f2;
				f2 <= f1 + f2;
			end
		end
endmodule
	
