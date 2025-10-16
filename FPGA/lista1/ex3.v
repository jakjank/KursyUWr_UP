module bit_counter(input clk, dir, zero, output reg [15:0] out);
  always @(posedge clk)
    begin
      if (zero)
        out <= 0;
      else if (dir)
      	out <= out - 1;
      else
        out <= out + 1;
    end
endmodule