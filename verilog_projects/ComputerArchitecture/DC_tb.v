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
    reg clk, rst;
    wire [3:0] Out;
    integer i;
	
	// 4-bit Down Counter
    Test T1(clk, rst, Out);

    initial begin
        clk = 0;
        rst = 1'b0;
        $display(" rst CLK  |  Out_Data");
        #5 $display("  %b   %b   |  %d", rst, clk, Out);
        rst = 1'b1;
        #5 $display("  %b   %b   |  %d", rst, clk, Out);
        
        for(i = 0; i <= 3'b111; i=i+1) begin
            #10 $display("  %b   %b   |  %d", rst, clk, Out);
        end
    end
    
    always #5 clk = ~clk;
endmodule