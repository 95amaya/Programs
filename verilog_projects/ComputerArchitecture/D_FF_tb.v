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
    reg clk, Data;
    wire Q;
    integer i;
	
	// D Flip Flop Test
    Test T1(clk, Data, Q);

    initial begin
        clk = 0;
        Data = 1'b1;
        #5 $display(" D \t  CLK   |    Q");
        #5 $display(" %b \t   %b    |    %b", Data, clk, Q);
        Data = 1'b0;
        #5 $display(" %b \t   %b    |    %b", Data, clk, Q);
        #5 $display(" %b \t   %b    |    %b", Data, clk, Q);
        Data = 1'b1;
        #5 $display(" %b \t   %b    |    %b", Data, clk, Q);
    end
    
    always #5 clk = ~clk;
endmodule