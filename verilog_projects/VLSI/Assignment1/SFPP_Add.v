`timescale 1ns / 1ps

`define BIAS 8'b01111111

module Add(input [31:0] N1, input [31:0] N2, output reg [31:0] N3);
wire signdiff;
//wire [7:0] diff;

reg cout;
reg [7:0] offset, newexp, diff;
reg [22:0] sum, shift;
reg [23:0] sum2, sum3;

assign signdiff = N1[31] ^ N2[31];

always@(*) begin
        offset = N1[30:23] - `BIAS;
		diff = (N1[30:23] - `BIAS) - (N2[30:23] - `BIAS);
        shift = diff ? ({1'b1, N2[22:1]}) >> (diff - 1'b1) : ({1'b1, N2[22:1]});
        if(signdiff) begin
//            $display("Made it diff %h, sign %h", diff, signdiff);
            {cout, sum} = diff ? (({1'b1,N1[22:0]} - {1'b0, shift}) << diff) : ((N1[22:0] - N2[22:0]) << 1'b1); 
//            $display("new Cout %b, new Sum %h", cout, sum);
            newexp = offset - cout + `BIAS;
//            $display("new exponent %h", newexp);
        end
        else begin
            {cout, sum} = diff ? (N1[22:0] + shift) : ({1'b1,N1[22:1]} + shift);
            newexp = offset + cout + `BIAS;
        end
        N3 = {N1[31], newexp, sum};
end
endmodule

// Single Floating Point Multiplier
// N[31] = Sign Bit
// N[30:23] = 8-bit Exponent
// N[22:0] = 23-bit Fraction
module Test(input [31:0] N1, input [31:0] N2, output [31:0] N3);
wire [31:0] out1, out2;

Add Add1(N1, N2, out1);
Add Add2(N2, N1, out2);

assign N3 = N1[30:0] >= N2[30:0] ? out1 : out2;

endmodule

