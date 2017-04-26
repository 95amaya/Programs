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

// Constants representing the functions
`define AND    4'b0000
`define OR     4'b0001
`define ADD    4'b0010
`define UNUSED 4'b0011
`define ANDI   4'b0100
`define ORI    4'b0101
`define SUB    4'b0110
`define SLT    4'b0111
// Additional Functions
`define XOR    4'b1000
`define XNOR   4'b1001
`define LSL    4'b1010 // Shift Operand A
`define LSR    4'b1011
`define SAT    4'b1100
`define ASR    4'b1101
`define RL     4'b1110
`define RR     4'b1111

// Main ALU data-flow modeled
module Test(input [31:0] A, input [31:0] B, input [3:0] Fin, output [31:0] Y, output reg Cout);
reg [31:0] out, temp;

assign Y = out;
    always@(*) begin
       case(Fin)
			`AND:  begin out <= A & B; Cout <= 1'b0; end
			`OR:   begin out <= A | B; Cout <= 1'b0; end
			`ADD:  {Cout, out} <= A + B;
			`ANDI: begin out <= A & ~B; Cout <= 1'b0; end
			`ORI:  begin out <= A | ~B; Cout <= 1'b0; end
			`SUB:  {Cout, out} <= A - B;
			`SLT: begin
                     {Cout, temp} = A - B;
                     out = 32'h00000000 | Cout; // Sign Extend
			     end
			`XOR: {Cout, out} <= A ^ B;
			`XNOR: {Cout, out} <= A ~^ B;
			`LSL: begin out <= A << 1'b1; Cout <= 1'b0; end
			`LSR: begin out <= A >> 1'b1; Cout <= 1'b0; end
			`SAT: begin
			         {Cout, temp} = A + B;
			         if(Cout == 1'b1) 
			             out = 32'hFFFFFFFF; 
			         else 
			             out <= temp;
			      end
			`ASR: begin out <= A >>> 1'b1; Cout <= 1'b0; end
			`RL: begin out <= {A[30:0], A[31]}; Cout <= 1'b0; end // out <= ((A << 1'b1) | A[30]))
			`RR: begin out <= {A[0], A[31:1]}; Cout <= 1'b0; end
			default: {Cout, out} <= 33'h000000000;
	   endcase
    end

endmodule
 