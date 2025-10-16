module priority_encoder(output reg q, v, input i0, i1);
  always @(*) 
    case ({i0,i1})
      2'b00: begin
              q = 0;
              v = 0;
             end
      2'b01: begin
              q = 1;
              v = 1;
             end
      2'b10: begin
              q = 0;
              v = 1;
             end
      2'b11: begin
              q = 0;
              v = 1;
             end
    endcase
endmodule

module priority_encoder4(output reg [1:0] q, output reg v, input [3:0] i);
  wire w1, w2, w3, w4;
  priority_encoder pe0(.q(w1), .v(w2), .i0(i[0]), .i1(i[1]));
  priority_encoder pe1(.q(w3), .v(w4), .i0(i[2]), .i1(i[3]));
  
  always @(*) begin
    if (w4) begin
      q = {1'b1, w3};
      v = 1;
    end
    if (w2) begin
      q = {1'b0, w1};
      v = 1;
    end
    if ({w2, w4} == 2'b00) begin
      q = 2'b00;
      v = 0;
    end
  end
endmodule
