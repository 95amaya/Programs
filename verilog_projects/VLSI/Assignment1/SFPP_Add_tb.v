`timescale 1ns / 1ps


module Test_tb(); 
    reg [31:0] N1, N2;
    wire [31:0] N3;
    
    // Single Floating Point Adder module
    Test T1(N1, N2, N3);
        
    initial begin
//      N <= 32'h0000|0000
        N1 = 32'h40A00000; // 5
        N2 = 32'h40000000; // 2
        $display("\n--------- Simulation Results ---------");
        $display("\n\t--- Positives ---");
        $display(" %5s %8s %4s %5s", "N1", "N2", "|", "N3");
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 5 + 2 = 7 (0x40E0|0000)
        N1 = 32'h40100000; // 2.25
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 2.25 + 2 = 4.25 (0x4088|0000)
        N2 = 32'h40800000; // 4
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 2.25 + 4 = 6.25 (0x40c8|0000)
        
        $display("\n\t--- Fractions ---");
        $display(" %5s %8s %4s %5s", "N1", "N2", "|", "N3");
        N1 = 32'h3F000000; // 1/2
        N2 = 32'h3E800000; // 1/4
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 1/2 + 1/4 = 3/4 (0x3F40|0000)
        N2 = 32'h3F400000; // 3/4
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 1/2 + 3/4 = 5/4 (0x3FA0|0000)
        
        $display("\n\t--- Negatives ---");
        N1 = 32'hC0A00000; // -5
        N2 = 32'hC0000000; // -2
        $display(" %5s %8s %4s %5s", "N1", "N2", "|", "N3");
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // -5 + -2 = -7 (0xc0e0|0000)
        N2 = 32'h40000000; // 2
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // -5 + 2 = -3 (0xc040|0000)
        // Testing
        N1 = 32'h41200000; // 10
        N2 = 32'hC1700000; // -15
        #5 $display(" %8h %8h \t %8h", N1, N2, N3); // 10 - 15 = -5 (0xc0a0|0000)
              
        
    end

endmodule