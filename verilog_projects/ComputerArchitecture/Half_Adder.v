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

// half adder test Data Flow Model
module Test(input A, input B, output Sum, output Carry);
assign Sum = ~A&B || A&~B;
assign Carry = A|B; 
endmodule

// half adder test Behavioral Model
/*module Test1(input A, input B, output reg Sum, output reg Carry);
    always@(A or B) begin // level sensitive
        Carry <= A|B; // c needs to be a register
        Sum <= ~A&B | A&~B;
    end
endmodule

// half adder test Gate-level Model
module Test2(input A, input B, output Sum, output Carry);
xor sum(Sum, A, B);
or carry(Carry, A, B);
endmodule*/
     