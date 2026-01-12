// 32-bit Parallel Hardware Multiplier for FPGA
// Uses Modified Booth Encoding (Radix-4) for parallel multiplication
// This design balances area and speed using partial product generation

module multiplier_32bit (
    input wire clk,
    input wire rst,
    input wire start,
    input wire [31:0] a,
    input wire [31:0] b,
    output reg [63:0] product,
    output reg done
);

    // State machine
    localparam IDLE = 2'b00;
    localparam COMPUTE = 2'b01;
    localparam DONE = 2'b10;
    
    reg [1:0] state;
    reg [4:0] stage;
    
    // Booth encoding: process 2 bits at a time with overlap
    // For 32-bit operands, we need 17 partial products (0 to 32, step by 2)
    reg [63:0] partial_products [0:16];
    reg [63:0] accumulator;
    
    // Parallel partial product generation using Booth Radix-4
    integer i;
    reg [2:0] booth_bits;
    reg [32:0] multiplicand_ext;
    
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            state <= IDLE;
            done <= 1'b0;
            product <= 64'd0;
            stage <= 5'd0;
            accumulator <= 64'd0;
        end else begin
            case (state)
                IDLE: begin
                    done <= 1'b0;
                    if (start) begin
                        state <= COMPUTE;
                        stage <= 5'd0;
                        accumulator <= 64'd0;
                        
                        // Sign extend multiplicand
                        multiplicand_ext = {a[31], a};
                        
                        // Generate all 17 partial products in parallel
                        for (i = 0; i <= 16; i = i + 1) begin
                            if (i == 0)
                                booth_bits = {b[1], b[0], 1'b0};
                            else if (i == 16)
                                booth_bits = {1'b0, b[31], b[30]};
                            else
                                booth_bits = {b[2*i+1], b[2*i], b[2*i-1]};
                            
                            // Booth encoding logic
                            case (booth_bits)
                                3'b000, 3'b111: partial_products[i] = 64'd0;
                                3'b001, 3'b010: partial_products[i] = {{31{a[31]}}, multiplicand_ext} << (2*i);
                                3'b011: partial_products[i] = {{30{a[31]}}, multiplicand_ext, 1'b0} << (2*i);
                                3'b100: partial_products[i] = (~({{30{a[31]}}, multiplicand_ext, 1'b0}) + 1) << (2*i);
                                3'b101, 3'b110: partial_products[i] = (~({{31{a[31]}}, multiplicand_ext}) + 1) << (2*i);
                            endcase
                        end
                    end
                end
                
                COMPUTE: begin
                    // Parallel tree reduction of partial products
                    // Stage 1: Add pairs of partial products in parallel
                    if (stage == 5'd0) begin
                        accumulator <= partial_products[0] + partial_products[1] + 
                                      partial_products[2] + partial_products[3] +
                                      partial_products[4] + partial_products[5] +
                                      partial_products[6] + partial_products[7];
                        stage <= 5'd1;
                    end
                    // Stage 2: Add remaining partial products
                    else if (stage == 5'd1) begin
                        accumulator <= accumulator + partial_products[8] + 
                                      partial_products[9] + partial_products[10] +
                                      partial_products[11] + partial_products[12] +
                                      partial_products[13] + partial_products[14] +
                                      partial_products[15] + partial_products[16];
                        stage <= 5'd2;
                    end
                    // Stage 3: Output result
                    else begin
                        product <= accumulator;
                        done <= 1'b1;
                        state <= DONE;
                    end
                end
                
                DONE: begin
                    if (!start) begin
                        state <= IDLE;
                        done <= 1'b0;
                    end
                end
                
                default: state <= IDLE;
            endcase
        end
    end

endmodule


// Alternative: Dadda multiplier (optimal parallel reduction)
// Dadda tree minimizes stages and uses CSA (Carry-Save Adders) for speed
module multiplier_32bit_combinational (
    input wire [31:0] a,
    input wire [31:0] b,
    output wire [63:0] product
);

    // Generate partial products (32x32 = 32 partial products)
    wire [31:0] pp [0:31];
    
    genvar i, j;
    generate
        for (i = 0; i < 32; i = i + 1) begin : gen_pp_rows
            for (j = 0; j < 32; j = j + 1) begin : gen_pp_cols
                assign pp[i][j] = a[j] & b[i];
            end
        end
    endgenerate
    
    // Dadda reduction stages
    // Dadda sequence: 2, 3, 4, 6, 9, 13, 19, 28, 42...
    // For 32 rows, we need to reduce: 32 -> 28 -> 19 -> 13 -> 9 -> 6 -> 4 -> 3 -> 2
    
    // Stage 1: Reduce 32 rows to 28 (reduce columns with > 28 bits)
    wire [63:0] s1 [0:27];
    wire [63:0] c1 [0:3];
    
    // Helper wires for bit organization
    wire [63:0] pp_ext [0:31];
    generate
        for (i = 0; i < 32; i = i + 1) begin : extend_pp
            assign pp_ext[i] = {{32{1'b0}}, pp[i]} << i;
        end
    endgenerate
    
    // Stage 1: Use full adders and half adders to reduce to 28
    generate
        for (i = 0; i < 28; i = i + 1) begin : s1_pass
            assign s1[i] = pp_ext[i];
        end
    endgenerate
    
    // Full adder for reduction
    full_adder fa1_0 (.a(pp_ext[28][31:0]), .b(pp_ext[29][31:0]), .c(pp_ext[30][31:0]), 
                      .sum(c1[0][31:0]), .carry(c1[1][31:0]));
    assign c1[0][63:32] = pp_ext[28][63:32];
    assign c1[1][63:33] = pp_ext[29][63:33];
    
    assign c1[2] = pp_ext[31];
    assign c1[3] = 64'd0;
    
    // Stage 2: Reduce to 19 using CSA (Carry-Save Adders)
    wire [63:0] s2 [0:18];
    wire [63:0] c2 [0:9];
    
    csa_array #(.WIDTH(64), .NUM_INPUTS(32)) csa_stage2 (
        .in({s1[0], s1[1], s1[2], s1[3], s1[4], s1[5], s1[6], s1[7], s1[8], s1[9],
             s1[10], s1[11], s1[12], s1[13], s1[14], s1[15], s1[16], s1[17], s1[18], s1[19],
             s1[20], s1[21], s1[22], s1[23], s1[24], s1[25], s1[26], s1[27],
             c1[0], c1[1], c1[2], c1[3]}),
        .sum(s2[0]),
        .carry(c2[0])
    );
    
    // Continue reduction stages to 2 rows (sum and carry)
    // Final stage uses a fast carry-propagate adder
    wire [63:0] final_sum, final_carry;
    
    // Simplified: directly sum all for demonstration
    // In real implementation, continue CSA tree reduction
    assign final_sum = s1[0] + s1[1] + s1[2] + s1[3] + s1[4] + s1[5] + s1[6] + 
                       s1[7] + s1[8] + s1[9] + s1[10] + s1[11] + s1[12] + s1[13];
    assign final_carry = s1[14] + s1[15] + s1[16] + s1[17] + s1[18] + s1[19] + 
                         s1[20] + s1[21] + s1[22] + s1[23] + s1[24] + s1[25] + 
                         s1[26] + s1[27] + c1[0] + c1[1] + c1[2];
    
    // Final CPA (Carry-Propagate Adder) - can use Kogge-Stone for speed
    assign product = final_sum + final_carry;

endmodule


// Full Adder module
module full_adder #(parameter WIDTH = 32) (
    input wire [WIDTH-1:0] a,
    input wire [WIDTH-1:0] b,
    input wire [WIDTH-1:0] c,
    output wire [WIDTH-1:0] sum,
    output wire [WIDTH-1:0] carry
);
    assign sum = a ^ b ^ c;
    assign carry = ((a & b) | (b & c) | (a & c)) << 1;
endmodule


// Carry-Save Adder Array
module csa_array #(parameter WIDTH = 64, NUM_INPUTS = 32) (
    input wire [WIDTH*NUM_INPUTS-1:0] in,
    output wire [WIDTH-1:0] sum,
    output wire [WIDTH-1:0] carry
);
    // Simplified CSA - in practice, build proper tree
    wire [WIDTH-1:0] temp_s [0:NUM_INPUTS-1];
    wire [WIDTH-1:0] temp_c [0:NUM_INPUTS-1];
    
    genvar i;
    generate
        for (i = 0; i < NUM_INPUTS; i = i + 1) begin : unpack
            assign temp_s[i] = in[WIDTH*i +: WIDTH];
        end
    endgenerate
    
    // Tree reduction using full adders
    assign sum = temp_s[0] ^ temp_s[1] ^ temp_s[2];
    assign carry = ((temp_s[0] & temp_s[1]) | (temp_s[1] & temp_s[2]) | (temp_s[0] & temp_s[2])) << 1;
    
endmodule


// Testbench for verification
module tb_multiplier();
    reg clk, rst, start;
    reg [31:0] a, b;
    wire [63:0] product;
    wire done;
    
    // Instantiate the multiplier
    multiplier_32bit uut (
        .clk(clk),
        .rst(rst),
        .start(start),
        .a(a),
        .b(b),
        .product(product),
        .done(done)
    );
    
    // Clock generation
    initial clk = 0;
    always #5 clk = ~clk;
    
    // Test cases
    initial begin
        $dumpfile("multiplier.vcd");
        $dumpvars(0, tb_multiplier);
        
        // Initialize
        rst = 1;
        start = 0;
        a = 0;
        b = 0;
        #20 rst = 0;
        
        // Test 1: Simple multiplication
        #10 a = 32'd15; b = 32'd10; start = 1;
        #10 start = 0;
        wait(done);
        $display("Test 1: %d * %d = %d (Expected: 150)", a, b, product);
        
        // Test 2: Larger numbers
        #20 a = 32'd1000; b = 32'd2000; start = 1;
        #10 start = 0;
        wait(done);
        $display("Test 2: %d * %d = %d (Expected: 2000000)", a, b, product);
        
        // Test 3: Maximum value
        #20 a = 32'hFFFF; b = 32'hFFFF; start = 1;
        #10 start = 0;
        wait(done);
        $display("Test 3: %h * %h = %h", a, b, product);
        
        // Test 4: Negative numbers (signed)
        #20 a = 32'hFFFFFFFF; b = 32'd2; start = 1; // -1 * 2
        #10 start = 0;
        wait(done);
        $display("Test 4: -1 * 2 = %d (Expected: -2)", $signed(product));
        
        #50 $finish;
    end
    
endmodule
