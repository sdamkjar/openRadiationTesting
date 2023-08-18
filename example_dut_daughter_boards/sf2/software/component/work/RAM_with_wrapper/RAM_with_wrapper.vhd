----------------------------------------------------------------------
-- Created by SmartDesign Thu Sep 20 13:44:56 2018
-- Version: v11.8 SP3 11.8.3.6
----------------------------------------------------------------------

----------------------------------------------------------------------
-- Libraries
----------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

library smartfusion2;
use smartfusion2.all;
----------------------------------------------------------------------
-- RAM_with_wrapper entity declaration
----------------------------------------------------------------------
entity RAM_with_wrapper is
    -- Port list
    port(
        -- Inputs
        PADDR   : in  std_logic_vector(7 downto 0);
        PCLK    : in  std_logic;
        PENABLE : in  std_logic;
        PRESETN : in  std_logic;
        PSEL    : in  std_logic;
        PWDATA  : in  std_logic_vector(7 downto 0);
        PWRITE  : in  std_logic;
        -- Outputs
        PRDATA  : out std_logic_vector(7 downto 0);
        PREADY  : out std_logic;
        PSLVERR : out std_logic
        );
end RAM_with_wrapper;
----------------------------------------------------------------------
-- RAM_with_wrapper architecture body
----------------------------------------------------------------------
architecture RTL of RAM_with_wrapper is
----------------------------------------------------------------------
-- Component declarations
----------------------------------------------------------------------
-- mem_apb_wrp
component mem_apb_wrp
    generic( 
        ADDR_WIDTH : integer := 8 ;
        DATA_WIDTH : integer := 8 
        );
    -- Port list
    port(
        -- Inputs
        PADDR        : in  std_logic_vector(7 downto 0);
        PCLK         : in  std_logic;
        PENABLE      : in  std_logic;
        PRESETN      : in  std_logic;
        PSEL         : in  std_logic;
        PWDATA       : in  std_logic_vector(7 downto 0);
        PWRITE       : in  std_logic;
        mem_data_out : in  std_logic_vector(7 downto 0);
        -- Outputs
        PRDATA       : out std_logic_vector(7 downto 0);
        PREADY       : out std_logic;
        PSLVERR      : out std_logic;
        mem_data_in  : out std_logic_vector(7 downto 0);
        raddr        : out std_logic_vector(5 downto 0);
        rclk         : out std_logic;
        rd_enable    : out std_logic;
        waddr        : out std_logic_vector(5 downto 0);
        wclk         : out std_logic;
        wr_enable    : out std_logic
        );
end component;
-- mux_blk
component mux_blk
    -- Port list
    port(
        -- Inputs
        mem_data_in_init  : in  std_logic_vector(7 downto 0);
        p1                : in  std_logic;
        raddr_init        : in  std_logic_vector(5 downto 0);
        rclk_init         : in  std_logic;
        rd_enable_init    : in  std_logic;
        rdata             : in  std_logic_vector(7 downto 0);
        waddr_init        : in  std_logic_vector(5 downto 0);
        wclk_init         : in  std_logic;
        wr_enable_init    : in  std_logic;
        -- Outputs
        mem_data_out_init : out std_logic_vector(7 downto 0);
        raddr             : out std_logic_vector(5 downto 0);
        rclk              : out std_logic;
        rd_en             : out std_logic;
        waddr             : out std_logic_vector(5 downto 0);
        wclk              : out std_logic;
        wdata             : out std_logic_vector(7 downto 0);
        wr_en             : out std_logic
        );
end component;
-- RAM_with_wrapper_SRAM_64x8_0_TPSRAM   -   Actel:SgCore:TPSRAM:1.0.101
component RAM_with_wrapper_SRAM_64x8_0_TPSRAM
    -- Port list
    port(
        -- Inputs
        RADDR : in  std_logic_vector(5 downto 0);
        RCLK  : in  std_logic;
        REN   : in  std_logic;
        WADDR : in  std_logic_vector(5 downto 0);
        WCLK  : in  std_logic;
        WD    : in  std_logic_vector(7 downto 0);
        WEN   : in  std_logic;
        -- Outputs
        RD    : out std_logic_vector(7 downto 0)
        );
