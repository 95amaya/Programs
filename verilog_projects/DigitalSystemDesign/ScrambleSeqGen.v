`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/13/2015 11:41:34 AM
// Design Name: 
// Module Name: Guess_Hex
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

                    // Input clk, reset button, data to be scrambled, scrambled data output
module scramble16bits(input clk, input Enable, input [15:0] data_in, output reg [15:0] data_out);

    reg [4:0] counter;
    
    initial begin
        data_out <= 0;
        counter <= 0;
    end
    
    always @(posedge clk) begin
        if(Enable) begin
            data_out[3:0]   <= data_in[3:0] ^ data_in[7:4];
            data_out[7:4]   <= data_in[7:4] ^ data_in[11:8];
            data_out[11:8]  <= data_in[11:8] ^ data_in[15:12];
            data_out[15:12] <= counter ^ data_in[15:12];
        end
        counter <= counter + 1'b1;
    end
    
endmodule 

module Seven( input [15:0] Data, input Clk_1k,
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
                0 : begin SSEG_AN = 8'b11111110;   value = Data[3:0];  end  //  hex-1 location
                1 : begin SSEG_AN = 8'b11111101;   value = Data[7:4];  end   // hex-2 location
                2 : begin SSEG_AN = 8'b11111011;   value = Data[11:8];  end  // comp-1 location
                3 : begin SSEG_AN = 8'b11110111;   value = Data[15:12];  end  // comp-2 location
                //4 : begin SSEG_AN = 8'b11101111;   value = Data;     end  // 111
                default : SSEG_AN = 8'b11111111;
            endcase      

            case (value) // need to cycle through values not SW
                4'b0000 : SSEG_CA = 8'B11000000; /*0*/  4'b0001 : SSEG_CA = 8'b11111001; /*1*/
                4'b0010 : SSEG_CA = 8'b10100100; /*2*/  4'b0011 : SSEG_CA = 8'b10110000; /*3*/
                4'b0100 : SSEG_CA = 8'b10011001; /*4*/  4'b0101 : SSEG_CA = 8'b10010010; /*5*/
                4'b0110 : SSEG_CA = 8'b10000010; /*6*/  4'b0111 : SSEG_CA = 8'b11111000; /*7*/
                4'b1000 : SSEG_CA = 8'b10000000; /*8*/  4'b1001 : SSEG_CA = 8'b10011000; /*9*/
                4'b1010 : SSEG_CA = 8'b10001000; /*A*/  4'b1011 : SSEG_CA = 8'b10000011; /*B*/
                4'b1100 : SSEG_CA = 8'b11000110; /*C*/  4'b1101 : SSEG_CA = 8'b10100001; /*D*/
                4'b1110 : SSEG_CA = 8'b10000110; /*E*/  4'b1111 : SSEG_CA = 8'b10001110; /*F*/
                default : SSEG_CA = 8'b11111111;
            endcase
            if(digit >= 3'b100) begin digit = 0; end
            else begin digit = digit +1;        end 
        end
endmodule

module Seq_Gen( input CLK, output [7:0] SSEG_CA, output [7:0] SSEG_AN, output [3:0] LEDS);

            parameter SIM = 0;
            wire Clk_1k, Clk_Slow;
            reg [3:0] Store [0:3];  // ROM storing Random Hex values
            wire [15:0] Rand;       // Random number generated from module
            reg [1:0] i; // 3 bit value counting 0-7
            wire Enable;
            
            //---------------- Instantiate Modules ------------------------
            // Parameter for simulation. Change clock speed for simulation
            if(SIM) begin
                clock #(.THOUclk(32'h000000001), .SLOWclk(32'h00000012)) RunClock(CLK, Clk_1k, Clk_Slow);
            end
            else begin
                clock RunClock(CLK, Clk_1k, Clk_Slow);
            end
            // Instantiate Segment display module for sequence 
            Seven S7({Store[0],Store[1],Store[2],Store[3]}, Clk_1k, SSEG_CA, SSEG_AN);  // Display 4 Hex numbers
            // Instantiate Random number module
            scramble16bits scram(Clk_1k, Enable, {Store[0],Store[1],Store[2],Store[3]}, Rand); // Generate Random number
            
            initial   //-------------------------------- initial Block  -----------------------------------
            begin // Instantiate ROM with number for random number generator (seed)
               // 2 = 0010              3 = 0011            9 = 1001                A = 1010
               Store[0] <=4'b0010;  Store[1] <=4'b0011;  Store[2] <=4'b1001;  Store[3] <=4'b1010;
               i <= 2'b11;
            end

            assign LEDS = Store[i];
            assign Enable = (i == 2'b00)?1'b1:1'b0; // Enables scramble to generate new random number every new count
            
            always @(posedge CLK) begin
            // If scramble is not enabled then store Random sequence into ROM
                if(!Enable) begin
                    Store[0] <= Rand[15:12]; 
                    Store[1] <= Rand[11:8]; 
                    Store[2] <= Rand[7:4]; 
                    Store[3] <= Rand[3:0];
                end
            end
            
            // begin counting through Random sequence
            always@(posedge Clk_Slow) begin             
                i <= i + 2'b01;
            end
endmodule
