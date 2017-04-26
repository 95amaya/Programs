`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/20/2017 02:13:02 PM
// Design Name: 
// Module Name: Test_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Test_tb(); 
    reg [3:0] A, B;
    wire [7:0] Output;
    integer i;
	
	// 4-bit unsigned multiplier
    Test T1(A, B, Output);

    initial begin
        $display("  A \t  B    |    Output");
        for(i = 0; i <= 4'b1111; i=i+1) begin
            A = i;
            B = i;
            #5 $display("%b\t%b   |   %b", A, B, Output);
        end
    end
endmodule

