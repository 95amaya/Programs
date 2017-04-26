`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/13/2015 11:41:34 AM
// Design Name: 
// Module Name: SM_ROM
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
module clock( input CLK,output reg Clk_Slow,output reg LED);     // slows down 100 Mhz CLK to 1k second period.
	        reg [31:0] k_count;
	        initial begin  k_count <= 32'h00000000;  end  //--------- initial Block  ----------
           always @(posedge CLK) 
   	           begin k_count = k_count + 32'h00000001;
                     if( k_count > 32'h02F5E100) 
                       begin k_count <= 32'h00000000;
                             Clk_Slow <= ! Clk_Slow;
                             LED <= ~LED;                  // outputs Clk_Slow state
                       end
               end
endmodule

module D_FF (input CLK,  input d, output reg q);    //----------------- D Flip-Flop -------------------
           always @(posedge CLK) 
               begin  q <= d;
               end
endmodule

module Seven( input [1:0] SW, input CLK, output reg [7:0] SSEG_CA, output reg [7:0] SSEG_AN );
            initial begin  SSEG_AN = 8'b11111110; end //--------------- initial Block  ----------------
          always@(posedge CLK)
              begin
   		        case (SW)
                    2'b00 : SSEG_CA = 8'b11000000; /*0*/  
                    2'b01 : SSEG_CA = 8'b11111001; /*1*/
                    2'b10 : SSEG_CA = 8'b10100100; /*2*/  
                    default : SSEG_CA = 8'b10001110; /*F*/
                endcase
              end
endmodule

module SM_ROM( input CLK, input x3,input x2,input x1, input PBC, output q0, output q1,
               output reg Z3, output reg Z2, output reg Z1, output LED,output reg LEDPBC,
               output [7:0] SSEG_CA, output [7:0] SSEG_AN);
             //wire [4:0] InX;
             //wire q1,q0,LED;  // connects outputs of D_FF to LEDS q0 and q1. 
             reg Q0,Q1;//,Z1,Z2,Z3;
             initial   //-------------------------------- initial Block  -----------------------------------
                begin    Q0<=0; Q1<=0;  // Possible outputs give State '0' 
                end
            clock RunCLK(CLK,Clk_Slow,LED);
            D_FF Q_0(CLK,Q0,q0);
            D_FF Q_1(CLK,Q1,q1);
            Seven S7( {Q1,Q0}, CLK, SSEG_CA, SSEG_AN );
            always@(posedge Clk_Slow)
                begin  LEDPBC <= PBC;                  // outputs button state to LED 14
                  if(PBC)
                     begin 
                       Z1 <= x2 | Q0 | Q1;   //Z1 = x2 | Q0 | Q1;
                       Z2 <= (~q1) &(~q0) & (~x2);  // Z2 = (~q1) &(~q0) & (x2);
                       Z3 <= (~q1) & (~q0) & (x2) & (~x1);// Z3 = (~q1) & (~q0) & x2 & (~x1);
                       Q1 <= (q0 & x2) | ((~q1) & x2 & (~x1)) | ((~q1) & x3 & x2);
                       Q0 <= ((~q1) & (~x2)) | (q1 & (~x1)) | ((~q1) & (~q0) & (~x3) & x1);   
                     end
                end
endmodule
