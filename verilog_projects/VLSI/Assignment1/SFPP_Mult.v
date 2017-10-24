`timescale 1ns / 1ps

`define BIAS 8'b01111111

// 23-bit Fraction Adder
module Fraction(input [22:0] A, input [22:0] B, output [22:0] Sum, output Cout);

assign {Cout, Sum} = A + B;

endmodule

module Exponent(input Cin, input [7:0] A, input [7:0] B, output [7:0] Sum);
wire [7:0] offset;

// Subtract Bias from numbers and add them together to get offset
assign offset = (A - `BIAS) + (B - `BIAS);

// add new offset plus carry from fraction to new bias to get resulting exponent
assign Sum = Cin + offset + `BIAS;

endmodule

// Single Floating Point Multiplier
// N[31] = Sign Bit
// N[30:23] = 8-bit Exponent
// N[22:0] = 23-bit Fraction
module Test(input [31:0] N1, input [31:0] N2, output [31:0] N3);
wire carry;

// Sign XOR logic to get the resulting sign bit
assign N3[31] = N1[31] ^ N2[31];

// Add 23-bit fraction and pass carry to exponent
Fraction Adder1(N1[22:0], N2[22:0], N3[22:0], carry);

// Exponent logic block
// use 127 bias for single floating point precision
Exponent Adder2(carry, N1[30:23], N2[30:23], N3[30:23]);
 
endmodule

