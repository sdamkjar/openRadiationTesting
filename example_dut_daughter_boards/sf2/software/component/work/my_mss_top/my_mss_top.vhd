----------------------------------------------------------------------
-- Created by SmartDesign Thu Sep 20 14:33:03 2018
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
-- my_mss_top entity declaration
----------------------------------------------------------------------
entity my_mss_top is
    -- Port list
    port(
        -- Inputs
        DEVRST_N            : in  std_logic;
        FAB_RESET_N         : in  std_logic;
        FIC_2_APB_M_PRDATA  : in  std_logic_vector(31 downto 0);
        FIC_2_APB_M_PREADY  : in  std_logic;
        FIC_2_APB_M_PSLVERR : in  std_logic;
        -- Outputs
        FIC_0_CLK           : out std_logic;
        FIC_0_LOCK          : out std_logic;
        FIC_2_APB_M_PADDR   : out std_logic_vector(15 downto 2);
        FIC_2_APB_M_PENABLE : out std_logic;
        FIC_2_APB_M_PSEL    : out std_logic;
        FIC_2_APB_M_PWDATA  : out std_logic_vector(31 downto 0);
        FIC_2_APB_M_PWRITE  : out std_logic;
        INIT_DONE           : out std_logic;
        MSS_READY           : out std_logic
        );
end my_mss_top;
----------------------------------------------------------------------
-- my_mss_top architecture body
----------------------------------------------------------------------
architecture RTL of my_mss_top is
----------------------------------------------------------------------
-- Component declarations
----------------------------------------------------------------------
-- my_mss
component my_mss
    -- Port list
    port(
        -- Inputs
        DEVRST_N            : in  std_logic;
        FAB_RESET_N         : in  std_logic;
        FIC_2_APB_M_PRDATA  : in  std_logic_vector(31 downto 0);
        FIC_2_APB_M_PREADY  : in  std_logic;
        FIC_2_APB_M_PSLVERR : in  std_logic;
        -- Outputs
        FIC_0_CLK           : out std_logic;
        FIC_0_LOCK          : out std_logic;
        FIC_2_APB_M_PADDR   : out std_logic_vector(15 downto 2);
        FIC_2_APB_M_PENABLE : out std_logic;
        FIC_2_APB_M_PSEL    : out std_logic;
        FIC_2_APB_M_PWDATA  : out std_logic_vector(31 downto 0);
        FIC_2_APB_M_PWRITE  : out std_logic;
        INIT_DONE           : out std_logic;
        MSS_READY           : out std_logic
        );
end component;
----------------------------------------------------------------------
-- Signal declarations
----------------------------------------------------------------------
signal FIC_0_CLK_net_0                  : std_logic;
signal FIC_0_LOCK_net_0                 : std_logic;
signal FIC_2_APB_MASTER_0_PADDR         : std_logic_vector(15 downto 2);
signal FIC_2_APB_MASTER_0_PENABLE       : std_logic;
signal FIC_2_APB_MASTER_0_PSELx         : std_logic;
signal FIC_2_APB_MASTER_0_PWDATA        : std_logic_vector(31 downto 0);
signal FIC_2_APB_MASTER_0_PWRITE        : std_logic;
signal INIT_DONE_net_0                  : std_logic;
signal MSS_READY_net_0                  : std_logic;
signal FIC_0_CLK_net_1                  : std_logic;
signal FIC_0_LOCK_net_1                 : std_logic;
signal INIT_DONE_net_1                  : std_logic;
signal MSS_READY_net_1                  : std_logic;
signal FIC_2_APB_MASTER_0_PADDR_net_0   : std_logic_vector(15 downto 2);
signal FIC_2_APB_MASTER_0_PSELx_net_0   : std_logic;
signal FIC_2_APB_MASTER_0_PENABLE_net_0 : std_logic;
signal FIC_2_APB_MASTER_0_PWRITE_net_0  : std_logic;
signal FIC_2_APB_MASTER_0_PWDATA_net_0  : std_logic_vector(31 downto 0);

begin
----------------------------------------------------------------------
-- Top level output port assignments
----------------------------------------------------------------------
 FIC_0_CLK_net_1                  <= FIC_0_CLK_net_0;
 FIC_0_CLK                        <= FIC_0_CLK_net_1;
 FIC_0_LOCK_net_1                 <= FIC_0_LOCK_net_0;
 FIC_0_LOCK                       <= FIC_0_LOCK_net_1;
 INIT_DONE_net_1                  <= INIT_DONE_net_0;
 INIT_DONE                        <= INIT_DONE_net_1;
 MSS_READY_net_1                  <= MSS_READY_net_0;
 MSS_READY                        <= MSS_READY_net_1;
 FIC_2_APB_MASTER_0_PADDR_net_0   <= FIC_2_APB_MASTER_0_PADDR;
 FIC_2_APB_M_PADDR(15 downto 2)   <= FIC_2_APB_MASTER_0_PADDR_net_0;
 FIC_2_APB_MASTER_0_PSELx_net_0   <= FIC_2_APB_MASTER_0_PSELx;
 FIC_2_APB_M_PSEL                 <= FIC_2_APB_MASTER_0_PSELx_net_0;
 FIC_2_APB_MASTER_0_PENABLE_net_0 <= FIC_2_APB_MASTER_0_PENABLE;
 FIC_2_APB_M_PENABLE              <= FIC_2_APB_MASTER_0_PENABLE_net_0;
 FIC_2_APB_MASTER_0_PWRITE_net_0  <= FIC_2_APB_MASTER_0_PWRITE;
 FIC_2_APB_M_PWRITE               <= FIC_2_APB_MASTER_0_PWRITE_net_0;
 FIC_2_APB_MASTER_0_PWDATA_net_0  <= FIC_2_APB_MASTER_0_PWDATA;
 FIC_2_APB_M_PWDATA(31 downto 0)  <= FIC_2_APB_MASTER_0_PWDATA_net_0;
----------------------------------------------------------------------
-- Component instances
----------------------------------------------------------------------
-- my_mss_0
my_mss_0 : my_mss
    port map( 
        -- Inputs
        DEVRST_N            => DEVRST_N,
        FAB_RESET_N         => FAB_RESET_N,
        FIC_2_APB_M_PRDATA  => FIC_2_APB_M_PRDATA,
        FIC_2_APB_M_PREADY  => FIC_2_APB_M_PREADY,
        FIC_2_APB_M_PSLVERR => FIC_2_APB_M_PSLVERR,
        -- Outputs
        FIC_0_CLK           => FIC_0_CLK_net_0,
        FIC_0_LOCK          => FIC_0_LOCK_net_0,
        MSS_READY           => MSS_READY_net_0,
        INIT_DONE           => INIT_DONE_net_0,
        FIC_2_APB_M_PADDR   => FIC_2_APB_MASTER_0_PADDR,
        FIC_2_APB_M_PSEL    => FIC_2_APB_MASTER_0_PSELx,
        FIC_2_APB_M_PENABLE => FIC_2_APB_MASTER_0_PENABLE,
        FIC_2_APB_M_PWRITE  => FIC_2_APB_MASTER_0_PWRITE,
        FIC_2_APB_M_PWDATA  => FIC_2_APB_MASTER_0_PWDATA 
        );

end RTL;
