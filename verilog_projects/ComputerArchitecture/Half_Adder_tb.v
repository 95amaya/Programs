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
    reg clk; 
    reg A,B;
    wire Sum, Carry;

    Test T1(A, B, Sum, Carry);
    
    initial begin
        clk = 0;
        A = 0;
        B = 0;
        //$display("The value of in  is: %b", );
        $display(" A B  |  Sum   Carry");
        //$write ("The value of Select is: %b", Select) ;
        #20
        $display(" %b %b\t  %b\t\t%b", A, B, Sum, Carry);
        B = 1;
        #20
        $display(" %b %b\t  %b\t\t%b", A, B, Sum, Carry);
        //$display("  %b\t\t%b", Select, Out);
        B = 0;
        A = 1;
        #20
        $display(" %b %b\t  %b\t\t%b", A, B, Sum, Carry);
        //$display("  %b\t\t%b", Select, Out);
        B = 1;
        #20
        $display(" %b %b\t  %b\t\t%b", A, B, Sum, Carry);
        //$display("  %b\t\t%b", Select, Out);
    end
    
    always #10 clk <= ~clk;
endmodule

