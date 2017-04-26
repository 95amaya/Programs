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

// JK Flip Flop Test Behavioral Model

module Test(input clk, input J, input K, output reg Q);

    always@(posedge clk) begin
        case({J,K})
        2'b00: Q <= Q; 
        2'b01: Q <= 1'b1;
        2'b10: Q <= 1'b0;
        2'b11: Q <= ~Q;
        endcase
    end
    
endmodule

