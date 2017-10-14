`timescale 1ns / 1ps

// Constants representing the functions
`define ADD  3'b000
`define SUB  3'b001
`define OR   3'b010
`define AND  3'b011
`define SHL  3'b100
`define SHR  3'b101
`define ROL  3'b110
`define ROR  3'b111

// Main ALU data-flow modeled
module Test(input Cin, input [3:0] A, input [3:0] B, input [2:0] Fin, output [3:0] Y, output reg Cout);
reg [3:0] out;

assign Y = out;

always@(*) begin
   case(Fin)
        `ADD:  {Cout, out} <= A + B + Cin;
        `SUB:  {Cout, out} <= A - B - Cin; 
        `OR:  begin out <= A | B; Cout <= 1'b0; end
        `AND: begin out <= A & B; Cout <= 1'b0; end
        `SHL: begin out <= A << 1'b1; Cout <= 1'b0; end
        `SHR: begin out <= A >> 1'b1; Cout <= 1'b0; end 
        `ROL: begin out <= {A[2:0], A[3]}; Cout <= 1'b0; end
        `ROR: begin out <= {A[0], A[3:1]}; Cout <= 1'b0; end
        default: {Cout, out} <= 5'b00000;
   endcase
end

endmodule
 