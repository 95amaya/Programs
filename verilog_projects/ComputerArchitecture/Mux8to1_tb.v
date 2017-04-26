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
    reg [0:7] In;
    reg [0:2] Select;
    wire Out;
 
	// 8:1 Mux Test
    Test T1(In, Select, Out);

    initial begin
        In = 8'b11110000;
        $display("8-bit In = %b", In);
        $display("Select  |  Out");
        for(i = 0; i <= 3'b111; i=i+1) begin
            Select = i;
            #5 $display("  %b\t\t%b", Select, Out);
        end
    end
endmodule

