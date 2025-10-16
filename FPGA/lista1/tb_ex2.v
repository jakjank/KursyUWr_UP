module priority_encoder4_tb;
	reg [3:0] i;
	wire [1:0] q;
	wire v;

	priority_encoder4 pe4(q, v, i);

	initial begin
		i = 4'b0000;
		#5 i = 4'b0001;
		#5 i = 4'b0010;
		#5 i = 4'b0100;
		#5 i = 4'b1000;

		#5 i = 4'b0011;
		#5 i = 4'b0110;
		#5 i = 4'b1100;

		#5 i = 4'b0111;
		#5 i = 4'b1110;

		#5 i = 4'b1111;

		#5 i = 4'b1001;
		#5 i = 4'b1010;
		#5 i = 4'b0101;
		#5 i = 4'b1101;
		#5 i = 4'b1011;
		
		#5 $finish;
	end

	initial $monitor(
		"i=%b v=%d q=%b",
		i, v, q);
endmodule
