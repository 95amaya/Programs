`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/20/2017 02:13:02 PM
// Design Name: 
// Module Name: Test_tb
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


module Test_tb();
    reg clk, rst, wr_en;
    reg [2:0] r_reg1, r_reg2, wr_reg;
    reg [15:0] wr_data;
    wire [15:0] r_data1, r_data2;
    integer i;
	
	// 16-bit Regester Bank with 8 registers Test
    Test T1(clk, rst, wr_en, wr_reg, wr_data, r_reg1, r_reg2,
        r_data1, r_data2);

    initial begin
        {clk, wr_en, wr_reg, wr_data, r_reg1, r_reg2} = 0;
        rst = 1'b0;
        
        $display(" rst CLK wr_en wr_reg wr_data r_reg1 r_reg2  |  r_data1  r_data2 ");
        #5 $display("  %b   %b    %b    %b    %h    %b    %b    |  %h \t %h", 
        rst, clk, wr_en, wr_reg, wr_data, r_reg1, r_reg2, r_data1, r_data2);
        rst = 1'b1;
        #5 $display("  %b   %b    %b    %b    %h    %b    %b    |  %h \t %h", 
        rst, clk, wr_en, wr_reg, wr_data, r_reg1, r_reg2, r_data1, r_data2);
                
        wr_en = 1'b1;
        for(i = 0; i <= 3'b111; i=i+1) begin
            wr_reg = i; wr_data = (i+1)*4; r_reg1 = i; r_reg2 = i;
            #10 $display("  %b   %b    %b    %b    %h    %b    %b    |  %h \t %h", 
            rst, clk, wr_en, wr_reg, wr_data, r_reg1, r_reg2, r_data1, r_data2);
        end
    end
    
    always #5 clk = ~clk;
endmodule