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

// Partial-Full-Adder Behavioral Model
module Partial_Full_Adder(input Cin, input A, input B, output P, output G);

//Sum <= Cin ^ A ^ B;
assign G = A & B;
assign P = A ^ B;		

endmodule

module Carry_Lookahead_Logic(input Cin, input [3:0] P, input [3:0] G, output [3:0] Cout);

// Cout[2:0] generate Carry out for internal partial full adders
assign Cout[0] = G[0] | (P[0] & Cin);
assign Cout[1] = G[1] | (P[1] & G[0]) | (P[1] & P[0] & Cin);
assign Cout[2] = G[2] | (P[2] & G[1]) | (P[2] & P[1] & G[0]) | (P[2] & P[1] & P[0] & Cin);

// Count[3] generates Carry out / Generate bit for 4-bit adder
assign Cout[3] = G[3] | (P[3] & G[2]) | (P[3] & P[2] & G[1]) | (P[3] & P[2] & P[1] & G[0]) | (P[3] & P[2] & P[1] & P[0] & Cin);

endmodule

// 4-bit Look ahead Adder
//module Test(input Cin, input [3:0] A, input [3:0] B, output [3:0] Sum, output Cout, output Pg, output Gg);
//module Four_Bit_CLA(input Cin, input [3:0] A, input [3:0] B, output [3:0] Sum, output Cout, output Pg, output Gg);
module Four_Bit_CLA(input Cin, input [3:0] A, input [3:0] B, output [3:0] Sum, output Pg, output Gg);
wire [3:0] prop, gen, carry;

// Define 4 Partial Full Adders which have A, B, and Carry inputs
// It will output a sum, propagate, and generate bits 
// The progatate and generate bits will be inputted into the carry lookahead logic
Partial_Full_Adder PFA1(Cin, A[0], B[0], prop[0], gen[0]);
Partial_Full_Adder PFA2(carry[0], A[1], B[1], prop[1], gen[1]);
Partial_Full_Adder PFA3(carry[1], A[2], B[2], prop[2], gen[2]);
Partial_Full_Adder PFA4(carry[2], A[3], B[3], prop[3], gen[3]);

// Define Carry Lookahead Logic which has Cin, Propagate, and Generate inputs
// It will output a 4-bit carry that can be inputted into the partial full adders
Carry_Lookahead_Logic CLL1(Cin, prop, gen, carry);

// Sum bits are assigned from progatate and carry bits (carry needs to include cin)
// Carry[3] is carry out bit
assign Sum = prop ^ {carry[2:0], Cin};
//assign Cout = carry[3];

// The 4-bit Lookahead Adder will need its own generate and propogate bits
assign Gg = carry[3];
assign Pg = &prop; // Bitwise reduction

endmodule

// 8-bit carry ripple adder
 module Test(input Cin, input [7:0] A, input [7:0] B, output [7:0] Sum, output Cout, output Pg, output Gg);
 wire [1:0] prop, gen;
 wire carry;

 Four_Bit_CLA CLA1(Cin, A[3:0], B[3:0], Sum[3:0], prop[0], gen[0]);
 Four_Bit_CLA CLA2(carry, A[7:4], B[7:4], Sum[7:4], prop[1], gen[1]);

 // Carry lookahead logic for 8-bit CLA
 assign carry = gen[0] | (prop[0] & Cin);
 assign Cout = gen[1] | (prop[1] & gen[0]) | (prop[1] & prop[0] & Cin);
 assign Gg = Cout;
 assign Pg = &prop;
 
 endmodule