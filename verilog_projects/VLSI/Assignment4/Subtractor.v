`timescale 1ns / 1ps

module Full_Substractor(input Bin, input A, input B, output reg Diff, output reg Bout);		

always@(*) begin
    {Bout, Diff} <= A - B - Bin;
end

endmodule

// 4-bit Subtractor
module Test(input Bin, input [3:0] A, input [3:0] B, output [3:0] Diff, output Bout);
wire [2:0] carry;

// Define 4 Full Subtractors which have A, B, and Carry inputs
// It will output a Difference and Borrow bit. 
//The borrow bit will serve as a carry input to the next subtractor 
Full_Substractor FS1(Bin, A[0], B[0], Diff[0], carry[0]);
Full_Substractor FS2(carry[0], A[1], B[1], Diff[1], carry[1]);
Full_Substractor FS3(carry[1], A[2], B[2], Diff[2], carry[2]);
Full_Substractor FS4(carry[2], A[3], B[3], Diff[3], Bout);
// Bout will serve as last borrow output if B > A

endmodule