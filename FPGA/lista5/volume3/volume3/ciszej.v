// ciszej.v

// This file was auto-generated as a prototype implementation of a module
// created in component editor.  It ties off all outputs to ground and
// ignores all inputs.  It needs to be edited to make it do something
// useful.
// 
// This file will not be automatically regenerated.  You should check it in
// to your version control system if you want to keep it.

`timescale 1 ps / 1 ps
module ciszej #(
		parameter BITS = 24
	) (
		output reg [BITS-1:0] source_data,            //       source.data
		input  wire        source_ready,           //             .ready
		output reg        source_valid,           //             .valid
		input  wire [BITS-1:0] sink_data,              //         sink.data
		output wire        sink_ready,             //             .ready
		input  wire        sink_valid,             //             .valid
		input  wire        clock_clk,              //        clock.clk
		output wire [7:0]  avalon_slave_readdata,  // avalon_slave.readdata
		input  wire        avalon_slave_write,     //             .write
		input  wire [7:0]  avalon_slave_writedata, //             .writedata
		input  wire        reset             //        reset.reset
	);

	reg [7:0] volume_down;
	
	always @(posedge clock_clk or posedge reset) begin
		if (reset) begin
			source_data <= 0;
			source_valid <= 1'b0;
			volume_down <= 8'b0;
		end else begin
			if (sink_valid && sink_ready) begin
				source_data <= $signed(sink_data) >>> volume_down;
				source_valid <= 1'b1;
			end else if (source_ready) begin
				source_valid <= 1'b0;
			end
			
			if (avalon_slave_write) begin
				volume_down <= avalon_slave_writedata;
			end
		end
	end
	
	assign sink_ready = source_ready || !source_valid;


	assign avalon_slave_readdata = volume_down;

endmodule
