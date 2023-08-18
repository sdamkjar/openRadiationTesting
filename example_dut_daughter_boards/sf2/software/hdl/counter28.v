`timescale 1 ns / 100 ps

module counter28    (
	cntout,  // Output of the counter
 	clk,  // clock input
 	nreset       // reset input
	);
 //----------Output Ports--------------
 output [27:24] cntout;
 //------------Input Ports-------------- 
 input clk, nreset;
 //------------Internal Variables--------
 reg [27:0] cnt;
 
//-------------Code Starts Here-------
 always @(posedge clk)
 if (~nreset) // active low reset
    begin
		cnt <= 28'b0 ;
	end
  else
	begin
    	cnt <= cnt + 1;
  	end 
  
assign cntout = cnt[27:24];
endmodule 