`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Edward Rodriguez
// 
// Create Date: 10/06/2015 10:50:14 AM
// Design Name: multiplexing
// Module Name: HexDis
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
// This code slows down the 100 Mhz clock to a 1 second period and a 1k second period.
module clock( input CLK, output reg Clk_1K,output reg Clk_Slow);     // slows down 100 Mhz CLK to 1k second period.
	        reg [31:0] counter_out,k_count;
	        initial begin     //--------------------------------------- Begin initial Block -----------------------------
           	        counter_out <= 32'h00000000;
                    k_count<= 32'h00000000;
                    Clk_Slow <=0;
                    Clk_1K <=0;
                    end    	  //---------------------------------------  End initial Block  -----------------------------
           always @(posedge CLK) 
                begin  counter_out  <=  counter_out + 32'h00000001;           	
            	       if( counter_out > 32'h000186A0)   
                        begin
                          counter_out <=  32'h00000000;
                          Clk_1K <= !Clk_1K;
                       	end
   	            end
   	       always @(posedge CLK) 
   	            begin k_count = k_count + 32'h00000001;
                      if( k_count > 32'h02F5E100) 
                       begin
                         k_count <= 32'h00000000;
                         Clk_Slow <= ! Clk_Slow;
                       end
                end
endmodule

module HexDis( input CLK, input [7:0] SW, output reg [7:0] LED,
           	   output reg [7:0] SSEG_CA,  output reg [7:0] SSEG_AN );
	         wire  Clk_1K, Clk_Slow;		  // connects clock module output to always block sensitivity list
	         reg   [3:0] value;           // used to hold a one digit value
	         reg   [1:0] digit;		          // used  to cycle through the four digits locations
             reg   [2:0] L1,L2,L3,L4;    
             clock GenClk(CLK, Clk_1K, Clk_Slow);  //  instantiate the clock module 
	         
	         initial begin
    	             SSEG_AN = 8'b11111111;   L1 = 3'b000;   L2 = 3'b001;
    	                                      L3 = 3'b110;   L4 = 3'b111;
	                 end
	       /* always @(posedge Clk_Slow) 
                begin      
                     L1 = L1 + 1;   L2 = L2 + 1;
                     L3 = L3 + 1;   L4 = L4 + 1; 
                end*/       
            always @(posedge Clk_1K) 
                 begin  LED <= SW;	
       		            case(digit)	     // determines digit location and loads switch value
           		           0 : begin SSEG_AN = ~((SSEG_AN & 0)|( 1 << (L1) ));   value =  SW[3:0];  end  //  hex-1  ((~(SSEG_AN&0))&(0<<0))
           		           1 : begin SSEG_AN = ~((SSEG_AN & 0)|( 1 << (L2) ));   value =  SW[7:4];  end  //  hex-2  ((~(SSEG_AN&0))&(0<<1))
           		           2 : begin SSEG_AN = ~((SSEG_AN & 0)|( 1 << (L3) ));   value = ~SW[3:0];  end  // comp-1  ((~(SSEG_AN&0))&(0<<6))
           		           3 : begin SSEG_AN = ~((SSEG_AN & 0)|( 1 << (L4) ));   value = ~SW[7:4];  end  // comp-2  ((~(SSEG_AN&0))&(0<<7))
       		            endcase
   		                digit = digit +1;       
    		            case(value)	     // determines digit displayed
           		           4'b0000 : SSEG_CA = 8'B11000000; /*0*/   4'b0001 : SSEG_CA = 8'b11111001; /*1*/
           		           4'b0010 : SSEG_CA = 8'b10100100; /*2*/   4'b0011 : SSEG_CA = 8'b10110000; /*3*/
           		           4'b0100 : SSEG_CA = 8'b10011001; /*4*/   4'b0101 : SSEG_CA = 8'b10010010; /*5*/
           		           4'b0110 : SSEG_CA = 8'b10000010; /*6*/   4'b0111 : SSEG_CA = 8'b11111000; /*7*/
           		           4'b1000 : SSEG_CA = 8'b10000000; /*8*/   4'b1001 : SSEG_CA = 8'b10011000; /*9*/
           		           4'b1010 : SSEG_CA = 8'b10001000; /*A*/   4'b1011 : SSEG_CA = 8'b10000011; /*B*/
           		           4'b1100 : SSEG_CA = 8'b11000110; /*C*/   4'b1101 : SSEG_CA = 8'b10100001; /*D*/
           		           4'b1110 : SSEG_CA = 8'b10000110; /*E*/   4'b1111 : SSEG_CA = 8'b10001110; /*F*/
           		           default : SSEG_CA = 8'b11000000;
       		            endcase
   	             end
endmodule
