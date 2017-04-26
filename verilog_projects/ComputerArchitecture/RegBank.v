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

// 16-bit Regester Bank with 8 registers Test Behavioral Model
module Test(input clk, input rst, input wr_en, input [2:0] wr_reg,
input [15:0] wr_data, input [2:0] r_reg1, input [2:0] r_reg2,
output reg [15:0] r_data1, output reg [15:0] r_data2);


reg [15:0] reg_bank [0:7]; // 8 X 16-bit register bank

    always@(posedge clk or negedge rst) begin
        if(!rst) begin : RESET
            integer i;
            for(i = 0; i <= 3'b111; i = i+1) begin
                reg_bank[i] <= 0;
            end
        end
        else begin 
            if(wr_en && wr_reg != 0) begin
                r_data1 = reg_bank[r_reg1];
                if(wr_reg == r_reg2)
                    r_data2 = wr_data;
                else
                    r_data2 = reg_bank[r_reg2];
                reg_bank[wr_reg] = wr_data;
            end    
            else begin
                r_data1 <= reg_bank[r_reg1];
                r_data2 <= reg_bank[r_reg2];
            end
        end
    end
    
endmodule