end component;
----------------------------------------------------------------------
-- Signal declarations
----------------------------------------------------------------------
signal BIF_1_PRDATA                : std_logic_vector(7 downto 0);
signal BIF_1_PREADY                : std_logic;
signal BIF_1_PSLVERR               : std_logic;
signal mem_apb_wrp_0_mem_data_in   : std_logic_vector(7 downto 0);
signal mem_apb_wrp_0_raddr         : std_logic_vector(5 downto 0);
signal mem_apb_wrp_0_rclk          : std_logic;
signal mem_apb_wrp_0_rd_enable     : std_logic;
signal mem_apb_wrp_0_waddr         : std_logic_vector(5 downto 0);
signal mem_apb_wrp_0_wclk          : std_logic;
signal mem_apb_wrp_0_wr_enable     : std_logic;
signal mux_blk_0_mem_data_out_init : std_logic_vector(7 downto 0);
signal mux_blk_0_raddr             : std_logic_vector(5 downto 0);
signal mux_blk_0_rclk              : std_logic;
signal mux_blk_0_rd_en             : std_logic;
signal mux_blk_0_waddr             : std_logic_vector(5 downto 0);
signal mux_blk_0_wclk              : std_logic;
signal mux_blk_0_wdata             : std_logic_vector(7 downto 0);
signal mux_blk_0_wr_en             : std_logic;
signal SRAM_64x8_0_RD              : std_logic_vector(7 downto 0);
signal BIF_1_PRDATA_net_0          : std_logic_vector(7 downto 0);
signal BIF_1_PREADY_net_0          : std_logic;
signal BIF_1_PSLVERR_net_0         : std_logic;
----------------------------------------------------------------------
-- TiedOff Signals
----------------------------------------------------------------------
signal GND_net                     : std_logic;

begin
----------------------------------------------------------------------
-- Constant assignments
----------------------------------------------------------------------
 GND_net <= '0';
----------------------------------------------------------------------
-- Top level output port assignments
----------------------------------------------------------------------
 BIF_1_PRDATA_net_0  <= BIF_1_PRDATA;
 PRDATA(7 downto 0)  <= BIF_1_PRDATA_net_0;
 BIF_1_PREADY_net_0  <= BIF_1_PREADY;
 PREADY              <= BIF_1_PREADY_net_0;
 BIF_1_PSLVERR_net_0 <= BIF_1_PSLVERR;
 PSLVERR             <= BIF_1_PSLVERR_net_0;
----------------------------------------------------------------------
-- Component instances
----------------------------------------------------------------------
-- mem_apb_wrp_0
mem_apb_wrp_0 : mem_apb_wrp
    generic map( 
        ADDR_WIDTH => ( 8 ),
        DATA_WIDTH => ( 8 )
        )
    port map( 
        -- Inputs
        PCLK         => PCLK,
        PENABLE      => PENABLE,
        PSEL         => PSEL,
        PRESETN      => PRESETN,
        PWRITE       => PWRITE,
        PADDR        => PADDR,
        PWDATA       => PWDATA,
        mem_data_out => mux_blk_0_mem_data_out_init,
        -- Outputs
        PREADY       => BIF_1_PREADY,
        PSLVERR      => BIF_1_PSLVERR,
        PRDATA       => BIF_1_PRDATA,
        rd_enable    => mem_apb_wrp_0_rd_enable,
        wr_enable    => mem_apb_wrp_0_wr_enable,
        wclk         => mem_apb_wrp_0_wclk,
        rclk         => mem_apb_wrp_0_rclk,
        raddr        => mem_apb_wrp_0_raddr,
        waddr        => mem_apb_wrp_0_waddr,
        mem_data_in  => mem_apb_wrp_0_mem_data_in 
        );
-- mux_blk_0
mux_blk_0 : mux_blk
    port map( 
        -- Inputs
        rd_enable_init    => mem_apb_wrp_0_rd_enable,
        wr_enable_init    => mem_apb_wrp_0_wr_enable,
        wclk_init         => mem_apb_wrp_0_wclk,
        rclk_init         => mem_apb_wrp_0_rclk,
        raddr_init        => mem_apb_wrp_0_raddr,
        waddr_init        => mem_apb_wrp_0_waddr,
        mem_data_in_init  => mem_apb_wrp_0_mem_data_in,
        rdata             => SRAM_64x8_0_RD,
        p1                => GND_net,
        -- Outputs
        mem_data_out_init => mux_blk_0_mem_data_out_init,
        rd_en             => mux_blk_0_rd_en,
        wr_en             => mux_blk_0_wr_en,
        wclk              => mux_blk_0_wclk,
        rclk              => mux_blk_0_rclk,
        raddr             => mux_blk_0_raddr,
        waddr             => mux_blk_0_waddr,
        wdata             => mux_blk_0_wdata 
        );
-- SRAM_64x8_0   -   Actel:SgCore:TPSRAM:1.0.101
SRAM_64x8_0 : RAM_with_wrapper_SRAM_64x8_0_TPSRAM
    port map( 
        -- Inputs
        WEN   => mux_blk_0_wr_en,
        REN   => mux_blk_0_rd_en,
        WCLK  => mux_blk_0_wclk,
        RCLK  => mux_blk_0_rclk,
        WD    => mux_blk_0_wdata,
        WADDR => mux_blk_0_waddr,
        RADDR => mux_blk_0_raddr,
        -- Outputs
        RD    => SRAM_64x8_0_RD 
        );

end RTL;
