module myALU_tb();
    reg  [7:0] v1, v2;
    reg  [2:0] opc;
    wire [7:0] out;
    reg [7:0] expect;

    reg [7:0] mem [0:64];
    integer i = 0;
    integer test_num = 0;

    myALU dut(opc, v1, v2, out);

    initial begin
        $readmemh("./ex2_test_data.hex", mem);

        forever begin
            opc = mem[i][2:0];
            v1 = mem[i+1];
            v2 = mem[i+2];
            expect = mem[i+3];

            if (v1 == 8'hFF && v2 == 8'hFF && mem[i+2] == 8'hFF && expect == 8'hFF) begin
                $display("Done");
                $finish;
            end

            if (test_num == 10) begin
                $display("Done");
                $finish;
            end

            #1
            if (out !== expect) begin
                $display("Failed test %d: opc=%0d v1=%d v2=%d => out=%d (expect %d)", 
                          test_num, opc, v1, v2, out, expect);
            end else begin
                $display("Ok test %0d: opc=%0d v1=%h v2=%h => %h", 
                          test_num, opc, v1, v2, out);
            end

            test_num = test_num + 1;
            i = i + 4;
        end
        $finish;
    end
endmodule
