module jk_latch_tb;
	reg j, k, clk;
  wire q;

	jk_latch l1(q,j,k,clk);
	
	initial begin
    clk = 0;
    forever #5 clk = ~clk;  // 10ns clock period
  end

	initial begin
		j = 0;
		k = 0;
		# 10;

		j = 0;
		k = 1;
		# 10;

		j = 1;
		k = 0;
		# 10;

		j = 0;
		k = 0;
		# 10;

		j = 1;
		k = 1;
		# 40;

		$finish;
	end

	initial $monitor($time, 
		" clk=%d j=%d k=%d q=%d",
		clk, j, k, q);
endmodule 
