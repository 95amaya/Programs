`timescale 1ns / 1ps

`define MASK1 64'h00000000000000FF
`define MASK2 64'h000000FF00000000

module Test_tb(); 
//    reg [31:0] A, B; 
//    wire [63:0] Output;
    reg [63:0] A, B; //63
    wire [127:0] Output; //127
    integer i;
	
	// 16-64-bit unsigned multiplier
    Test T1(A, B, Output);

    initial begin
        $display(" %2s %14s    |   %10s", "A", "B", "Output");
        for(i = 0; i <= 4'b1111; i=i+1) begin
            A = `MASK1 & $random;
            case(i%2)
                1'b0: B = `MASK1 & $random;
                1'b1: B = `MASK2 & $random;
                default: B = `MASK1 & $random;
            endcase
            
            #5 $display(" %3d %14d   |   %10d", A, B, Output);
        end
    end
endmodule

