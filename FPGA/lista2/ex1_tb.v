module print_7seg_tb();
	reg [3:0] in;
	wire [7:0] out;	
	decode_7seg decoder(in, out);

	integer i;

	initial begin
		for (i = 0; i < 16; i = i + 1) begin
			$display("i = %d", i);
			in = i;
			#5 ;
		end
		$finish;
	end
endmodule
