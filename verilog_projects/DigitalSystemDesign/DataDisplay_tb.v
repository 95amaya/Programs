`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 11/07/2016 09:30:23 AM
// Design Name: 
// Module Name: DataDisplay_tb
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


module DataDisplay_tb();
    reg clk;
    wire [7:0] SSEG_CA;
    wire [7:0] SSEG_AN;
    wire [3:0] LEDS;
    
    Seq_Gen #(.SIM(1)) Disp(clk, SSEG_CA, SSEG_AN, LEDS);    
    initial begin
        clk = 0;
    end
    
    always #5 clk <= ~clk;
endmodule