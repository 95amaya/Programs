`timescale 1ns / 1ps

module BCDtoBinary();
	reg [11:0] A;
	reg St, clk;
	
	wire [9:0] B;
	wire [11:0] BCD; // Display change in BCD
	
	Test T1(clk, A, St, B, BCD); 
	
	initial begin
	   A = 12'h227;
	   St = 1'b1;
	   clk = 1'b0;
	   // Works but Use this simulation for output file to save
//	   #250;
//	   St = 1'b0;
//	   A = 12'h009;
//	   #10;
//	   St = 1'b1;
	end

    always #5 clk = ~clk;
    
endmodule