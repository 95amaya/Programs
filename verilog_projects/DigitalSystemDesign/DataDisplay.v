`timescale 1ns / 1ps

// This code slows down the 100 Mhz clock to a 1 second period and a 1k second period.
module clock ( input CLK, output reg Clk_1K, output reg Clk_Slow);     // slows down 100 Mhz CLK to 1k second period.
            parameter THOUclk = 32'h000186A0;
            parameter SLOWclk = 32'h02F5E100; 
            
	        reg [31:0] counter_out,k_count;
	        initial begin     //--------------------------------------- Begin initial Block -----------------------------
           	        counter_out <= 32'h00000000;
                    k_count <= 32'h00000000;
                    Clk_Slow <= 1'b1;
                    Clk_1K <= 0;
                    end    	  //---------------------------------------  End initial Block  -----------------------------
           always @(posedge CLK) 
                begin  counter_out  <=  counter_out + 32'h00000001;           	
            	       if( counter_out > THOUclk)   
                        begin
                          counter_out <=  32'h00000000;
                          Clk_1K <= !Clk_1K;
                       	end
   	            end
   	       always @(posedge CLK) 
   	            begin k_count = k_count + 32'h00000001;
                      if( k_count > SLOWclk) 
                       begin
                         k_count <= 32'h00000000;
                         Clk_Slow <= ! Clk_Slow;
                       end
                end
endmodule

module Seven( input [3:0] Data, input Clk_1k,
              output reg [7:0] SSEG_CA, output reg [7:0] SSEG_AN );
              
          reg   [2:0] digit;		          // used  to cycle through the four digits locations
          reg   [3:0] value;           // used to hold a one digit value
          reg   dp;
        
          /*** --------------- initial Block  ---------------- ***/
          initial begin  
            SSEG_AN <= 8'b11111110; // digit 0
            SSEG_CA <= 8'b11111011; // 2
            digit <= 0;
            value <= 0;
            dp <= 0;
          end 
          
        always@(posedge Clk_1k) begin //Important not to use CLK
            case(digit)	     // determines digit location and loads switch value
                0 : begin SSEG_AN = 8'b11111110;   value = Data[0]; dp = 0;  end  //  hex-1 location
                1 : begin SSEG_AN = 8'b11111101;   value = Data[1]; dp = 0;  end   // hex-2 location
                2 : begin SSEG_AN = 8'b11111011;   value = Data[2]; dp = 0;  end  // comp-1 location
                3 : begin SSEG_AN = 8'b11110111;   value = Data[3]; dp = 0;  end  // comp-2 location
                4 : begin SSEG_AN = 8'b11101111;   value = Data;    dp = 1;  end  // 111
                default : SSEG_AN = 8'b11111111;
            endcase      
            if(dp) begin // Show decimal point
                case (value) // need to cycle through values not SW
                    4'b0000 : SSEG_CA = 8'B01000000; /*0*/  4'b0001 : SSEG_CA = 8'b01111001; /*1*/
                    4'b0010 : SSEG_CA = 8'b00100100; /*2*/  4'b0011 : SSEG_CA = 8'b00110000; /*3*/
                    4'b0100 : SSEG_CA = 8'b00011001; /*4*/  4'b0101 : SSEG_CA = 8'b00010010; /*5*/
                    4'b0110 : SSEG_CA = 8'b00000010; /*6*/  4'b0111 : SSEG_CA = 8'b01111000; /*7*/
                    4'b1000 : SSEG_CA = 8'b00000000; /*8*/  4'b1001 : SSEG_CA = 8'b00011000; /*9*/
                    4'b1010 : SSEG_CA = 8'b00001000; /*A*/  4'b1011 : SSEG_CA = 8'b00000011; /*B*/
                    4'b1100 : SSEG_CA = 8'b01000110; /*C*/  4'b1101 : SSEG_CA = 8'b00100001; /*D*/
                    4'b1110 : SSEG_CA = 8'b00000110; /*E*/  4'b1111 : SSEG_CA = 8'b00001110; /*F*/
                    default : SSEG_CA = 8'b11111111;
                endcase
            end
            else begin
                case (value) // Don't show decimal point
                    4'b0000 : SSEG_CA = 8'B11000000; /*0*/  4'b0001 : SSEG_CA = 8'b11111001; /*1*/
                     default : SSEG_CA = 8'b11111111;
                endcase
            end
            if(digit >= 3'b100) begin digit = 0; end
            else begin digit = digit +1;        end 
        end
endmodule

module Seq_Gen( input CLK, output [7:0] SSEG_CA, output [7:0] SSEG_AN, output [3:0] LEDS);

            parameter SIM = 0;
            wire Clk_1k, Clk_Slow;
            reg [4:0] Store [0:7];  // ROM storing number sequence
            wire [3:0] Data; // Holds 4-bit number from ROM
            reg [2:0] i; // 3 bit value counting 0-7
            
            
            initial   //-------------------------------- initial Block  -----------------------------------
            begin      // Possible outputs give State '0'
               // 2 = 0010              3 = 0011            9 = 1001                A = 1010
               Store[0] <=4'b0010;  Store[1] <=4'b0011;  Store[2] <=4'b1001;  Store[3] <=4'b1010;
               // 1 = 0001              D = 1101            0 = 0000                E = 1110
               Store[4] <=4'b0001;  Store[5] <=4'b1101;  Store[6] <=4'b0000;  Store[7] <=4'b1110;
               i <= 111;
            end
            
            if(SIM) begin
                //clock #(.THOUclk(32'h000000001), .SLOWclk(32'h00000025)) RunClock(CLK, Clk_1k, Clk_Slow);
                clock #(.THOUclk(32'h000000001), .SLOWclk(32'h0000000E)) RunClock(CLK, Clk_1k, Clk_Slow);
            end
            else begin
                clock RunClock(CLK, Clk_1k, Clk_Slow);
            end
            Seven S7(Data[3:0], Clk_1k, SSEG_CA, SSEG_AN);
            
            assign Data = Store[i];
            assign LEDS = Data[3:0];
           
            always@(posedge Clk_Slow) begin                
                i <= i + 3'b001;   // Counts through ROM to display sequence
            end
endmodule
