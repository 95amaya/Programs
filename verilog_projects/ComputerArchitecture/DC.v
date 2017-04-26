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

// 4-bit Down Counter Test Behavioral Model
module Test(input clk, input rst, output reg [3:0] Q);
         
    always@(posedge clk or negedge rst) begin
        if(!rst)
            Q <= 4'h00;
        else 
            Q <= Q - 1'b1;
    end
    
endmodule

