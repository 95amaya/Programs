`timescale 1ns / 1ps

module Test_tb(); 
	reg Cin;
    reg [3:0] A, B;
    reg [2:0] Fin;
    wire [3:0] Y;
    wire Cout;
    integer i, j;
	
	// 4-bit ALU Test
    Test T1(Cin, A, B, Fin, Y, Cout);

    initial begin
        for(i = 0; i <= 3'b010; i=i+1) begin
            {A, B, Cin} = $random;
            #5;
            $display("Initial A and B");
            $display("A: %b, B: %b", A, B);
            $display("Fin|\tY\t|  Cout");
            for(j = 0; j <= 3'b111; j=j+1) begin
                Fin = j;
                #5 $display("%b|  %b\t\t%b", Fin, Y, Cout);
            end
        end
    end
endmodule