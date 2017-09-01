`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/20/2017 01:54:05 PM
// Design Name: 
// Module Name: Test
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
    reg [3:0] In;
    wire [15:0] Out;
        
     // 4:16 Decoder Test
    Test T1(In, Out);

    initial begin
        $display("  Input  |  16-bit Decoder Output");
        for(i = 0; i <= 4'b1111; i=i+1) begin
            In = i;
            if(In == 4'b1000) begin
                $display("\n  Input  |  16-bit Decoder Output");
            end
            #5 $display("  %b\t\t%b", In, Out);
        end
    end
endmodule