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
    reg Cin;
    reg [63:0] A, B;
    wire Carry;
    wire [63:0] Sum;
    
    // 64-bit ripple carry adder module
    Test T1(Cin, A, B, Sum, Carry);
        
    initial begin
        Cin = 0;
//      A <= 64'h0000|0000|0000|0000
        A = 64'h0000000000000000;
        B = 64'hFFFFFFFFFFFFFFFF;
        $display("\n------------ Simulation Results ------------");
        $display("Cin %8s %16s %11s %11s %11s", "A", "B", "|", "Sum", "Cout");
        #5 $display(" %1b  %16h %16h\t\t%16h\t%1b", Cin, A, B, Sum, Carry);
        Cin = 1;
        #5 $display(" %1b  %16h %16h\t\t%16h\t%1b", Cin, A, B, Sum, Carry);
//      A <= 64'h0000|0000|0000|0000
        A = 64'h000000FF00000000;
        #5 $display(" %1b  %16h %16h\t\t%16h\t%1b", Cin, A, B, Sum, Carry);
//        for(i = 0; i <= 5'h1F; i=i+1) begin
//            {A, B, Cin} = $random;
//            if(i % 10 == 0) begin
//                $display("\nCin     A        B\t\t|\t\tSum   Cout");
//            end
//            #5 $display(" %b  %h %h\t\t%h\t%b", Cin, A, B, Sum, Carry);
//        end
    end

endmodule