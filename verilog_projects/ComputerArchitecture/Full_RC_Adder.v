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
/*module Test(input A, input B, output Sum, output Carry);
assign Sum = ~A&B || A&~B;
assign Carry = A|B; 
endmodule

// half adder test Behavioral Model
module Test1(input A, input B, output reg Sum, output reg Carry);
    always@(A or B) begin // level sensitive
        Carry <= A|B; // c needs to be a register
        Sum <= ~A&B | A&~B;
    end
endmodule*/

//half adder test Gate-level Model
module half_adder(input A, input B, output Sum, output Carry);
xor sum(Sum, A, B);
or carry(Carry, A, B);
endmodule

// full adder gate-level model
/*module Test(input Cin, input A, input B, output Sum, output Cout);
wire sum1;
wire carry1;
wire carry2;

// Instantiate first half-addder
half_adder add1( A, B, sum1, carry1);
// Instantiate 2nd half_adder with carry in and sum of first_half adder input  
half_adder add2(Cin, sum1, Sum, carry2);
// Instantiate or for carry out
or Carry_Out( Cout, carry1, carry2); 
endmodule*/

// Full-Adder Behavioral Model
module Full_Adder(input Cin, input A, input B, output reg Sum, output reg Cout);

    always@(*)begin
        Sum <= Cin ^ A ^ B;
        Cout <= ((A ^ B) & Cin) | (A & B); 
    end
    
endmodule

// 4-bit carry ripple adder
module Test(input Cin, input [3:0] A, input [3:0] B, output [3:0] Sum, output Cout);
wire [2:0] ripple;

Full_Adder FA1(Cin, A[0], B[0], Sum[0], ripple[0]);
Full_Adder FA2(ripple[0], A[1], B[1], Sum[1], ripple[1]);
Full_Adder FA3(ripple[1], A[2], B[2], Sum[2], ripple[2]);
Full_Adder FA4(ripple[2], A[3], B[3], Sum[3], Cout);
endmodule