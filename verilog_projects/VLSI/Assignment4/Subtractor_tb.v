`timescale 1ns / 1ps

module Test_tb(); 
    integer i;
    reg Bin;

    reg [3:0] A, B;
    wire [3:0] Diff;
	wire Bout;

    // 4-bit subtractor Module
    Test T1(Bin, A, B, Diff, Bout);
        
    initial begin
        for(i = 0; i <= 5'h1F; i=i+1) begin
            {A, B, Bin} = $random;
            if(i % 10 == 0) begin
                // 4-bit test display
                 $display("\nBin   A     B\t|\tDiff  Bout");
            end
            #5 $display(" %b  %b %b\t\t%b\t%b", Bin, A, B, Diff, Bout);
        end
    end

endmodule