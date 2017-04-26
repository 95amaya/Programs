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
    
    reg [3:0] AA, BB;
    wire [3:0] sum;
    
    // Full Adder Test Module
    //Test T1(Cin, A, B, Sum, Carry);
    // 4-bit ripple carry adder module
    Test T1(Cin, AA, BB, sum, Carry);
        
    initial begin
    /* // Full Adder Test
        $display("Cin A B  |  Sum    Cout");
        for(i = 0; i <= 3'b111; i=i+1) begin
            {Cin, A, B} = i;
            #5 $display(" %b  %b %b\t\t %b\t\t%b", Cin, A, B, Sum, Carry);
        end
    */
            $display("Cin   A    B\t|\tSum   Cout");
            for(i = 0; i <= 9'h1FF; i=i+1) begin
                {AA[3:2], BB[3:2], AA[1:0], BB[1:0], Cin} = i;
                #5 $display(" %b  %b %b\t\t%b\t%b", Cin, AA, BB, sum, Carry);
            end
    end
    //always #10 clk <= ~clk;
    /*always #10 B <= ~B;
    always #20 A <= ~A;
    always #40 Cin <= ~Cin;
    always #10 $display(" %b  %b %b\t\t%b\t\t%b", Cin, A, B, Sum, Carry);*/
endmodule