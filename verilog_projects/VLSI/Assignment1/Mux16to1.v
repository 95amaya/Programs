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

// 16x1 mux test
module Test(input [15:0] Input, input [3:0] sel, output Out);
wire [1:0] mid;

Eightto1Mux Mux2(Input[15:8], sel[2:0], mid[1]);
Eightto1Mux Mux1(Input[7:0] , sel[2:0], mid[0]);

assign Out = sel[3]? mid[1] : mid[0];
endmodule

// 8x1 mux test
module Eightto1Mux(input [7:0] Input, input [2:0] sel, output Out);
wire [1:0] mid;

Fourto1Mux Mux2(Input[7:4], sel[1:0], mid[1]);
Fourto1Mux Mux1(Input[3:0], sel[1:0], mid[0]);

assign Out = sel[2]? mid[1] : mid[0];
endmodule

module Fourto1Mux(input [3:0] in, input [1:0] sel, output Out);
assign Out = sel[0] ? (sel[1] ? in[3] : in[2]) : (sel[1] ? in[1] : in[0]); 
endmodule