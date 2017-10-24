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
    reg [31:0] N1, N2;
    wire [31:0] N3;
    
    // Single Floating Point Multiplier module
    Test T1(N1, N2, N3);
        
    initial begin
//      N <= 32'h0000|0000
        N1 = 32'h40A00000; // 5
        N2 = 32'h40000000; // 2
        $display("\n--------- Simulation Results ---------");
        $display("\n\t--- Positives ---");
        $display(" %5s %8s %4s %5s", "N1", "N2", "|", "N3");
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 5 x 2 = 10 (0x4120|0000)
        N1 = 32'h40100000; // 2.25
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 2.25 x 2 = 4.5 (0x4090|0000)
        N2 = 32'h40800000; // 4
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 2.25 x 4 = 9 (0x4110|0000)
        
        $display("\n\t--- Fractions ---");
        $display(" %5s %8s %4s %5s", "N1", "N2", "|", "N3");
        N1 = 32'h3F000000; // 1/2
        N2 = 32'h3E800000; // 1/4
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 1/2 x 1/4 = 1/8 (0x3E00|0000)
        N2 = 32'h3F400000; // 3/4
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 1/2 x 3/4 = 3/8 (0x3EC0|0000)
        
        $display("\n\t--- Negatives ---");
        N1 = 32'hC0A00000; // -5
        N2 = 32'hC0000000; // -2
        $display(" %5s %8s %4s %5s", "N1", "N2", "|", "N3");
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // -5 x -2 = 10 (0x4120|0000)
        N2 = 32'h40000000; // 2
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // -5 x 2 = -10 (0xC120|0000)
              
        
    end

endmodule