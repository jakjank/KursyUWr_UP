module fib_counter_tb();
	wire [31:0] out;
	reg clk;
	reg rst;
	
	reg [31:0] expected_f1, expected_f2, expected_out;	

	fib_counter fc(out, clk, rst);

	initial begin
		rst = 1;
		expected_f1 = 0;
		expected_f2 = 1;
		expected_out = 0;
		#25 rst = 0;
	end

	always begin
		#10 clk = 0;
		#10 clk = 1;
	end

	initial  $monitor("clk=%d out=%d", clk, out);

	always @(posedge clk) begin
		if (!rst) begin
			if (out !== expected_out) begin
				$display("ERROR: time=%d out=%d expected=%d",
						$time, out, expected_out);
				#5 $finish;
			end
			
			expected_out <= expected_f1 + expected_f2;
      expected_f1 <= expected_f2;
      expected_f2 <= expected_f1 + expected_f2;

			if(expected_out + expected_f2 < expected_out) begin
				$display("DONE");
				#5 $finish;
			end
		end
	end
endmodule


