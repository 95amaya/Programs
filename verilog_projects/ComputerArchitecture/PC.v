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

// 16-bit Program Counter Test Behavioral Model
module Test(input clk, input rst, input pc_wrt, input [15:0] in_data,
            output reg[15:0] out_data);
         
    always@(posedge clk or negedge rst) begin
        if(!rst)
            out_data <= 16'h0000;
        else begin
            if(pc_wrt)
                out_data <= in_data;
             else
                out_data <= 16'h0000;
        end
    end
    
endmodule
