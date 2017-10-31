`timescale 1ns / 1ps

//64-bit unsigned multiplier
 module Test(input [63:0] A, input [63:0] B, output [127:0] Output);
 assign Output = A * B;
 endmodule