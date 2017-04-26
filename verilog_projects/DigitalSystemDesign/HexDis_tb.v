`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/11/2016 09:16:20 AM
// Design Name: 
// Module Name: HexDis_tb
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


module HexDis_tb(
    );
    reg CLK;
    wire [7:0] LED;
    reg [7:0] SW;
    wire [7:0] SSEG_CA;
    wire [7:0] SSEG_AN;
    
    HexDis Hex1 (CLK, SW, LED, SSEG_CA, SSEG_AN);
    
    initial begin
    CLK = 0;
    end
    
    always #5 CLK = ~CLK;
endmodule
