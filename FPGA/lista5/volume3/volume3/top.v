module top(
	input wire CLOCK_50,
	input wire [3:0] KEY,
	
	output wire        AUD_XCK,
    input  wire        AUD_ADCDAT,
    input  wire        AUD_ADCLRCK,
    input  wire        AUD_BCLK,
    output wire        AUD_DACDAT,
    input  wire        AUD_DACLRCK,

    // I2C pins
    inout  wire        FPGA_I2C_SDAT,
    output wire        FPGA_I2C_SCLK
);

	audio_sys sys(
		.clk_clk (CLOCK_50),
		.reset_reset_n (KEY[0]),
		.audio_clk_clk (AUD_XCK),
		.audio_ADCDAT (AUD_ADCDAT),
		.audio_ADCLRCK (AUD_ADCLRCK),
		.audio_BCLK (AUD_BCLK),
		.audio_DACDAT (AUD_DACDAT),
		.audio_DACLRCK (AUD_DACLRCK),
		.av_i2c_SDAT (FPGA_I2C_SDAT),
		.av_i2c_SCLK (FPGA_I2C_SCLK)
	);
	
endmodule

/*
set masters [get_service_paths master]
set master [lindex $masters 0]
open_service master $master
left:
master_write_8 $master 0x10 2
right:
master_write_8 $master 0x11 4

master_read_8 $master 0x10 1]
master_read_8 $master 0x11 1
close_service master $master
*/