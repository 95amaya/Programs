`timescale 1ns / 1ps

module Test_tb(); 
    reg [31:0] A, B, C;
    wire [31:0] out;
    
    // Single Floating Point Multiplier module
    Test T1(A, B, C, out);
        
    initial begin
//      A <= 32'h0000|0000
        A = 32'h40A00000; // 5
        B = 32'h40000000; // 2
		C = 32'h41700000; // 15
        $display("\n--------- Simulation Results ---------");
        $display(" (%4s   *%4s   )  + %4s %4s %7s", "A", "B", "C", "|", "output");
        #5 $display(" %8h %8h   %8h \t %8h", A, B, C, out); // (5 x 2) + 15 = 25 (0x41C8|0000)
        C = 32'hC1700000; // -15
        #5 $display(" %8h %8h   %8h \t %8h", A, B, C, out); // (5 x 2) - 15 = -5 (0xC0a0|0000)
        A = 32'hC0A00000; // -5
        #5 $display(" %8h %8h   %8h \t %8h", A, B, C, out); // (-5 x 2) - 1/4 = -25 (0xC1C8|0000)
        A = 32'h3F000000; // 1/2
        B = 32'h3F000000; // 1/2
        C = 32'h3E800000; // 1/4
        #5 $display(" %8h %8h   %8h \t %8h", A, B, C, out); // (1/2 x 1/2) + 1/4 = 1/2 (0x3F00|0000)
    end

endmodule