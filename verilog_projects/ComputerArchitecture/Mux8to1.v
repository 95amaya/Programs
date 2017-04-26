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

// 8x1 mux test
module Test(input [0:7] Input, input [2:0] sel, output Out);

wire [0:1] mid;
Fourto1Mux Mux1(Input[0:3], sel[1:0], mid[0]);
Fourto1Mux Mux2(Input[4:7], sel[1:0], mid[1]);

assign Out = sel[2]? mid[1] : mid[0];
endmodule

module Fourto1Mux(input [0:3] in, input [1:0] sel, output Out);
assign Out = sel[0] ? (sel[1] ? in[3] : in[2]) : (sel[1] ? in[1] : in[0]); 
endmodule