//-------------------------------------------------------------------------------
//-- Title      : mux logic for accessing SRAM
//-------------------------------------------------------------------------------
//-- File       : mux_blk.v
//-- Author     : Corporate Applications Engineering
//-- Company    : Microsemi Corporation
//-- Device     : SmartFusion2
//-- Standard   : Verilog
//-------------------------------------------------------------------------------
//-- Description: This code implementes the mux logic to access the SRAM from the APB  
//--              bus and simple user interface.
//-------------------------------------------------------------------------------
//-- Copyright (c) 2012   Microsemi Corporation
//--                      All rights reserved.
//-------------------------------------------------------------------------------
//-- Revisions  : V1.0
//-------------------------------------------------------------------------------
`timescale 1 ns/100 ps
module mux_blk(
  
  rd_enable_init, wr_enable_init,
  wclk_init, rclk_init,
  raddr_init, waddr_init,
  mem_data_in_init, mem_data_out_init,
  
  rd_en, wr_en,
  wclk, rclk,
  raddr, waddr,
  wdata, rdata,
  );

parameter DATA_WIDTH = 8; // data width 
parameter ADDR_WIDTH = 8; // data width 

input rd_enable_init;
input wr_enable_init;
input wclk_init, rclk_init;
input [ADDR_WIDTH-3:0] raddr_init, waddr_init;
input [DATA_WIDTH-1:0] mem_data_in_init;
output  [DATA_WIDTH-1:0] mem_data_out_init;

output rd_en;
output wr_en;
output wclk, rclk;
output [ADDR_WIDTH-3:0] raddr, waddr;
output [DATA_WIDTH-1:0] wdata;
input  [DATA_WIDTH-1:0] rdata;



assign 	rd_en 	=  rd_enable_init;
assign 	wr_en 	=  wr_enable_init;
assign 	wclk 	=  wclk_init;
assign 	rclk 	=  rclk_init;
assign 	raddr 	= (rd_en) ? raddr_init : 5'b00000;
assign 	waddr 	= (wr_en) ? waddr_init : 5'b11111;
assign 	wdata 	=  mem_data_in_init;

assign 	mem_data_out_init = rdata;
    
endmodule