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


// 4-bit unsigned Multiplier
module Test(input [3:0] A, input [3:0] B, output [7:0] Output);
wire [7:0] sum1, sum2, sum3, sum4;

assign sum1 = B[0] ? A : 8'h00;
assign sum2 = B[1] ? (A << 1'b1) : 8'h00;  
assign sum3 = B[2] ? (A << 2'b10) : 8'h00;  
assign sum4 = B[3] ? (A << 2'b11) : 8'h00;  
assign Output = sum1 + sum2 + sum3 + sum4;
endmodule

