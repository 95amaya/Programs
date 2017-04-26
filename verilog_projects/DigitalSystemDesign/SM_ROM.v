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
module clock( input CLK,output reg Clk_Slow, output reg LED);     // slows down 100 Mhz CLK to 1k second period.
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
               output reg Z3, output reg Z2, output reg Z1,output reg LEDPBC, output LED,
               output [7:0] SSEG_CA, output [7:0] SSEG_AN);
             reg [4:0] Store [0:31];
             wire [4:0] InX;
             //wire q1,q0,LED;  // connects outputs of D_FF to LEDS q0 and q1. 
             //reg Z1,Z2,Z3;
             reg Q0,Q1;
             assign InX = Store[{q1,q0,x3,x2,x1}];
             initial   //-------------------------------- initial Block  -----------------------------------
                begin      // Possible outputs give State '0' 
                   Store[0]  <=5'b01001;  Store[1]  <=5'b01001;  Store[2]  <=5'b10110;  Store[3]  <=5'b00101;
                   Store[4]  <=5'b01001;  Store[5]  <=5'b01001;  Store[6]  <=5'b10110;  Store[7]  <=5'b00110;
                 // Possible outputs give State '1' 
                   Store[8]  <=5'b00101;  Store[9]  <=5'b00101;  Store[10] <=5'b00110;  Store[11] <=5'b00110;
                   Store[12] <=5'b00101;  Store[13] <=5'b00101;  Store[14] <=5'b00110;  Store[15] <=5'b00110;
                 // Possible outputs give State '2'
                   Store[16] <=5'b00101;  Store[17] <=5'b00100;  Store[18] <=5'b00101;  Store[19] <=5'b00100;
                   Store[20] <=5'b00101;  Store[21] <=5'b00100;  Store[22] <=5'b00101;  Store[23] <=5'b00100;
                 // Possible outputs give state '3'  *******Don't Cares*******
                   Store[24] <=5'b00000;  Store[25] <=5'b00000;  Store[26] <=5'b00000;  Store[27] <=5'b00000;
                   Store[28] <=5'b00000;  Store[29] <=5'b00000;  Store[30] <=5'b00000;  Store[31] <=5'b00000;
                end
            clock RunClock(CLK,Clk_Slow,LED);
            D_FF Q_0(CLK,Q0,q0);
            D_FF Q_1(CLK,Q1,q1);
            Seven S7({Q1,Q0}, CLK, SSEG_CA, SSEG_AN );
            always@(posedge Clk_Slow)
                begin  LEDPBC <= PBC;                  // outputs button state to LED 14
                  if(PBC)
                     begin 
                       Q0 <= InX[0];  Q1 <= InX[1];
                       Z1 <= InX[2];  Z2 <= InX[3]; Z3 <= InX[4];
                     end
                end
endmodule
