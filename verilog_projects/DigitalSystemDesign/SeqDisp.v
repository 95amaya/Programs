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
// This code slows down the 100 Mhz clock to a 1 second period and a 1k second period.
module clock( input CLK, output reg Clk_1K, output reg Clk_Slow);     // slows down 100 Mhz CLK to 1k second period.
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

module Seven( input [3:0] Data, input Clk_1k, input Enable,
              output reg [7:0] SSEG_CA, output reg [7:0] SSEG_AN );
          initial begin  SSEG_AN = 8'b11111110; end //--------------- initial Block  ----------------
          reg   [2:0] digit;		          // used  to cycle through the four digits locations
          reg   [3:0] value;           // used to hold a one digit value
        always@(posedge Clk_1k) begin //Important not to use CLK
            if(Enable) begin
                case(digit)	     // determines digit location and loads switch value
                    0 : begin SSEG_AN = 8'b11111110;   value = Data[0];  end  //  hex-1 location
                    1 : begin SSEG_AN = 8'b11111101;   value = Data[1];  end   // hex-2 location
                    2 : begin SSEG_AN = 8'b11111011;   value = Data[2];  end  // comp-1 location
                    3 : begin SSEG_AN = 8'b11110111;   value = Data[3];  end  // comp-2 location
                    4 : begin SSEG_AN = 8'b11101111;   value = Data; digit = 3'b111; end  // comp-2 location
                endcase
            
                digit = digit +1; 
                case (value) // need to cycle through values not SW
                    4'b0000 : SSEG_CA = 8'B11000000; /*0*/  4'b0001 : SSEG_CA = 8'b11111001; /*1*/
                    4'b0010 : SSEG_CA = 8'b10100100; /*2*/  4'b0011 : SSEG_CA = 8'b10110000; /*3*/
                    4'b0100 : SSEG_CA = 8'b10011001; /*4*/  4'b0101 : SSEG_CA = 8'b10010010; /*5*/
                    4'b0110 : SSEG_CA = 8'b10000010; /*6*/  4'b0111 : SSEG_CA = 8'b11111000; /*7*/
                    4'b1000 : SSEG_CA = 8'b10000000; /*8*/  4'b1001 : SSEG_CA = 8'b10011000; /*9*/
                    4'b1010 : SSEG_CA = 8'b10001000; /*A*/ 4'b1011 : SSEG_CA = 8'b10000011; /*B*/
                    4'b1100 : SSEG_CA = 8'b11000110; /*C*/  4'b1101 : SSEG_CA = 8'b10100001; /*D*/
                    4'b1110 : SSEG_CA = 8'b10000110; /*E*/  4'b1111 : SSEG_CA = 8'b10001110; /*F*/
                    default : SSEG_CA = 8'b11000000;
                endcase
            end
            else begin
                SSEG_AN = 8'b11111111;
            end
        end
endmodule

module Gen_Seq( input CLK, output [7:0] SSEG_CA, output [7:0] SSEG_AN, output [3:0] LEDS, output EnableOUT);
                // input [3:0] Data, input Enable, output [3:0] LEDS, output EnableOUT

            //reg  Clk_1K;//, Clk_Slow;		  // connects clock module output to always block sensitivity list
            wire Clk_1k, Clk_Slow;
            reg [4:0] Store [0:3]; 
            /* Works
            reg [4:0] Value; // Gets each row
            reg Enable;
            **/
            wire [4:0] Value;
            wire Enable;
            reg [3:0] i;
            
            
            initial   //-------------------------------- initial Block  -----------------------------------
            begin      // Possible outputs give State '0' 
               Store[0] <=5'b10000;  Store[1] <=5'b10001;  Store[2] <=5'b10010;  Store[3] <=5'b10011;
            end
            clock RunClock(CLK, Clk_1k, Clk_Slow);
            Seven S7(Value[3:0], Clk_1k, Enable, SSEG_CA, SSEG_AN);
            
            /* Works also */
            assign Value = Store[i];
            assign Enable = Value[4];
           
            always@(posedge Clk_Slow) begin                  // outputs button state to LED 14
               // Value = Store[i]; works
               // Enable = Value[4]; 
                i = i+1;
            end
            
            assign LEDS = Value[3:0];
            assign EnableOUT = Enable;
endmodule
