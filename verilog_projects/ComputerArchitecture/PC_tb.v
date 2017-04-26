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
    reg clk, rst, enable;
    reg [15:0] In;
    wire [15:0] Out;
    integer i;
	
	// 16-bit Program Counter
    Test T1(clk, rst, enable, In, Out);

    initial begin
        clk = 0;
        In = 16'h00FF;
        rst = 1'b0;
        enable = 1'b0;
        $display(" In_Data rst enable CLK  |  Out_Data");
        #5 $display("  %h    %b    %b     %b   |  %h", In, rst, enable, clk, Out);
        rst = 1'b1;
        enable = 1'b1;
        #5 $display("  %h    %b    %b     %b   |  %h", In, rst, enable, clk, Out);
        enable = 1'b0;
        #5 $display("  %h    %b    %b     %b   |  %h", In, rst, enable, clk, Out);
        #5 $display("  %h    %b    %b     %b   |  %h", In, rst, enable, clk, Out);
    end
    
    always #5 clk = ~clk;
endmodule

