`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 01/20/2017 01:54:05 PM
// Design Name: 
// Module Name: Test
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

// 8-bit even parity checker
module Test(input [7:0] In, output evenParity);
assign evenParity =  ((In[0] ^ In[1] ^ In[2] ^ In[3]) ^ 
                      (In[4] ^ In[5] ^ In[6] ^ In[7]));
endmodule

