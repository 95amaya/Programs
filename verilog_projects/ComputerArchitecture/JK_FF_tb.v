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
    reg clk, J, K;
    wire Q;
    integer i;
	
	// JK Flip Flop Test
    Test T1(clk, J, K, Q);

    initial begin
        clk = 0;
        $display(" J K \t  CLK   |    Q");
        
        for(i = 0; i <= 3'b111; i=i+1) begin
            {J, K} = (i + 3'b010)/2;
            #5 $display(" %b %b \t   %b    |    %b", J, K, clk, Q);
        end
    end
    
    always #5 clk = ~clk;
endmodule