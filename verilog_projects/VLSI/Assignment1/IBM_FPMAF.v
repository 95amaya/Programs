`timescale 1ns / 1ps

`define BIAS 8'b01111111

// --------------------- Multiplier ------------------------------
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
module SFPM(input [31:0] N1, input [31:0] N2, output [31:0] N3);
wire carry;

// Sign XOR logic to get the resulting sign bit
assign N3[31] = N1[31] ^ N2[31];

// Add 23-bit fraction and pass carry to exponent
Fraction Adder1(N1[22:0], N2[22:0], N3[22:0], carry);

// Exponent logic block
// use 127 bias for single floating point precision
Exponent Adder2(carry, N1[30:23], N2[30:23], N3[30:23]);
 
endmodule

// --------------------- ADDER ------------------------------
module Add(input [31:0] N1, input [31:0] N2, output reg [31:0] N3);
wire signdiff;
//wire [7:0] diff;

reg cout;
reg [7:0] offset, newexp, diff;
reg [22:0] sum, shift;
reg [23:0] sum2, sum3;

assign signdiff = N1[31] ^ N2[31];

always@(*) begin
        offset = N1[30:23] - `BIAS;
		diff = (N1[30:23] - `BIAS) - (N2[30:23] - `BIAS);
        shift = diff ? ({1'b1, N2[22:1]}) >> (diff - 1'b1) : ({1'b1, N2[22:1]});
        if(signdiff) begin
            {cout, sum} = diff ? (({1'b1,N1[22:0]} - {1'b0, shift}) << diff) : ((N1[22:0] - N2[22:0]) << 1'b1);
            newexp = offset - cout + `BIAS;
        end
        else begin
            {cout, sum} = diff ? (N1[22:0] + shift) : ({1'b1,N1[22:1]} + shift);
            newexp = offset + cout + `BIAS;
        end
        N3 = {N1[31], newexp, sum};
end
endmodule

// Single Floating Point Multiplier
// N[31] = Sign Bit
// N[30:23] = 8-bit Exponent
// N[22:0] = 23-bit Fraction
module SFPA(input [31:0] N1, input [31:0] N2, output [31:0] N3);
wire [31:0] out1, out2;

Add Add1(N1, N2, out1);
Add Add2(N2, N1, out2);

assign N3 = N1[30:0] >= N2[30:0] ? out1 : out2;

endmodule

module Test(input [31:0] A, input [31:0] B, input [31:0] C, output [31:0] out);
wire [31:0] product;

SFPM Multiplier1(A, B, product);
SFPA Adder1(product, C, out); 

endmodule

