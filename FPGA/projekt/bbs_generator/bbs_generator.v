module decode_7seg(
    input [3:0] in,
    output reg [6:0] seg
);
    always @(*) begin
        case (in)
            4'h0: seg = ~7'b0111111;
            4'h1: seg = ~7'b0000110;
            4'h2: seg = ~7'b1011011;
            4'h3: seg = ~7'b1001111;
            4'h4: seg = ~7'b1100110;
            4'h5: seg = ~7'b1101101;
            4'h6: seg = ~7'b1111101;
            4'h7: seg = ~7'b0000111;
            4'h8: seg = ~7'b1111111;
            4'h9: seg = ~7'b1101111;
            4'hA: seg = ~7'b1110111;
            4'hB: seg = ~7'b1111100;
            4'hC: seg = ~7'b1011000;
            4'hD: seg = ~7'b1011110;
            4'hE: seg = ~7'b1111001;
            4'hF: seg = ~7'b1110001;
            default: seg = 7'b0000000;
        endcase
    end
endmodule

module bbs_generator(
    input  wire CLOCK_50,
	 input wire res,
    output reg  [9:0] LEDR,
    output wire [6:0] HEX0,
    output wire [6:0] HEX1,
    output wire [6:0] HEX2,
    output wire [6:0] HEX3,
    output wire [6:0] HEX4,
    output wire [6:0] HEX5
);
	
    // ----------------- Display counter
    reg [47:0] counter;
    wire [6:0] hex_arr [5:0];
    assign HEX0 = hex_arr[0];
    assign HEX1 = hex_arr[1];
    assign HEX2 = hex_arr[2];
    assign HEX3 = hex_arr[3];
    assign HEX4 = hex_arr[4];
    assign HEX5 = hex_arr[5];

    genvar j;
    generate
      for (j = 0; j < 6; j = j+1) begin : displays
            decode_7seg dec (
                 .in(counter[j*4+3:j*4]),
                 .seg(hex_arr[j])
            );
      end
    endgenerate

	 // ----------------- Params
    reg  [63:0] x_reg;
    localparam [63:0] SEED = 64'd65537;

    reg start_square, start_mod;
    wire [255:0] square_out;
    wire square_done;
    wire [63:0] mod_out;
    wire mod_done;

    reg mod_lsb;

    reg [2:0] state;
    localparam IDLE         = 3'd0,
               START_SQUARE = 3'd1,
               WAIT_SQUARE  = 3'd2,
               START_MOD    = 3'd3,
               WAIT_MOD     = 3'd4,
               DONE         = 3'd5;
	 
    // ----------------- Instantiate squarer
    square_pipe sq_inst (
        .clk(CLOCK_50),
        .rst(rst),
        .start(start_square),
        .a(x_reg),
        .square(square_out),
        .done(square_done)
    );

    // ----------------- Instantiate modulo
    get_modulo_pq mod_inst (
        .clk(CLOCK_50),
        .rst(rst),
        .start(start_mod),
        .a(square_out),
        .result(mod_out),
        .done(mod_done)
    );

    always @(posedge CLOCK_50 or posedge rst) begin
        if (rst) begin
            state <= IDLE;
            x_reg <= SEED;
            start_square <= 0;
            start_mod <= 0;
            counter <= 0;
            mod_lsb <= 0;
        end else begin
            start_square <= 0;
            start_mod <= 0;

            case (state)
                IDLE: begin
                    x_reg <= SEED;
                    state <= START_SQUARE;
                end

                START_SQUARE: begin
                    start_square <= 1;
                    state <= WAIT_SQUARE;
                end

                WAIT_SQUARE: if (square_done)
                    state <= START_MOD;

                START_MOD: begin
                    start_mod <= 1;
                    state <= WAIT_MOD;
                end

                WAIT_MOD: if (mod_done) begin
                    mod_lsb <= mod_out[0];
                    state <= DONE;
                end

                DONE: begin
                    x_reg <= mod_out;
                    state <= START_SQUARE;

                    // Increment counter every new number
                    if (mod_lsb == 1'b0)
                        counter <= counter + 1;

                    LEDR[0] <= mod_lsb;
                    LEDR[1] <= ~mod_lsb;
                end
            endcase
        end
    end

endmodule