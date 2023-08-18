//-------------------------------------------------------------------------------
//-- Title      : APB wrapper to SRAM
//-------------------------------------------------------------------------------
//-- File       : mem_apb_wrp.v
//-- Author     : Corporate Applications Engineering
//-- Company    : Microsemi Corporation
//-- Device     : SmartFusion2
//-- Standard   : Verilog
//-------------------------------------------------------------------------------
//-- Description: This code implementes the APB wrapper to receive the read writes  
//--              from the FIC_0 and does the corresponding read or write from SRAM.
//-------------------------------------------------------------------------------
//-- Copyright (c) 2012   Microsemi Corporation
//--                      All rights reserved.
//-------------------------------------------------------------------------------
//-- Revisions  : V1.0
//-------------------------------------------------------------------------------
`timescale 1 ns/100 ps
module mem_apb_wrp(
  PCLK,
  PENABLE,
  PSEL,
  PRESETN,
  PWRITE,
  PREADY,
  PSLVERR,
  PADDR,
  PWDATA,
  PRDATA,
  rd_enable, wr_enable,
  wclk, rclk,
  raddr, waddr,
  mem_data_in,  mem_data_out);

parameter DATA_WIDTH = 8; // data width 
parameter ADDR_WIDTH = 8; // data width 


input PCLK,PENABLE, PSEL, PRESETN, PWRITE;
input  [ADDR_WIDTH-1:0] PADDR;
input  [DATA_WIDTH-1:0] PWDATA;
output [DATA_WIDTH-1:0] PRDATA;
output PREADY, PSLVERR;

output rd_enable;
output wr_enable;
output wclk, rclk;
output [ADDR_WIDTH-3:0] raddr, waddr;
output [DATA_WIDTH-1:0] mem_data_in;
input  [DATA_WIDTH-1:0] mem_data_out;

reg rd_enable;
reg wr_enable;
wire wclk, rclk;
wire [ADDR_WIDTH-3:0] raddr, waddr;
wire [DATA_WIDTH-1:0] mem_data_in;
wire [DATA_WIDTH-1:0] mem_data_out;

reg  PREADY;
wire [DATA_WIDTH-1:0] PRDATA;
reg  [1:0]   fsm; //state machine register


assign PSLVERR = 1'b0;
assign mem_data_in = PWDATA;
assign PRDATA = mem_data_out;
assign wclk = PCLK;
assign rclk = PCLK;
assign raddr[ADDR_WIDTH-3:0] = PADDR[ADDR_WIDTH-1:2];
assign waddr[ADDR_WIDTH-3:0] = PADDR[ADDR_WIDTH-1:2];

always@(posedge PCLK or negedge PRESETN)
if(~PRESETN)
  begin
      fsm <= 2'b00;
      rd_enable <= 1'b0;
      wr_enable <= 1'b0;
      PREADY <= 1'b1;
  end
else
  begin
  
  case (fsm)
     2'b00 :  begin
                  if (~PSEL)
                        begin
                          fsm <= 2'b00;
                        end
                  else        
                        begin
                          fsm <= 2'b01;
                          if (PWRITE)
                                begin 
                                    rd_enable <= 1'b0;
                                    wr_enable <= 1'b1;
                                    PREADY <= 1'b1;
                                end
                          else
                                begin      
                                    rd_enable <= 1'b1;
                                    wr_enable <= 1'b0;
                                    PREADY <= 1'b0; 
                                end
                        end
               end

     2'b01 :  begin            
                          if (PWRITE)
                            begin 
                                rd_enable <= 1'b0;
                                wr_enable <= 1'b0;
                                PREADY <= 1'b1;
                                fsm <= 2'b00;
                            end
                          else
                            begin      
                                rd_enable <= 1'b1; // added to extend the read data so that apb interface can read it
                                wr_enable <= 1'b0;
                                PREADY <= 1'b0;
                                fsm <= 2'b10; 
                            end
              end

     2'b10 :  begin            
                          fsm <= 2'b11;
                          PREADY <= 1'b1;                                     
              end

     2'b11 :  begin            
                          fsm <= 2'b00;
                          rd_enable <= 1'b0; // not need but added to extend the read data so that apb interface can read it
              end

    default : fsm <= 2'b00;
  endcase
end
   
endmodule