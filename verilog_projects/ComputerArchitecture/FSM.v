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
`define START    2'b00
`define STATE1   2'b01
`define STATE2   2'b10

// Test FSM
module Test( input clk, input rst, input in, output reg out);
            
	reg [1:0] currState;

	always @(posedge clk or negedge rst) begin
	if(!rst) begin
	   currState <= `START;
	   out <= 1'b0;
	end
	else begin
        case(currState)
          `START: begin
                //out = 1'b0;
                if(in) begin
                    out = 1'b0;
                    currState = `STATE1;
                end
                else begin
                    out = 1'b0;
                    currState = `STATE2;
                end
          end 
          `STATE1: begin
				if(in) begin
                    out = 1'b1;
                    currState = `STATE1;
                end
                else begin
                    out = 1'b1;
                    currState = `STATE2;
                end
          end
          `STATE2: begin 
				if(in) begin
                    out = 1'b0;
                    currState = `STATE1;
                end
                else begin
                    out = 1'b0;
                    currState = `STATE2;
                end
		  end          
          default: currState <= `START;
        endcase
      end
	end
endmodule