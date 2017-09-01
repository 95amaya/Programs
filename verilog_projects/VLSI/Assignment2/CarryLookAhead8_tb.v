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
    integer i;
    reg Cin;

    reg [7:0] A, B;
    wire [7:0] Sum;
	wire Carry, Pg, Gg;

    // Carry Lookahead Adder Module
    Test T1(Cin, A, B, Sum, Carry, Pg, Gg);
        
    initial begin
        for(i = 0; i <= 5'h1F; i=i+1) begin
            {A, B, Cin} = $random;
            if(i % 10 == 0) begin
                // 8-bit test display
                $display("\nCin     A        B\t\t|\t\tSum   Cout\tPg\tGg");
                // 4-bit test display
                // $display("\nCin   A     B\t|\tSum   Cout\tPg\tGg");
            end
            #5 $display(" %b  %b %b\t\t%b\t%b\t%b\t%b", Cin, A, B, Sum, Carry, Pg, Gg);
        end
    end

endmodule