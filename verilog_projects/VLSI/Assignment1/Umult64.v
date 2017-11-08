`timescale 1ns / 1ps

//64-bit unsigned multiplier
 //module mult(input [32:0] A, input [32:0] B, output [63:0] sum);
 module Test(input [63:0] A, input [63:0] B, output [127:0] sum);
 //wire [127:0] shift [0:63];
 wire [127:0] shift [0:63];

// 32-bit completion
 assign shift[0]  = B[0]  ? A : 0;          assign shift[16] = B[16] ? (A << 16) : 0;       
 assign shift[1]  = B[1]  ? (A << 1) : 0;   assign shift[17] = B[17] ? (A << 17) : 0; 
 assign shift[2]  = B[2]  ? (A << 2) : 0;   assign shift[18] = B[18] ? (A << 18) : 0;     
 assign shift[3]  = B[3]  ? (A << 3) : 0;   assign shift[19] = B[19] ? (A << 19) : 0;   
 assign shift[4]  = B[4]  ? (A << 4) : 0;   assign shift[20] = B[20] ? (A << 20) : 0;  
 assign shift[5]  = B[5]  ? (A << 5) : 0;   assign shift[21] = B[21] ? (A << 21) : 0; 
 assign shift[6]  = B[6]  ? (A << 6) : 0;   assign shift[22] = B[22] ? (A << 22) : 0;  
 assign shift[7]  = B[7]  ? (A << 7) : 0;   assign shift[23] = B[23] ? (A << 23) : 0;   
 assign shift[8]  = B[8]  ? (A << 8) : 0;   assign shift[24] = B[24] ? (A << 24) : 0;  
 assign shift[9]  = B[9]  ? (A << 9) : 0;   assign shift[25] = B[25] ? (A << 25) : 0; 
 assign shift[10] = B[10] ? (A << 10) : 0;  assign shift[26] = B[26] ? (A << 26) : 0;  
 assign shift[11] = B[11] ? (A << 11) : 0;  assign shift[27] = B[27] ? (A << 27) : 0;   
 assign shift[12] = B[12] ? (A << 12) : 0;  assign shift[28] = B[28] ? (A << 28) : 0;  
 assign shift[13] = B[13] ? (A << 13) : 0;  assign shift[29] = B[29] ? (A << 29) : 0; 
 assign shift[14] = B[14] ? (A << 14) : 0;  assign shift[30] = B[30] ? (A << 30) : 0;   
 assign shift[15] = B[15] ? (A << 15) : 0;  assign shift[31] = B[31] ? (A << 31) : 0;   
 
 
 // 64-bit completion
 assign shift[32] = B[32] ? (A << 32) : 0;  assign shift[48] = B[48] ? (A << 48) : 0;  
 assign shift[33] = B[33] ? (A << 33) : 0;  assign shift[49] = B[49] ? (A << 49) : 0;  
 assign shift[34] = B[34] ? (A << 34) : 0;  assign shift[50] = B[50] ? (A << 50) : 0; 
 assign shift[35] = B[35] ? (A << 35) : 0;  assign shift[51] = B[51] ? (A << 51) : 0;
 assign shift[36] = B[36] ? (A << 36) : 0;  assign shift[52] = B[52] ? (A << 52) : 0; 
 assign shift[37] = B[37] ? (A << 37) : 0;  assign shift[53] = B[53] ? (A << 53) : 0;  
 assign shift[38] = B[38] ? (A << 38) : 0;  assign shift[54] = B[54] ? (A << 54) : 0; 
 assign shift[39] = B[39] ? (A << 39) : 0;  assign shift[55] = B[55] ? (A << 55) : 0; 
 assign shift[40] = B[40] ? (A << 40) : 0;  assign shift[56] = B[56] ? (A << 56) : 0; 
 assign shift[41] = B[41] ? (A << 41) : 0;  assign shift[57] = B[57] ? (A << 57) : 0;   
 assign shift[42] = B[42] ? (A << 42) : 0;  assign shift[58] = B[58] ? (A << 58) : 0; 
 assign shift[43] = B[43] ? (A << 43) : 0;  assign shift[59] = B[59] ? (A << 59) : 0;
 assign shift[44] = B[44] ? (A << 44) : 0;  assign shift[60] = B[60] ? (A << 60) : 0; 
 assign shift[45] = B[45] ? (A << 45) : 0;  assign shift[61] = B[61] ? (A << 61) : 0;   
 assign shift[46] = B[46] ? (A << 46) : 0;  assign shift[62] = B[62] ? (A << 62) : 0; 
 assign shift[47] = B[47] ? (A << 47) : 0;  assign shift[63] = B[63] ? (A << 63) : 0;
 

 // 32-bit Summation
// assign sum = shift[0] + shift[1] + shift[2] + shift[3] + shift[4] + shift[5] + shift[5] + shift[6] +
// shift[7] + shift[8] + shift[9] + shift[10] + shift[11] + shift[12] + shift[13] + shift[14] + shift[15] + 
// shift[16] + shift[17] + shift[18] + shift[19] + shift[20] + shift[21] + shift[22] + shift[23] + shift[24] + 
// shift[25] + shift[26] + shift[27] + shift[28] + shift[29] + shift[30] + shift[31];
 
 // 64-bit Summation
 assign sum = shift[0] + shift[1] + shift[2] + shift[3] + shift[4] + shift[5] + shift[5] + shift[6] +
 shift[7] + shift[8] + shift[9] + shift[10] + shift[11] + shift[12] + shift[13] + shift[14] + shift[15] + 
 shift[16] + shift[17] + shift[18] + shift[19] + shift[20] + shift[21] + shift[22] + shift[23] + shift[24] + 
 shift[25] + shift[26] + shift[27] + shift[28] + shift[29] + shift[30] + shift[31] +
 shift[32] + shift[33] + shift[34] + shift[35] + shift[36] + shift[37] + shift[38] + shift[39] +
 shift[40] + shift[41] + shift[42] + shift[43] + shift[44] + shift[45] + shift[46] + shift[47] + shift[48] + 
 shift[49] + shift[50] + shift[51] + shift[52] + shift[53] + shift[54] + shift[55] + shift[56] + shift[57] + 
 shift[58] + shift[59] + shift[60] + shift[61] + shift[62] + shift[63];
 
 endmodule
 

