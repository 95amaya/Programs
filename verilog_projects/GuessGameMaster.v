`timescale 1ns / 1ps
/*************************************************
Filename: Guess_Game.v
Purpose: Code for Guess_4hex game for DSD project
Date Created: 11/2016
***************************************************/
// Constants representing the states
`define START       2'b00
`define SCROLL      2'b01
`define GUESS       2'b10
`define CORRECT_SEQ 2'b11

// This code slows down the 100 Mhz clock to a 1 second period and a 1k second period.
module clock ( input CLK, output reg Clk_1K, output reg Clk_Slow);     // slows down 100 Mhz CLK to 1k second period.
            parameter THOUclk = 32'h000186A0;
            parameter SLOWclk = 32'h02F5E100; 
            
	        reg [31:0] counter_out, k_count;
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


/************************************************************
debounce
    Takes a button input and debounces it by having a counter
track how long the button has been held down. If it has
been held down long enough conider it to be pressed.
"Long enough" in this case is aound a couple ms.
This is used to remove glitches and add stability to input
buttons.
************************************************************/
module debounce(input clk, input button, output reg press);
    reg [7:0] pressCounter;
    parameter pressLimit = 4'hF;
    
    initial begin
        pressCounter <= 0;
    end
    
    always@(posedge clk) begin
        if(button) begin
            if(pressCounter == pressLimit) begin
                press <= 1'b1;
                pressCounter <= 1'b0;
            end
            else if(pressCounter == 0)
                press <= 1'b0;
            else
                pressCounter <= pressCounter + 1'b1;     
        end
        else begin
            pressCounter <= 1'b1;
            press <= 1'b0;
        end
    end
endmodule

/***************************** Top module state machine ********************************************/
module Guess_Game( input CLK, input [3:0] Guess, input resetb, input Enable,
                input moveLeft, input moveRight, input Enter, input SW14, input SW15,
                output [7:0] SSEG_CA, output [7:0] SSEG_AN, output [3:0] LEDS);

            parameter SIM = 0;
            wire Clk_1k, Clk_Slow;
            //reg [3:0] Store [0:7];  // ROM storing number sequence
            reg [3:0] Store [0:3];  // ROM storing number sequence
            wire [3:0] Data; // Holds 4-bit number from ROM
            wire [15:0] Rand, Hex;
            reg checkDisp;
            reg [3:0] counter;
            reg [1:0] State;
            reg [2:0] out;

            wire pressEnter, pressReset, en;
            wire [1:0] corrSeq; // 0 = do nothing, 1 = start over, 2 = correct sequence 
            wire [7:0] Start_CA, Start_AN, Scroll_CA, Scroll_AN, Guess_CA, Guess_AN, Correct_CA, Correct_AN, Sequence_CA, Sequence_AN;
            reg [7:0] Output_CA, Output_AN;
            
            
            //---------------- Instantiate Modules ------------------------
            // Parameter for simulation. Change clock speed for simulation
            if(SIM) begin
                clock #(.THOUclk(32'h000000001), .SLOWclk(32'h00000012)) RunClock(CLK, Clk_1k, Clk_Slow);
                //Guess #(.SIM(1'b1)) DG(Guess, CLK, Clk_Slow, Clk_1k, moveLeft, moveRight, SSEG_CA, SSEG_AN, LEDS);  // Display 4 Hex numbers
                debounce #(.pressLimit(2'h2)) EnterButton(Clk_1k, Enter, pressEnter);
            end
            else begin
                // Define all the clocks you need before you send them to submodules
                clock RunClock(CLK, Clk_1k, Clk_Slow);
                debounce EnterButton(Clk_1k, Enter, pressEnter);
                debounce ResetButton(Clk_1k, resetb, pressReset);
                // Instantiate Random number module
                scramble16bits scram(Clk_1k, en, {Store[0],Store[1],Store[2],Store[3]}, Rand); // Generate Random number
                //Start Game
                Start StartGame({Store[0],Store[1],Store[2],Store[3]}, Guess, Clk_1k, Clk_Slow, Start_CA, Start_AN);
                // Dislay Random Sequence
                RandomDisp ScrollRandSeq({Store[0],Store[1],Store[2],Store[3]}, Guess, Clk_1k, Scroll_CA, Scroll_AN);
                // Play Game
			    Guess try(Clk_1k, Clk_Slow, pressEnter, Guess, State, {Store[0],Store[1],Store[2],Store[3]}, corrSeq, Guess_CA, Guess_AN, LEDS, Hex);
                // Display End game Sequence
                EndSeq EndGame(Clk_1k, Hex, {Store[0],Store[1],Store[2],Store[3]}, Sequence_CA, Sequence_AN);
            end
            
            
            initial   //-------------------------------- initial Block  -----------------------------------
            begin // Instantiate ROM with number for random number generator (seed)
               // 2 = 0010              3 = 0011            9 = 1001                A = 1010
               Store[0] <=4'b0010;  Store[1] <=4'b0011;  Store[2] <=4'b1001;  Store[3] <=4'b1010;
               counter <= 0;
               State <= 0;
               out <= 0;
               Output_AN <= 8'hFF;
               Output_CA <= 8'hFF;
            end

            //assign LEDS = Store[i];
            // See which state is currently in use
            //assign LEDS[1:0] = State;
            //assign Enable = (i == 2'b00)?1'b1:1'b0; // Enables scramble to generate new random number every new count
            
            // If Enable is low store random number sequence into ROM, Generating GUESS
            // Create state machine for guess sequence
            // Need 4 states: 00 - Getguess, 01 - Correctguess, 10 - Display Sequence, 11 - Correct Sequence 
            always @(posedge Clk_1k) begin //or negedge pressReset CLK
                case(State)
                    `START: begin
                        // Code for getting random number    
                        Output_AN <= Start_AN; 
                        Output_CA <= Start_CA;
                        if(pressEnter) begin
                            Store[0] <= Rand[15:12]; 
                            Store[1] <= Rand[11:8]; 
                            Store[2] <= Rand[7:4]; 
                            Store[3] <= Rand[3:0];
                            State <= `SCROLL;
                        end
                        if(pressReset) begin
                            Store[0] <=4'b0010;  // 2
                            Store[1] <=4'b0011;  // 3
                            Store[2] <=4'b1001;  // 9
                            Store[3] <=4'b1010;  // A
                            State <= `SCROLL;
                        end
                    end
                    `SCROLL: begin
                        Output_AN <= Scroll_AN; 
                        Output_CA <= Scroll_CA;
                        if(SW15)
                            State <= `GUESS; 
                    end
                    `GUESS: begin
                        Output_AN <= Guess_AN; 
                        Output_CA <= Guess_CA;
                        if(~SW15)
                            State <= `SCROLL;
                        else begin
                            case( corrSeq )
                                0: State <= `GUESS;
                                1: State <= `CORRECT_SEQ; // game over WRONG
                                2: State <= `CORRECT_SEQ;  // Game over RIGHT
                                default State <= `GUESS;
                            endcase
                        end
                    end
                    `CORRECT_SEQ: begin
                        Output_AN <= Sequence_AN; 
                        Output_CA <= Sequence_CA;
                        if(pressEnter)
                            State <= `START;
                    end
                    default: State <= `START;
                endcase
            end
            
            assign SSEG_AN = Output_AN;
            assign SSEG_CA = Output_CA;
            assign en = (State == `START) ? 1'b1: 1'b0;
