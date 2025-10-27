module pwm_generator (
    input wire clk,       // system clock
    input wire [7:0] threshold, // 0-255
    output reg pwm_out
);
    reg [7:0] counter = 0;

    always @(posedge clk) begin
        counter <= counter + 1;
        pwm_out <= (counter < threshold) ? 1'b1 : 1'b0;
    end
endmodule

module LedWave1(
    input  wire CLOCK_50,
    output wire [9:0] LEDR
);
    reg [15:0] pwm_counter = 0;
    reg [23:0] wave_timer = 0;
    reg [3:0] wave_pos = 0;
    reg [7:0] brightness[9:0];
    integer i;
	 integer direction = 1;

    // PWM counter
    always @(posedge CLOCK_50) pwm_counter <= pwm_counter + 1;

    // Move wave
    always @(posedge CLOCK_50) begin
        wave_timer <= wave_timer + 1;
        if (wave_timer == 24'd6_000_000) begin
            wave_timer <= 0;
				if (wave_pos == 1) direction <= 1; // wave_pos == 0 didnt work?
            else if (wave_pos == 9) direction <= -1;
            wave_pos <= wave_pos + direction;
        end
    end

    // Calculate brightness for each LED
	 parameter MIN_BRIGHT = 8'd8;
    always @(*) begin
        for (i = 0; i < 10; i = i + 1) begin
            integer dist;
            dist = (i > wave_pos) ? (i - wave_pos) : (wave_pos - i);
				
            if (dist == 0)
					brightness[i] = 8'd255;
				else
					brightness[i] = MIN_BRIGHT + (255 >> dist);
        end
    end

    // PWM outputs
    genvar j;
    generate
        for (j = 0; j < 10; j = j + 1) begin : generate_block
            assign LEDR[j] = (pwm_counter[7:0] < brightness[j]) ? 1'b1 : 1'b0;
        end
    endgenerate

endmodule