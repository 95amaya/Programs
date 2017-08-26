module Test_tb(); 
    integer i;
    reg [15:0] In;
    reg [3:0] Select;
    wire Out;
 
	// 16:1 Mux Test
    Test T1(In, Select, Out);
    //Eightto1Mux T2(In, Select, Out);
    
    initial begin
        In = 16'hFF00;
        $display("16-bit In = %b", In);
        $display("Select  |  Out");
        for(i = 0; i <= 4'b1111; i=i+1) begin
            Select = i;
            #5 $display("  %b\t\t%b", Select, Out);
        end
    end
endmodule