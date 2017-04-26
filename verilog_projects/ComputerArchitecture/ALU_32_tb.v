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
    reg [31:0] A, B;
    reg [3:0] Fin;
    wire [31:0] Y;
    wire Cout;
    integer i;
	
	// 32-bit ALU Test
    Test T1(A, B, Fin, Y, Cout);

    initial begin
        A = 32'h0000FFFF;
        B = 32'hFFFF0000;
        $display("Initial A and B");
        $display("A: %h, B: %h", A, B);
        $display("Fin |\t  Y \t\t Cout");
        for(i = 0; i <= 4'b1111; i=i+1) begin
            Fin = i;
            #5 $display("%b|  %h \t %b", Fin, Y, Cout);
        end
        A = 32'h000FFFFF;
        B = 32'hFFFF0000;
        $display("A and B");
        $display("A: %h, B: %h", A, B);
        $display("Fin |\t  Y \t\t Cout");
        for(i = 0; i <= 4'b1111; i=i+1) begin
            Fin = i;
            #5 $display("%b|  %h \t %b", Fin, Y, Cout);
        end
    end
endmodule