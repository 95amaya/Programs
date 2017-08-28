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
    integer i;
    reg A,B, Cin;
    wire Sum, Carry;
    
    reg [7:0] AA, BB;
    wire [7:0] sum;
    
    // Full Adder Test Module
    //Test T1(Cin, A, B, Sum, Carry);
    // 4-bit ripple carry adder module
    //Test T1(Cin, AA, BB, sum, Carry);
    // 8-bit ripple carry adder module
    Test T1(Cin, AA, BB, sum, Carry);
        
    initial begin
        for(i = 0; i <= 5'h1F; i=i+1) begin
            {AA, BB, Cin} = $random;
            if(i % 10 == 0) begin
                $display("\nCin     A        B\t\t|\t\tSum   Cout");
            end
            #5 $display(" %b  %b %b\t\t%b\t%b", Cin, AA, BB, sum, Carry);
        end
    end

endmodule