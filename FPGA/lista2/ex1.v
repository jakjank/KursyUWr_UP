module decode_7seg(input [3:0] in, output reg [7:0] seg);
	task print_7seg(input [7:0] s);
		reg A,B,C,D,E,F,G,DP;
    begin
      A = s[0];
      B = s[1];
      C = s[2];
      D = s[3];
      E = s[4];
      F = s[5];
      G = s[6];
      DP = s[7];
      $display(" %s ", (A ? "___" : "   "));
      $display("%s   %s", (F ? "|" : " "), (B ? "|" : " "));
      $display("%s   %s", (F ? "|" : " "), (B ? "|" : " "));
      $display(" %s ", (G ? "___" : "   "));
      $display("%s   %s", (E ? "|" : " "), (C ? "|" : " "));
      $display("%s   %s", (E ? "|" : " "), (C ? "|" : " "));
      $display(" %s  %s", (D ? "___" : "   "), (DP ? "." : " "));
      $display("");
    end
endtask

 always @(*) begin
    case (in)
      4'h0: seg = 8'b00111111;
      4'h1: seg = 8'b00000110;
      4'h2: seg = 8'b01011011;
      4'h3: seg = 8'b01001111;
      4'h4: seg = 8'b01100110;
      4'h5: seg = 8'b01101101;
      4'h6: seg = 8'b01111101;
      4'h7: seg = 8'b00000111;
      4'h8: seg = 8'b01111111;
      4'h9: seg = 8'b01101111;
      4'hA: seg = 8'b11110111;
      4'hB: seg = 8'b11111100;
      4'hC: seg = 8'b11011000;
      4'hD: seg = 8'b11011110;
      4'hE: seg = 8'b11111001;
      4'hF: seg = 8'b11110001;
      default: seg = 8'b00000000;
    endcase
    print_7seg(seg);
  end
	
endmodule

