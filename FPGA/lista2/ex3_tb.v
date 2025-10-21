module myCRC32_tb();
    reg clk;
    reg rst;
    reg in;
    wire [31:0] crc;

    myCRC32 mod(clk, rst, in, crc);

    initial clk = 0;

    always  #1 clk = ~clk;

    reg [127:0] filename;
    integer fd;
    integer i;
    integer r;
    reg [7:0] byte;

    initial begin
        rst = 1;
        #2 rst = 0;

        if (!$value$plusargs("file=%s", filename)) begin
            $display("ERROR: no file=%s argument given!", filename);
            $finish;
        end

        fd = $fopen(filename, "rb");

        while (!$feof(fd)) begin
            r = $fread(byte, fd);
            for (i=0; i<8; i=i+1) begin
                in = byte[i];
                #2;
            end
        end

        $fclose(fd);

        for (i = 0; i < 32; i = i + 1) begin
            in = 0;
            #2;
        end

        $display("CRC32 wynosi: %h", crc);

        $finish;
    end
endmodule