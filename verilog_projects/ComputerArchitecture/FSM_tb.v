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
    reg clk, rst, in;
    wire out;
   	
	// FSM Test
    Test T1(clk, rst, in, out);

    initial begin
        {clk, rst, in} = 0;
        
        $display(" rst CLK  X  |  Y ");
        #5 $display("  %b   %b   %b  |  %b (reset low)", rst, clk, in, out);
        rst = 1'b1;
        #5 $display("  %b   %b   %b  |  %b (reset high -> state 0)", rst, clk, in, out);
        in = 1'b0; // Stay in S2 output 0
        #10 $display("  %b   %b   %b  |  %b (stay in state2 output 0)", rst, clk, in, out);
        in = 1'b1; // Go to S1 output 0
        #10 $display("  %b   %b   %b  |  %b (state2 -> state1 output 0)", rst, clk, in, out);
        // Stay in S1 output 1
        #10 $display("  %b   %b   %b  |  %b (stay in state1 output 1)", rst, clk, in, out);
        in = 1'b0; // Go to S2 output 1
        #10 $display("  %b   %b   %b  |  %b (state1 -> state2 output 1)", rst, clk, in, out);
    end
    
    always #5 clk = ~clk;
endmodule

