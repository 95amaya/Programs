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
    reg [2:0] In;
    wire [7:0] Out;
	
	// 3:8 Decoder Test
    Test T1(In, Out);

    initial begin
        $display("  In  |  8-bit Decoder Output");
        for(i = 0; i <= 3'b111; i=i+1) begin
            In = i;
            #5 $display("  %b\t\t%b", In, Out);
        end
    end
endmodule

