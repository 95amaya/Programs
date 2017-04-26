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
    reg [7:0] In;
    wire parity;
    
    // 8-bit parity checker 
    Test T1(In, parity);

    initial begin
        $display("  Input  |  Parity");     
        for(i = 0; i <= 8'hFF; i=i+1) begin
            In = i;
            #5 $display("%b\t%b", In, parity);
        end
    end
endmodule