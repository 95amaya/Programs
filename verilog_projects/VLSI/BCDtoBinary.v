`timescale 1ns / 1ps
/*************************************************
Filename: BCDtoBinary.v
Purpose: Convert 12-bit BCD input -> 10-bit Binary number
Date Created: 9/2017
***************************************************/
// Constants representing the states
`define START    2'b00
`define CHECK    2'b01
`define SHIFT    2'b10
`define DONE     2'b11


`define LIMIT  4'b1000
`define SUB    4'b0011
`define MAXCNT 4'b1001
/***************************** Top module state machine ********************************************/
module Test(input clk, input [11:0] A, input St, output reg [9:0] B);

reg [3:0] ShiftCount;
reg [1:0] State;
reg [3:0] C, D, E;
integer f;

initial begin
    f = $fopen("output.txt","w");
end
// Create state machine for guess sequence
// Need 4 states: 00 - Start, 01 - Check, 10 - REFORMAT, 11 - SHIFT 
always @(posedge clk) begin //or negedge pressReset CLK
    if (St) begin
        case(State)
            `START: begin
                // Initialize Variables
                // Format 3-bit BCD to 3 X 4-bit Registers
                // CDE = 227 in BCD format  
                // C = 2, D = 2, E = 7
                ShiftCount <= 4'b0000;
                B <= 10'h000;
                C <= A[11:8];
                D <= A[7:4];
                E <= A[3:0];
                State <= `CHECK;
            end
            `CHECK: begin
                // Check values > 4'b1000 -> Reformat if true before shifting
                // Check comments vs uncommented way
                if (C >= `LIMIT) begin
                    C <= C - `SUB; 
                    State <= `CHECK;
                end
                if (D >= `LIMIT) begin
                    D <= D - `SUB;
                    State <= `CHECK;
                end
                if (E >= `LIMIT) begin
                    E <= E - `SUB;
                    State <= `CHECK;
                end
                State <= `SHIFT;
            end
            `SHIFT: begin
                // Increment shift count
                ShiftCount <= ShiftCount + 1'b1;   
                B <= {E[0], B[9:1]};
                E <= {D[0], E[3:1]};
                D <= {C[0], D[3:1]};
                C <= C >> 1'b1;
                if(ShiftCount == `MAXCNT) begin
                    State <= `DONE;
                end
                else begin
                    State <= `CHECK;
                end
            end
            `DONE: begin
                // DONE! Do nothing
            end
            default: State <= `START;
        endcase
    end
    else begin
        ShiftCount <= 4'b0000;
        B <= 10'h000;
        C <= 0;
        D <= 0;
        E <= 0;
        State <= `START;
    end    
end

always @(*) begin
    $monitor("----- %s -----", State == 2'b00 ? "1.)START" : (State == 2'b01 ? "2.)CHECK" : (State == 2'b10 ? "3.)SHIFT" : "4.)DONE")));
    $monitor("BCD = %b-%b-%b", C, D, E);
    $monitor("B = %b", B);
    
    if(State >= 0) begin
        $fdisplay(f,"----- %s -----", State == 2'b00 ? "1.)START" : (State == 2'b01 ? "2.)CHECK" : (State == 2'b10 ? "3.)SHIFT" : "4.)DONE")));
        $fdisplay(f,"BCD = %b-%b-%b", C, D, E);
        $fdisplay(f,"B = %b", B);
    end
end

endmodule
