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

// Full-Adder Behavioral Model
module Full_Adder(input Cin, input A, input B, output reg Sum, output reg Cout);

    always@(*)begin
        Sum <= Cin ^ A ^ B;
        Cout <= ((A ^ B) & Cin) | (A & B); 
    end
    
endmodule

// 4-bit carry ripple adder
module Four_Bit_Adder(input Cin, input [3:0] A, input [3:0] B, output [3:0] Sum, output Cout);
wire [2:0] ripple;

Full_Adder FA1(Cin, A[0], B[0], Sum[0], ripple[0]);
Full_Adder FA2(ripple[0], A[1], B[1], Sum[1], ripple[1]);
Full_Adder FA3(ripple[1], A[2], B[2], Sum[2], ripple[2]);
Full_Adder FA4(ripple[2], A[3], B[3], Sum[3], Cout);
endmodule

// 8-bit carry ripple adder
module Eight_Bit_Adder(input Cin, input [7:0] A, input [7:0] B, output [7:0] Sum, output Cout);
wire ripple;

Four_Bit_Adder FA1(Cin, A[3:0], B[3:0], Sum[3:0], ripple);
Four_Bit_Adder FA2(ripple, A[7:4], B[7:4], Sum[7:4], Cout);

endmodule

// 16-bit carry ripple adder
module Sixteen_Bit_Adder(input Cin, input [15:0] A, input [15:0] B, output [15:0] Sum, output Cout);
wire ripple;

Eight_Bit_Adder FA1(Cin, A[7:0], B[7:0], Sum[7:0], ripple);
Eight_Bit_Adder FA2(ripple, A[15:8], B[15:8], Sum[15:8], Cout);

endmodule

// 32-bit carry ripple adder
module ThirtyTwo_Bit_Adder(input Cin, input [31:0] A, input [31:0] B, output [31:0] Sum, output Cout);
wire ripple;

Sixteen_Bit_Adder FA1(Cin, A[15:0], B[15:0], Sum[15:0], ripple);
Sixteen_Bit_Adder FA2(ripple, A[31:16], B[31:16], Sum[31:16], Cout);

endmodule

// 64-bit carry ripple adder
module Test(input Cin, input [63:0] A, input [63:0] B, output [63:0] Sum, output Cout);
wire ripple;

ThirtyTwo_Bit_Adder FA1(Cin, A[31:0], B[31:0], Sum[31:0], ripple);
ThirtyTwo_Bit_Adder FA2(ripple, A[63:32], B[63:32], Sum[63:32], Cout);

endmodule