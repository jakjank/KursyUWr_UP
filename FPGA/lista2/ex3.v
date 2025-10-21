module myCRC32(
    input  wire       clk,
    input  wire       rst,
    input  wire       in,        // bit wejściowy, MSB-first
    output reg [31:0] crc_out    // wynikowy CRC (negacja rejestru)
);
    reg [31:0] crc;
    wire fb = in ^ crc[31];      // sprzężenie zwrotne z MSB

    always @(posedge clk or posedge rst) begin
        if (rst)
            crc <= 32'hFFFFFFFF;  // rejestr zainicjalizowany jedynkami
        else begin
            crc[31] <= crc[30];
            crc[30] <= crc[29];
            crc[29] <= crc[28];
            crc[28] <= crc[27];
            crc[27] <= crc[26];
            crc[26] <= crc[25] ^ fb;
            crc[25] <= crc[24];
            crc[24] <= crc[23] ^ fb;
            crc[23] <= crc[22] ^ fb;
            crc[22] <= crc[21] ^ fb;
            crc[21] <= crc[20];
            crc[20] <= crc[19];
            crc[19] <= crc[18];
            crc[18] <= crc[17];
            crc[17] <= crc[16] ^ fb;
            crc[16] <= crc[15];
            crc[15] <= crc[14];
            crc[14] <= crc[13];
            crc[13] <= crc[12] ^ fb;
            crc[12] <= crc[11] ^ fb;
            crc[11] <= crc[10] ^ fb;
            crc[10] <= crc[9]  ^ fb;
            crc[9]  <= crc[8]  ^ fb;
            crc[8]  <= crc[7]  ^ fb;
            crc[7]  <= crc[6]  ^ fb;
            crc[6]  <= crc[5];
            crc[5]  <= crc[4]  ^ fb;
            crc[4]  <= crc[3]  ^ fb;
            crc[3]  <= crc[2];
            crc[2]  <= crc[1]  ^ fb;
            crc[1]  <= crc[0]  ^ fb;
            crc[0]  <= fb;
        end
    end

    always @(posedge clk or posedge rst) begin
        if (rst)
            crc_out <= 32'h00000000; // negacja 0xFFFFFFFF
        else
            crc_out <= ~crc;         // wynik = negacja rejestru
    end
endmodule
