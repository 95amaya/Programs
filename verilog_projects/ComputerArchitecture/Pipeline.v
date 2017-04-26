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
///// ALU Definitions
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

///// Pipeline Definitions
`define FETCH    2'b00
`define EXECUTE  2'b01
`define GENPAR   2'b10

// Test Pipeline
module Test( input clk, input rst, input[15:0] code, input[31:0] A, 
			 input[31:0] B, output reg parity);
           
	reg [1:0] currState;
	reg [3:0] ctrl;
	reg [31:0] Num1, Num2, Result;

    wire par;
	wire [3:0] op;
	wire [31:0] res;
	
	Encoder encoder(code, op);
	ALU alu(A, B, ctrl, res);
	ParityChecker paritychecker(Result, par);
	
	always @(posedge clk or negedge rst) begin
	if(!rst) begin
	   currState <= `FETCH;
	   {Num1, Num2, Result} <= 0;
	   ctrl <= `UNUSED;
	end
	else begin
        case(currState)
          `FETCH: begin
                Num1 <= A;
				Num2 <= B;
				ctrl <= op;
                currState <= `EXECUTE;
          end 
          `EXECUTE: begin
				Result <= res;
                currState <= `GENPAR;
          end
          `GENPAR: begin 
                parity <= par;
                currState <= `FETCH;
		  end          
          default: currState <= `FETCH;
        endcase
      end
	end
endmodule

////////////////////////// Encoder CODE ////////////////////////////////////////////
module Encoder(input[15:0] code, output[3:0] newCode);
	reg[3:0] encode;	
	assign newCode = encode;
	
	always@(*) begin
	case(code)
		16'h0001 : encode <= `AND;    16'h0100 : encode <= `XOR;
		16'h0002 : encode <= `OR;     16'h0200 : encode <= `XNOR;
		16'h0004 : encode <= `ADD;    16'h0400 : encode <= `LSL;
		16'h0008 : encode <= `UNUSED; 16'h0800 : encode <= `LSR;
		16'h0010 : encode <= `ANDI;   16'h1000 : encode <= `SAT;
		16'h0020 : encode <= `ORI;	  16'h2000 : encode <= `ASR;
		16'h0040 : encode <= `SUB;	  16'h4000 : encode <= `RL;
		16'h0080 : encode <= `SLT;	  16'h8000 : encode <= `RR;
		default: encode <= `UNUSED;
	endcase
    end
endmodule

////////////////////////// ALU CODE ////////////////////////////////////////////

// Main ALU data-flow modeled
module ALU(input [31:0] A, input [31:0] B, input [3:0] Fin, output[31:0] Result, output reg Cout);
	reg [31:0] out, temp;
	assign Result = out;
	
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
			`RL: begin out <= {A[30:0], A[31]}; Cout <= 1'b0; end
			`RR: begin out <= {A[0], A[31:1]}; Cout <= 1'b0; end
			default: {Cout, out} <= 33'h000000000;
	   endcase
    end
endmodule

////////////////////////// Parity Checker Code ////////////////////////////////////////////
module ParityChecker(input [31:0] In, output evenParity);
    assign evenParity =  ^In;
endmodule

