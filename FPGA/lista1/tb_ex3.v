module tb_bit_counter();
	wire [15:0] out;
	reg zero;
	reg dir;
	reg clk;

	bit_counter bc(clk, dir, zero, out);

	always begin
		#1 clk = 0;
		#1 clk = 1;
	end

	initial $monitor($time, 
		" clk=%d zero=%d dir=%d out=%d",
		clk, zero, dir, out);

	initial begin
		zero = 1;
		#3
		zero = 0;
		dir = 0;

		#10 dir = 1;

		#20 dir = 0;

		#16 zero = 1;
		#2 zero = 0;

		#4 $finish;
	end
endmodule
