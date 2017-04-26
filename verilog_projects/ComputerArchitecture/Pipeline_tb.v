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
    reg[15:0] code;
    reg[31:0] A, B;
    wire parity;
   	
	// 3-Stage Pipeline Test
    Test T1(clk, rst, code, A, B, parity);

    initial begin
        {clk, rst, code, A, B} = 0;
        
        $display(" rst CLK code    A        B      |  Parity ");
        #10 $display("  %b   %b  %h %h %h  |  %b (reset low)", rst, clk, code, A, B, parity);
        rst = 1'b1; // Reset -> Fetch Stage
        A = 32'h00000002;
        B = 32'h00000002;
        code = 16'h0004; // Code = ADD
        #5 $display("  %b   %b  %h %h %h  |  %b (reset high)", rst, clk, code, A, B, parity);
        #5 $display("  %b   %b  %h %h %h  |  %b (Fetch Stage)", rst, clk, code, A, B, parity);
        #10 $display("  %b   %b  %h %h %h  |  %b (Execute Stage)", rst, clk, code, A, B, parity);
        #10 $display("  %b   %b  %h %h %h  |  %b (Parity Stage)", rst, clk, code, A, B, parity);
    end
    
    always #5 clk = ~clk;
endmodule

