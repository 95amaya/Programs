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
    wire AgtB, AltB, AeqB;
	
	// 4-bit comparator Test 
    Test T1(A, B, AgtB, AltB, AeqB);

    initial begin
        $display("  A \tB\t|\tAgtB   AltB   AeqB");
        A = 4'b1100;
        B = 4'b0011;
        #10 $display(" %b  %b\t\t %b\t\t%b\t\t%b",  A, B, AgtB, AltB, AeqB);
        A = 4'b0011;
        B = 4'b1100;
        #10 $display(" %b  %b\t\t %b\t\t%b\t\t%b",  A, B, AgtB, AltB, AeqB);
        A = 4'b1100;
        B = 4'b1100;
        #10 $display(" %b  %b\t\t %b\t\t%b\t\t%b",  A, B, AgtB, AltB, AeqB);
        A = 4'b1010;
        B = 4'b0101;
        #10 $display(" %b  %b\t\t %b\t\t%b\t\t%b",  A, B, AgtB, AltB, AeqB);
        B = 4'b1010;
        A = 4'b0101;
        #10 $display(" %b  %b\t\t %b\t\t%b\t\t%b",  A, B, AgtB, AltB, AeqB);
        A = 4'b0000;
        B = 4'b0000;
        #10 $display(" %b  %b\t\t %b\t\t%b\t\t%b",  A, B, AgtB, AltB, AeqB);
    end
endmodule