endmodule

/**************************************************************************************************
scramble16bits 
    Takes in 16 bit data register and scrambles it by shifting some bits around when the 
enable pin is down.
                        Input clk, press Enable, data to be scrambled, scrambled data output ******/ 
module scramble16bits(input clk, input Enable, input [15:0] data_in, output reg [15:0] data_out);

    reg [4:0] counter;
    
    initial begin
        data_out <= 0;
        counter <= 0;
    end
    
    always @(posedge clk) begin
        if(Enable) begin // if currState == `START
            data_out[3:0]   <= data_in[3:0] ^ data_in[7:4];
            data_out[7:4]   <= data_in[7:4] ^ data_in[11:8];
            data_out[11:8]  <= data_in[11:8] ^ data_in[15:12];
            data_out[15:12] <= counter ^ data_in[15:12];
        end
        counter <= counter + 1'b1;
    end
    
endmodule 

/*********************************************************************************
Start module
    First state in game which generates a random 4 hex, or 32 bit, number which the
    user will have to guess. This dislpays "PressE16" on the segment displays to
    notify the end user which button to press in order to begin the game. 
***********************************************************************************/
module Start( input [15:0] Data, input [3:0] Guess, input Clk_1k, input Clk_Slow,
              output reg [7:0] SSEG_CA, output reg [7:0] SSEG_AN );
              
          reg   [2:0] digit;		          // used  to cycle through the four digits locations
          reg   [3:0] value;           // used to hold a one digit value
          reg   [2:0] pick; //chooses the value that will be guessed
          
        
          /*** --------------- initial Block  ---------------- ***/
          initial begin  
            SSEG_AN <= 8'b11111111; // digit 0
            SSEG_CA <= 8'b11111111; // 2
            digit <= 0;
            value <= 0;
            pick <= 0;

          end 
                          
        // Spell "Press E16 To Play"
        always@(posedge Clk_1k) begin //Important not to use CLK
            case(digit)	     // determines digit location and loads switch value
                0 : begin SSEG_AN = 8'b01111111;   value = 4'b0000;   end  // P
                1 : begin SSEG_AN = 8'b10111111;   value = 4'b0010;   end  // r
                2 : begin SSEG_AN = 8'b11011111;   value = 4'b0100;   end  // E
                3 : begin SSEG_AN = 8'b11101111;   value = 4'b0110;   end  // S
                4 : begin SSEG_AN = 8'b11110111;   value = 4'b0110;   end  // S
                5 : begin SSEG_AN = 8'b11111011;   value = 4'b0100;   end  // E
                6 : begin SSEG_AN = 8'b11111101;   value = 4'b1000;   end  // 1
                7 : begin SSEG_AN = 8'b11111110;   value = 4'b1010;   end  // 6
                default : SSEG_AN = 8'b11111111;
            endcase      

            case (value) // need to cycle through values not SW
                4'b0000 : SSEG_CA = 8'B10001100; /*P*/  4'b0001 : SSEG_CA = 8'b11111001; /*1 T1*/
                4'b0010 : SSEG_CA = 8'b10101111; /*r*/  4'b0011 : SSEG_CA = 8'b10110000; /*3 T2*/
                4'b0100 : SSEG_CA = 8'b10000110; /*E*/  4'b0101 : SSEG_CA = 8'b10010010; /*5 T3*/
                4'b0110 : SSEG_CA = 8'b10010010; /*S*/  4'b0111 : SSEG_CA = 8'b11111000; /*7 P*/
                4'b1000 : SSEG_CA = 8'b11111001; /*1*/  4'b1001 : SSEG_CA = 8'b10011000; /*9 L*/
                4'b1010 : SSEG_CA = 8'b10000010; /*6*/  4'b1011 : SSEG_CA = 8'b10000011; /*B A*/
                4'b1100 : SSEG_CA = 8'b11000110; /*C */  4'b1101 : SSEG_CA = 8'b10100001; /*D y*/
                4'b1110 : SSEG_CA = 8'b10000110; /*E*/  4'b1111 : SSEG_CA = 8'b10001110; /*F*/
                default : SSEG_CA = 8'b11111111;
            endcase
            digit = digit +1;
        end
