----------------------------------------------------------------------
-- Created by SmartDesign Sun Sep 23 17:04:41 2018
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
-- MyFirstProject entity declaration
----------------------------------------------------------------------
entity MyFirstProject is
    -- Port list
    port(
        -- Inputs
        DEVRST_N         : in  std_logic;
        MMUART_0_RXD_F2M : in  std_logic;
        -- Outputs
        FPGA_LED         : out std_logic;
        M3_LED           : out std_logic;
        MMUART_0_TXD_M2F : out std_logic
        );
end MyFirstProject;
----------------------------------------------------------------------
-- MyFirstProject architecture body
----------------------------------------------------------------------
architecture RTL of MyFirstProject is
----------------------------------------------------------------------
-- Component declarations
----------------------------------------------------------------------
-- MyCounter
component MyCounter
    -- Port list
    port(
        -- Inputs
        Aclr  : in  std_logic;
        Clock : in  std_logic;
        -- Outputs
        Q     : out std_logic_vector(22 downto 0);
        Tcnt  : out std_logic
        );
end component;
-- MyFirstProject_MSS
component MyFirstProject_MSS
    -- Port list
    port(
        -- Inputs
        M3_RESET_N       : in  std_logic;
        MCCC_CLK_BASE    : in  std_logic;
        MMUART_0_RXD_F2M : in  std_logic;
        MSS_RESET_N_F2M  : in  std_logic;
        -- Outputs
        GPIO_0_M2F       : out std_logic;
        MMUART_0_TXD_M2F : out std_logic
        );
end component;
-- MyFirstProject_OSC_0_OSC   -   Actel:SgCore:OSC:2.0.101
component MyFirstProject_OSC_0_OSC
    -- Port list
    port(
        -- Inputs
        XTL                : in  std_logic;
        -- Outputs
        RCOSC_1MHZ_CCC     : out std_logic;
        RCOSC_1MHZ_O2F     : out std_logic;
        RCOSC_25_50MHZ_CCC : out std_logic;
        RCOSC_25_50MHZ_O2F : out std_logic;
        XTLOSC_CCC         : out std_logic;
        XTLOSC_O2F         : out std_logic
        );
end component;
-- SYSRESET
component SYSRESET
    -- Port list
    port(
        -- Inputs
        DEVRST_N         : in  std_logic;
        -- Outputs
        POWER_ON_RESET_N : out std_logic
        );
end component;
----------------------------------------------------------------------
-- Signal declarations
----------------------------------------------------------------------
signal FPGA_LED_net_0              : std_logic_vector(22 to 22);
signal M3_LED_net_0                : std_logic;
signal MMUART_0_TXD_M2F_net_0      : std_logic;
signal OSC_0_RCOSC_25_50MHZ_O2F    : std_logic;
signal SYSRESET_0_POWER_ON_RESET_N : std_logic;
signal FPGA_LED_net_1              : std_logic;
signal MMUART_0_TXD_M2F_net_1      : std_logic;
signal M3_LED_net_1                : std_logic;
signal Q_slice_0                   : std_logic_vector(21 downto 0);
signal Q_net_0                     : std_logic_vector(22 downto 0);
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
 FPGA_LED_net_1         <= FPGA_LED_net_0(22);
 FPGA_LED               <= FPGA_LED_net_1;
 MMUART_0_TXD_M2F_net_1 <= MMUART_0_TXD_M2F_net_0;
 MMUART_0_TXD_M2F       <= MMUART_0_TXD_M2F_net_1;
 M3_LED_net_1           <= M3_LED_net_0;
 M3_LED                 <= M3_LED_net_1;
----------------------------------------------------------------------
-- Slices assignments
----------------------------------------------------------------------
 FPGA_LED_net_0(22) <= Q_net_0(22);
 Q_slice_0          <= Q_net_0(21 downto 0);
----------------------------------------------------------------------
-- Component instances
----------------------------------------------------------------------
-- MyCounter_0
MyCounter_0 : MyCounter
    port map( 
        -- Inputs
        Clock => OSC_0_RCOSC_25_50MHZ_O2F,
        Aclr  => SYSRESET_0_POWER_ON_RESET_N,
        -- Outputs
        Tcnt  => OPEN,
        Q     => Q_net_0 
        );
-- MyFirstProject_MSS_0
MyFirstProject_MSS_0 : MyFirstProject_MSS
    port map( 
        -- Inputs
        MCCC_CLK_BASE    => OSC_0_RCOSC_25_50MHZ_O2F,
        MMUART_0_RXD_F2M => MMUART_0_RXD_F2M,
        MSS_RESET_N_F2M  => SYSRESET_0_POWER_ON_RESET_N,
        M3_RESET_N       => SYSRESET_0_POWER_ON_RESET_N,
        -- Outputs
        MMUART_0_TXD_M2F => MMUART_0_TXD_M2F_net_0,
        GPIO_0_M2F       => M3_LED_net_0 
        );
-- OSC_0   -   Actel:SgCore:OSC:2.0.101
OSC_0 : MyFirstProject_OSC_0_OSC
    port map( 
        -- Inputs
        XTL                => GND_net, -- tied to '0' from definition
        -- Outputs
        RCOSC_25_50MHZ_CCC => OPEN,
        RCOSC_25_50MHZ_O2F => OSC_0_RCOSC_25_50MHZ_O2F,
        RCOSC_1MHZ_CCC     => OPEN,
        RCOSC_1MHZ_O2F     => OPEN,
        XTLOSC_CCC         => OPEN,
        XTLOSC_O2F         => OPEN 
        );
-- SYSRESET_0
SYSRESET_0 : SYSRESET
    port map( 
        -- Inputs
        DEVRST_N         => DEVRST_N,
        -- Outputs
        POWER_ON_RESET_N => SYSRESET_0_POWER_ON_RESET_N 
        );

end RTL;
