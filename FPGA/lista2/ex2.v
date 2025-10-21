module myALU(input [2:0] opc, input [7:0] v1, v2, output reg [7:0] out);
    always @(*) begin
        case (opc)
            3'd0: out = v1 + v2;
            3'd1: out = v1 - v2;
            3'd2: out = v1 & v2;
            3'd3: out = v1 | v2;
            3'd4: out = ~(v1 + v2);
            3'd5: out = ~(v1 - v2);
            3'd6: out = ~(v1 & v2);
            3'd7: out = ~(v1 | v2);
        endcase
    end
endmodule