endmodule

/*********************************************************************************
RandDisp module
    Second state in game which scrolls the 4 hex random number across the display
    extremely fast. This will be the hint the user is given to try to guess the 
    random number.
***********************************************************************************/
module RandomDisp( input [15:0] Data, input [3:0] Guess, input Clk_1k,
              output reg [7:0] SSEG_CA, output reg [7:0] SSEG_AN );
              
           //wire  Clk_1K, Clk_Slow;		  // connects clock module output to always block sensitivity list
           parameter Scrollclk = 8'h15;
           reg   [3:0] value;           // used to hold a one digit value
           reg   [2:0] digit;                  // used  to cycle through the four digits locations
           reg   [2:0] L1,L2,L3,L4;    
           reg  [7:0] scroll_count;
           
           initial begin
                   SSEG_AN = 8'b11111111;   L1 = 3'b000;   L2 = 3'b001;
                   scroll_count = 0;        L3 = 3'b010;   L4 = 3'b011;                                  
           end
    
          always @(posedge Clk_1k) begin 
             if(scroll_count == Scrollclk) begin
                L1 = L1 + 1;   L2 = L2 + 1;
                L3 = L3 + 1;   L4 = L4 + 1;
                scroll_count = 0;
             end
             case(digit)         // determines digit location and loads switch value 1 << (Lx)
                0 : begin SSEG_AN = ~((SSEG_AN & 0)|( 1 << (L1) ));   value = Data[3:0];    end  //  hex-1  ((~(SSEG_AN&0))&(0<<0))
                1 : begin SSEG_AN = ~((SSEG_AN & 0)|( 1 << (L2) ));   value = Data[7:4];    end  //  hex-2  ((~(SSEG_AN&0))&(0<<1))
                2 : begin SSEG_AN = ~((SSEG_AN & 0)|( 1 << (L3) ));   value = Data[11:8];   end  // comp-1  ((~(SSEG_AN&0))&(0<<6))
                3 : begin SSEG_AN = ~((SSEG_AN & 0)|( 1 << (L4) ));   value = Data[15:12];  end  // comp-2  ((~(SSEG_AN&0))&(0<<7))
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
                if(digit >= 3'b101) begin digit = 0; end
                else begin digit = digit +1;        end
                scroll_count = scroll_count + 1'b1; 
          end
endmodule

/*********************************************************************************
EndSeq module
    Fourth and final state in game which user is notified if they have either guessed
    correctly too many times or guessed the correct sequence. This module displays
    this notification with a "GOOD JOB" or "GAME OVER" message.
***********************************************************************************/
module EndSeq(input Clk_1k, input [15:0] UserSeq, input [15:0] CorrSeq,
              output reg [7:0] SSEG_CA, output reg [7:0] SSEG_AN );
              
          reg   [2:0] digit;		          // used  to cycle through the four digits locations
          reg   [3:0] value;           // used to hold a one digit value
          
        
          /*** --------------- initial Block  ---------------- ***/
          initial begin  
            SSEG_AN <= 8'b11111111; // digit 0
            SSEG_CA <= 8'b11111111; // 2
            digit <= 0;
            value <= 0;
          end 
                          
        always@(posedge Clk_1k) begin //Important not to use CLK
            case(digit)	     // determines digit location and loads switch value
                0 : begin SSEG_AN = 8'b01111111;   value = CorrSeq[15:12];  end  // Correct Hex 4
                1 : begin SSEG_AN = 8'b10111111;   value = CorrSeq[11:8];   end  // Correct Hex 3
                2 : begin SSEG_AN = 8'b11011111;   value = CorrSeq[7:4];    end  // Correct Hex 2
                3 : begin SSEG_AN = 8'b11101111;   value = CorrSeq[3:0];    end  // Correct Hex 1
                4 : begin SSEG_AN = 8'b11110111;   value = UserSeq[15:12];  end  // User Hex 4
                5 : begin SSEG_AN = 8'b11111011;   value = UserSeq[11:8];   end  // User Hex 3
                6 : begin SSEG_AN = 8'b11111101;   value = UserSeq[7:4];    end  // User Hex 2
                7 : begin SSEG_AN = 8'b11111110;   value = UserSeq[3:0];    end  // User Hex 1
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
            digit = digit + 1;
        end
        
endmodule

/*------------------------------------ Sub Top Module Guess -----------------------------------*/
/*********************************************************************************
Guess module
    Third state in game which the user will then try and guess the number using the
    4 right most switches. The user can use buttons T16 or R10 to scroll the place
    of the guess over. The user will enter their guess by pressing E16 which will
    then be checked against the real random number. The user will have 4 tries for 
    each place to guess the correct hex value in the random number. The user will 
    be able to toggle between the Guess and RandomDisp modules with the F16 button.
***********************************************************************************/
// Define substates
`define DISPLAY     2'b01
`define INCORRECT   2'b10
`define CORRECT     2'b11

module Guess(Clk_1k, Clk_Slow, pressEnter, Guess, currState, RandomHex, corrSeq, SSEG_CA, SSEG_AN, LEDS, Hex);
		
		input Clk_1k, Clk_Slow, pressEnter;
		input [3:0] Guess;
		input [1:0] currState;
		input [15:0] RandomHex;
		output [1:0] corrSeq; // 0 = do nothing, 1 = start over, 2 = correct sequence 
		output [7:0] SSEG_CA, SSEG_AN;
		output [3:0] LEDS;
		output reg [15:0] Hex;
          
          parameter SIM = 0;  
          parameter HoldCount = 16'h01FF; 
          parameter corrCount = 8'hFF;  
          reg   [1:0] correctCount;    // holds how many correct values have been guessed
          reg   [1:0] place;            // Displays place where user wants to guess hex value
          reg   [1:0] gameFlag;
          reg   [2:0] wrongCount;
          reg   [1:0] subState;      // Holds the substate of the guess module
          reg   [3:0] correctGuess;
          reg   [15:0] hex, holdCounter;         // Holds 16'b 0000 0000 0000 0000 = [hex4 hex3 hex2 hex1]
		  reg startFlag, LEDhigh, LEDlow;
          reg  [7:0] Output_CA, Output_AN;
          
		  wire [7:0] Guess_AN, Guess_CA, Correct_AN, Correct_CA, Incorrect_AN, Incorrect_CA;
		  wire pressLeft, pressRight, pressEnter; 
          wire correctFlag, endFlag;
          
          
          
          //wire [7:0] Display_AN, Display_CA;
          //////////////////////////
          //reg [1:0] currState;
          //reg [15:0] RandomHex;
            
          /*** --------------- initial Block  ---------------- ***/
          initial begin  
            Output_AN <= 8'b11111111; // digit 
            Output_CA <= 8'b11111111; // 2
            place <= 0;
            hex <= 0;
            correctCount <= 0;
            correctGuess <= 0;
            subState <= 0;
            holdCounter <= 0;
            startFlag <= 0;
            //currState <= `GUESS;
            //RandomHex <= 16'h1234;
            LEDhigh <= 0;
            LEDlow <= 0;
          end 
        
        // Check for button beeing pressed for a given amount of time
        // debounce input
        if(SIM) begin
          //  clock #(.THOUclk(32'h00000001), .SLOWclk(32'h00000012)) RunClock(CLK, Clk_1k, Clk_Slow);
       //     debounce #(.pressLimit(2'h2)) LeftButton(Clk_1k, moveLeft, pressLeft);
       //     debounce #(.pressLimit(2'h2)) RightButton(Clk_1k, moveRight, pressRight);
        //    debounce #(.pressLimit(2'h2)) EnterButton(Clk_1k, Enter, pressEnter);
            DisplayGuess Display(Clk_1k, hex, correctCount, Guess_CA, Guess_AN);
            Correct #(.pressLimit(1'h0)) CorrectGuess(correctGuess, Clk_1k, Flag, Correct_CA, Correct_AN);
            Incorrect #(.pressLimit(1'h0)) WrongGuess(Clk_1k, Incorrect_CA, Incorrect_AN );
        end
        else begin
         //   clock Runclock(CLK, Clk_1k, Clk_Slow);
        //    debounce LeftButton(Clk_1k, moveLeft, pressLeft);
        //    debounce RightButton(Clk_1k, moveRight, pressRight);
        //    debounce EnterButton(Clk_1k, Enter, pressEnter);
            DisplayGuess Display(Clk_1k, hex, correctCount, Guess_CA, Guess_AN);
            Correct CorrectGuess(Clk_1k, correctGuess, correctCount, startFlag, endFlag, Correct_CA, Correct_AN);
            Incorrect WrongGuess(Clk_1k, Incorrect_CA, Incorrect_AN );
        end
        
        // Set up for guess value 
        // Set up states - 00: Neutral/guess 01: Correct 10: Incorrect 
        always @(posedge Clk_1k) begin //or negedge pressReset CLK
          if(currState == `GUESS) begin
              case(subState)
                  `DISPLAY: begin
                      Output_AN <= Guess_AN; 
                      Output_CA <= Guess_CA;
                      // If moveleft button or moveright buttons are pressed, move the digit place
                      //if(pressLeft)   // Debounced input
                        //  place <= place + 1'b1;
                      //if(pressRight)   // Debounced input
                        //  place <= place - 1'b1;
                          
                      //            hex4 hex3 hex2 hex1
                      // 16'b hex = 0000 0000 0000 0000
                      //     Place:   4    3    2    1
                      //hex = 16'h0000 | (Guess << 4*place);
                      hex = (hex & ~(4'hF << 4*place)) | (Guess << 4*place); // zero out place you are currently in
                      
                      if(pressEnter) begin
                        if((hex & (4'b1111 << 4*place)) == (RandomHex & (4'b1111 << 4*place))) begin //exponent, want Random hex1, Randomh hex2 
                            hex = hex | (Guess << 4*place); // remember place you got right
                            correctCount = correctCount + 1'b1; 
                            correctGuess = Guess;
                            startFlag <= 1'b1;
                            place <= place + 1'b1;
                            subState <= `CORRECT;
                            wrongCount <= 0;
                            LEDhigh <= 0;
                            LEDlow <= 0;
                        end
                          else begin // Wrong answer, increase wrongCount (4 tries max), light LEDS[1] if too high and light LED[0] if too low.
                            subState <= `INCORRECT;
                            wrongCount <= wrongCount + 1'b1;
                            if((hex & (4'b1111 << 4*place)) > (RandomHex & (4'b1111 << 4*place))) begin
                                LEDhigh <= 1'b1;
                                LEDlow <= 1'b0;
                            end
                            else begin
                                LEDlow <= 1'b1;
                                LEDhigh <= 1'b0;
                            end
                          end
                      end 
                  end
                  `INCORRECT: begin
                      Output_AN <= Incorrect_AN; 
                      Output_CA <= Incorrect_CA;
                      if(holdCounter == HoldCount) begin
                          if(wrongCount == 3'b100) begin// overflow 4 guesses
                            gameFlag <= 2'b01; // GAME OVER
                            subState <= `DISPLAY;//`INCORRECT;
                            wrongCount <= 0;
                            holdCounter <= 0;
                            correctCount <= 0;
                            place <= 0;
                            Hex = hex;
                            hex = 0;
                          end
                          else begin
                              subState <= `DISPLAY;
                              holdCounter <= 0;
                          end
                      end
                      else 
                          holdCounter <= holdCounter + 1'b1;
                  end
                  `CORRECT: begin
                      Output_AN <= Correct_AN; 
                      Output_CA <= Correct_CA;
                      if(endFlag) begin
                        if(correctCount == 1'b0) begin
                            gameFlag <= 2'b10; // CORRECT!!! GAME WIN
                            subState <= `DISPLAY;
                            startFlag <= 0;
                            correctCount <= 0;
                            place <= 0;
                            Hex = hex;
                            hex = 0;
                        end
                        else begin
                          subState <= `DISPLAY;
                          startFlag <= 0;
                        end
                      end
                  end
                  default: subState <= `DISPLAY;
              endcase
          end
          else begin 
                subState <= `DISPLAY;
                gameFlag <= 2'b00; // Do nothing
          end
        end
        
        assign SSEG_AN = Output_AN;
        assign SSEG_CA = Output_CA;
        assign LEDS[3:2] = place;
        assign LEDS[1] = LEDhigh;
        assign LEDS[0] = LEDlow;
        assign corrSeq = gameFlag; // Keep track of game switching
endmodule

// Submodules for states
/*********************************************************************************
DisplayGuess module
    A submodule to the third state that displays the guess the user wants to input
***********************************************************************************/
module DisplayGuess(input Clk_1k, input [15:0] Hex, input [1:0] correctCount,
                    output [7:0] Display_CA, output [7:0] Display_AN); 

/*(input [3:0] Guess, input [15:0] hex, input Clk_1k, input [1:0] place,
                    input [1:0] correctPlace, output [1:0] correctGuess, output [7:0] Display_CA, 
                    output [7:0] Display_AN, output [3:0] LEDS); */
                
                /*( input [3:0] Guess, input Clk_1k, input pressLeft, input pressRight, input pressEnter,
                 input [1:0] currState, output corretGuess, output [7:0] Display_CA, output [7:0] Display_AN, output [3:0] LEDS);*/
              
          reg   [1:0] digit;          // used  to cycle through the four digits locations
          reg   [3:0] value;           // used to hold a one digit value
          reg   [7:0] Guess_AN, Guess_CA;
            
          /*** --------------- initial Block  ---------------- ***/
          initial begin  
            digit <= 0;
            value <= 0;
          end 
          
        always@(posedge Clk_1k) begin
            // Display based on how many correct values the user has gotten correct
            case(correctCount)
                0: begin
                    Guess_AN = 8'b11111110;   
                    value = Hex[3:0]; //  hex-1 location
                   end
                1: begin
                    case(digit)         // determines digit location and loads switch value
                        0 : begin Guess_AN = 8'b11111110;   value = Hex[3:0];   end  //  hex-1 location
                        1 : begin Guess_AN = 8'b11111101;   value = Hex[7:4];   end  //  hex-2 location
                        default: Guess_AN = 8'b11111111;
                    endcase   
                        digit = digit + 1'b1;
                   end
                2: begin
                    case(digit)         // determines digit location and loads switch value
                        0 : begin Guess_AN = 8'b11111110;   value = Hex[3:0];   end  //  hex-1 location
                        1 : begin Guess_AN = 8'b11111101;   value = Hex[7:4];   end  //  hex-2 location
                        2 : begin Guess_AN = 8'b11111011;   value = Hex[11:8];  end  // comp-1 location
                        default: Guess_AN = 8'b11111111;
                    endcase
                    digit = digit + 1'b1;
                   end   
                3: begin
                    case(digit)         // determines digit location and loads switch value
                      0 : begin Guess_AN = 8'b11111110;   value = Hex[3:0];   end  //  hex-1 location
                      1 : begin Guess_AN = 8'b11111101;   value = Hex[7:4];   end   // hex-2 location
                      2 : begin Guess_AN = 8'b11111011;   value = Hex[11:8];  end  // comp-1 location
                      3 : begin Guess_AN = 8'b11110111;   value = Hex[15:12]; end  // comp-2 location
                      default : Guess_AN = 8'b11111111;
                    endcase
                    digit = digit + 1'b1;
                   end
                   default: Guess_AN = 8'b11111111;
            endcase
                   
            case(value) // need to cycle through values not SW, change 4'b0000, to 8'b11111111
                4'b0000 : Guess_CA = 8'B11000000; /*0*/  4'b0001 : Guess_CA = 8'b11111001; /*1*/
                4'b0010 : Guess_CA = 8'b10100100; /*2*/  4'b0011 : Guess_CA = 8'b10110000; /*3*/
                4'b0100 : Guess_CA = 8'b10011001; /*4*/  4'b0101 : Guess_CA = 8'b10010010; /*5*/
                4'b0110 : Guess_CA = 8'b10000010; /*6*/  4'b0111 : Guess_CA = 8'b11111000; /*7*/
                4'b1000 : Guess_CA = 8'b10000000; /*8*/  4'b1001 : Guess_CA = 8'b10011000; /*9*/
                4'b1010 : Guess_CA = 8'b10001000; /*A*/  4'b1011 : Guess_CA = 8'b10000011; /*B*/
                4'b1100 : Guess_CA = 8'b11000110; /*C*/  4'b1101 : Guess_CA = 8'b10100001; /*D*/
                4'b1110 : Guess_CA = 8'b10000110; /*E*/  4'b1111 : Guess_CA = 8'b10001110; /*F*/
                default : Guess_CA = 8'b11111111; 
            endcase
        end
        
        assign Display_AN = Guess_AN;
        assign Display_CA = Guess_CA;
endmodule

/*********************************************************************************
IncorrectGuess module
    A submodule to the fourth state in the game when the user chooses an incorrect
    answer. Which will diplsay message
***********************************************************************************/
module Incorrect(input Clk_1k, output reg [7:0] SSEG_CA, output reg [7:0] SSEG_AN );
       
       parameter flickerCount = 8'h5F;
       reg  [7:0] flicker_counter;
       initial begin flicker_counter <= 0; end       
	   
       // Flicker '----' across leds 2 times
       always @(posedge Clk_1k) begin // can't have negedge clk in same list as posedge clk
           SSEG_AN = 8'b11110000;
           SSEG_CA[7] = 1;
           SSEG_CA[5:0] = 6'b111111;
           if(flicker_counter == flickerCount) begin
                SSEG_CA[6] = SSEG_CA[6] ^ 1'b1;
                flicker_counter = 0;
           end
           else flicker_counter = flicker_counter + 1'b1;
       end
endmodule

/*********************************************************************************
Correct module
    A submodule to the third state in the game when the user chooses a correct 
    answer. The answer will scroll from right to left into it's correct position
    in the random sequence. After this is done the user will be able to see the
    place in which the number is correct while also being able to guess the rest
    of the values.
***********************************************************************************/
module Correct( input Clk_1k, input [3:0] correctGuess, input [1:0] correctCount, input start,
              output endFlag, output reg [7:0] SSEG_CA, output reg [7:0] SSEG_AN );
              
           parameter Scrollclk = 8'h2F;
           reg   [3:0] value;           // used to hold a one digit value
           reg   [2:0] digit;                  // used  to cycle through the four digits locations
           reg   [2:0] L1;   
           reg  [7:0] scroll_count;
           reg count;
           
           initial begin
               SSEG_AN = 8'b11111111;   L1 = 3'b111; 
               scroll_count = 0;
           end
          
          always @(posedge Clk_1k) begin
            // Scroll from left to right correct guess across segment displays
            if(start) begin
                if(scroll_count == Scrollclk) begin
                   L1 = L1 - 1;
                   scroll_count = 0;
                end  

                SSEG_AN = ~((8'b00000000)|( 1'b1 << (L1) ));
                          
                case (correctGuess) // need to cycle through values not SW
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
                scroll_count = scroll_count + 1'b1;
             end
             else
                L1 = 3'b111;
          end
          assign endFlag = (L1 == (correctCount-1'b1)) ? 1'b1:1'b0;
endmodule