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
module Test(input Cin, input [7:0] A, input [7:0] B, output [7:0] Sum, output Cout);
wire ripple;

Four_Bit_Adder FA1(Cin, A[3:0], B[3:0], Sum[3:0], ripple);
Four_Bit_Adder FA2(ripple, A[7:4], B[7:4], Sum[7:4], Cout);

endmodule