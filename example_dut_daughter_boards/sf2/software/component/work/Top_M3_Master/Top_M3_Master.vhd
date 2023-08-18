----------------------------------------------------------------------
-- Created by SmartDesign Thu Sep 20 14:33:34 2018
-- Version: v11.8 SP3 11.8.3.6
----------------------------------------------------------------------

----------------------------------------------------------------------
-- Libraries
----------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

library smartfusion2;
use smartfusion2.all;
library COREAPB3_LIB;
use COREAPB3_LIB.all;
use COREAPB3_LIB.components.all;
----------------------------------------------------------------------
-- Top_M3_Master entity declaration
----------------------------------------------------------------------
entity Top_M3_Master is
    -- Port list
    port(
        -- Inputs
        DEVRST_N : in std_logic
        );
end Top_M3_Master;
----------------------------------------------------------------------
-- Top_M3_Master architecture body
----------------------------------------------------------------------
architecture RTL of Top_M3_Master is
----------------------------------------------------------------------
-- Component declarations
----------------------------------------------------------------------
-- CoreAPB3   -   Actel:DirectCore:CoreAPB3:4.1.100
-- using entity instantiation for component CoreAPB3
-- my_mss_top
component my_mss_top
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
-- RAM_with_wrapper
component RAM_with_wrapper
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
end component;
----------------------------------------------------------------------
-- Signal declarations
----------------------------------------------------------------------
signal CoreAPB3_0_APBmslave0_PENABLE         : std_logic;
signal CoreAPB3_0_APBmslave0_PREADY          : std_logic;
signal CoreAPB3_0_APBmslave0_PSELx           : std_logic;
signal CoreAPB3_0_APBmslave0_PSLVERR         : std_logic;
signal CoreAPB3_0_APBmslave0_PWRITE          : std_logic;
signal my_mss_top_0_FIC_0_CLK                : std_logic;
signal my_mss_top_0_FIC_2_APB_MASTER_PENABLE : std_logic;
signal my_mss_top_0_FIC_2_APB_MASTER_PRDATA  : std_logic_vector(31 downto 0);
signal my_mss_top_0_FIC_2_APB_MASTER_PREADY  : std_logic;
signal my_mss_top_0_FIC_2_APB_MASTER_PSELx   : std_logic;
signal my_mss_top_0_FIC_2_APB_MASTER_PSLVERR : std_logic;
signal my_mss_top_0_FIC_2_APB_MASTER_PWDATA  : std_logic_vector(31 downto 0);
signal my_mss_top_0_FIC_2_APB_MASTER_PWRITE  : std_logic;
signal my_mss_top_0_MSS_READY                : std_logic;
----------------------------------------------------------------------
-- TiedOff Signals
----------------------------------------------------------------------
signal VCC_net                               : std_logic;
signal GND_net                               : std_logic;
signal IADDR_const_net_0                     : std_logic_vector(31 downto 0);
signal PRDATAS1_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS2_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS3_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS4_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS5_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS6_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS7_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS8_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS9_const_net_0                  : std_logic_vector(31 downto 0);
signal PRDATAS10_const_net_0                 : std_logic_vector(31 downto 0);
signal PRDATAS11_const_net_0                 : std_logic_vector(31 downto 0);
signal PRDATAS12_const_net_0                 : std_logic_vector(31 downto 0);
signal PRDATAS13_const_net_0                 : std_logic_vector(31 downto 0);
signal PRDATAS14_const_net_0                 : std_logic_vector(31 downto 0);
signal PRDATAS15_const_net_0                 : std_logic_vector(31 downto 0);
signal PRDATAS16_const_net_0                 : std_logic_vector(31 downto 0);
----------------------------------------------------------------------
-- Bus Interface Nets Declarations - Unequal Pin Widths
----------------------------------------------------------------------
signal CoreAPB3_0_APBmslave0_PADDR_0_7to0    : std_logic_vector(7 downto 0);
signal CoreAPB3_0_APBmslave0_PADDR_0         : std_logic_vector(7 downto 0);
signal CoreAPB3_0_APBmslave0_PADDR           : std_logic_vector(31 downto 0);

signal CoreAPB3_0_APBmslave0_PRDATA          : std_logic_vector(7 downto 0);
signal CoreAPB3_0_APBmslave0_PRDATA_0_31to8  : std_logic_vector(31 downto 8);
signal CoreAPB3_0_APBmslave0_PRDATA_0_7to0   : std_logic_vector(7 downto 0);
signal CoreAPB3_0_APBmslave0_PRDATA_0        : std_logic_vector(31 downto 0);

signal CoreAPB3_0_APBmslave0_PWDATA_0_7to0   : std_logic_vector(7 downto 0);
signal CoreAPB3_0_APBmslave0_PWDATA_0        : std_logic_vector(7 downto 0);
signal CoreAPB3_0_APBmslave0_PWDATA          : std_logic_vector(31 downto 0);

signal my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_31to16: std_logic_vector(31 downto 16);
signal my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_15to2: std_logic_vector(15 downto 2);
signal my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_1to0: std_logic_vector(1 downto 0);
signal my_mss_top_0_FIC_2_APB_MASTER_PADDR_0 : std_logic_vector(31 downto 0);
signal my_mss_top_0_FIC_2_APB_MASTER_PADDR   : std_logic_vector(15 downto 2);


begin
----------------------------------------------------------------------
-- Constant assignments
----------------------------------------------------------------------
 VCC_net               <= '1';
 GND_net               <= '0';
 IADDR_const_net_0     <= B"00000000000000000000000000000000";
 PRDATAS1_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS2_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS3_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS4_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS5_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS6_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS7_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS8_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS9_const_net_0  <= B"00000000000000000000000000000000";
 PRDATAS10_const_net_0 <= B"00000000000000000000000000000000";
 PRDATAS11_const_net_0 <= B"00000000000000000000000000000000";
 PRDATAS12_const_net_0 <= B"00000000000000000000000000000000";
 PRDATAS13_const_net_0 <= B"00000000000000000000000000000000";
 PRDATAS14_const_net_0 <= B"00000000000000000000000000000000";
 PRDATAS15_const_net_0 <= B"00000000000000000000000000000000";
 PRDATAS16_const_net_0 <= B"00000000000000000000000000000000";
----------------------------------------------------------------------
-- Bus Interface Nets Assignments - Unequal Pin Widths
----------------------------------------------------------------------
 CoreAPB3_0_APBmslave0_PADDR_0_7to0(7 downto 0) <= CoreAPB3_0_APBmslave0_PADDR(7 downto 0);
 CoreAPB3_0_APBmslave0_PADDR_0 <= ( CoreAPB3_0_APBmslave0_PADDR_0_7to0(7 downto 0) );

 CoreAPB3_0_APBmslave0_PRDATA_0_31to8(31 downto 8) <= B"000000000000000000000000";
 CoreAPB3_0_APBmslave0_PRDATA_0_7to0(7 downto 0) <= CoreAPB3_0_APBmslave0_PRDATA(7 downto 0);
 CoreAPB3_0_APBmslave0_PRDATA_0 <= ( CoreAPB3_0_APBmslave0_PRDATA_0_31to8(31 downto 8) & CoreAPB3_0_APBmslave0_PRDATA_0_7to0(7 downto 0) );

 CoreAPB3_0_APBmslave0_PWDATA_0_7to0(7 downto 0) <= CoreAPB3_0_APBmslave0_PWDATA(7 downto 0);
 CoreAPB3_0_APBmslave0_PWDATA_0 <= ( CoreAPB3_0_APBmslave0_PWDATA_0_7to0(7 downto 0) );

 my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_31to16(31 downto 16) <= B"0000000000000000";
 my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_15to2(15 downto 2) <= my_mss_top_0_FIC_2_APB_MASTER_PADDR(15 downto 2);
 my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_1to0(1 downto 0) <= B"00";
 my_mss_top_0_FIC_2_APB_MASTER_PADDR_0 <= ( my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_31to16(31 downto 16) & my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_15to2(15 downto 2) & my_mss_top_0_FIC_2_APB_MASTER_PADDR_0_1to0(1 downto 0) );

----------------------------------------------------------------------
-- Component instances
----------------------------------------------------------------------
-- CoreAPB3_0   -   Actel:DirectCore:CoreAPB3:4.1.100
CoreAPB3_0 : entity COREAPB3_LIB.CoreAPB3
    generic map( 
        APB_DWIDTH      => ( 32 ),
        APBSLOT0ENABLE  => ( 1 ),
        APBSLOT1ENABLE  => ( 0 ),
        APBSLOT2ENABLE  => ( 0 ),
        APBSLOT3ENABLE  => ( 0 ),
        APBSLOT4ENABLE  => ( 0 ),
        APBSLOT5ENABLE  => ( 0 ),
        APBSLOT6ENABLE  => ( 0 ),
        APBSLOT7ENABLE  => ( 0 ),
        APBSLOT8ENABLE  => ( 0 ),
        APBSLOT9ENABLE  => ( 0 ),
        APBSLOT10ENABLE => ( 0 ),
        APBSLOT11ENABLE => ( 0 ),
        APBSLOT12ENABLE => ( 0 ),
        APBSLOT13ENABLE => ( 0 ),
        APBSLOT14ENABLE => ( 0 ),
        APBSLOT15ENABLE => ( 0 ),
        FAMILY          => ( 19 ),
        IADDR_OPTION    => ( 0 ),
        MADDR_BITS      => ( 28 ),
        SC_0            => ( 0 ),
        SC_1            => ( 0 ),
        SC_2            => ( 0 ),
        SC_3            => ( 0 ),
        SC_4            => ( 0 ),
        SC_5            => ( 0 ),
        SC_6            => ( 0 ),
        SC_7            => ( 0 ),
        SC_8            => ( 0 ),
        SC_9            => ( 0 ),
        SC_10           => ( 0 ),
        SC_11           => ( 0 ),
        SC_12           => ( 0 ),
        SC_13           => ( 0 ),
        SC_14           => ( 0 ),
        SC_15           => ( 0 ),
        UPR_NIBBLE_POSN => ( 6 )
        )
    port map( 
        -- Inputs
        PRESETN    => GND_net, -- tied to '0' from definition
        PCLK       => GND_net, -- tied to '0' from definition
        PADDR      => my_mss_top_0_FIC_2_APB_MASTER_PADDR_0,
        PWRITE     => my_mss_top_0_FIC_2_APB_MASTER_PWRITE,
        PENABLE    => my_mss_top_0_FIC_2_APB_MASTER_PENABLE,
        PWDATA     => my_mss_top_0_FIC_2_APB_MASTER_PWDATA,
        PSEL       => my_mss_top_0_FIC_2_APB_MASTER_PSELx,
        PRDATAS0   => CoreAPB3_0_APBmslave0_PRDATA_0,
        PREADYS0   => CoreAPB3_0_APBmslave0_PREADY,
        PSLVERRS0  => CoreAPB3_0_APBmslave0_PSLVERR,
        PRDATAS1   => PRDATAS1_const_net_0, -- tied to X"0" from definition
        PREADYS1   => VCC_net, -- tied to '1' from definition
        PSLVERRS1  => GND_net, -- tied to '0' from definition
        PRDATAS2   => PRDATAS2_const_net_0, -- tied to X"0" from definition
        PREADYS2   => VCC_net, -- tied to '1' from definition
        PSLVERRS2  => GND_net, -- tied to '0' from definition
        PRDATAS3   => PRDATAS3_const_net_0, -- tied to X"0" from definition
        PREADYS3   => VCC_net, -- tied to '1' from definition
        PSLVERRS3  => GND_net, -- tied to '0' from definition
        PRDATAS4   => PRDATAS4_const_net_0, -- tied to X"0" from definition
        PREADYS4   => VCC_net, -- tied to '1' from definition
        PSLVERRS4  => GND_net, -- tied to '0' from definition
        PRDATAS5   => PRDATAS5_const_net_0, -- tied to X"0" from definition
        PREADYS5   => VCC_net, -- tied to '1' from definition
        PSLVERRS5  => GND_net, -- tied to '0' from definition
        PRDATAS6   => PRDATAS6_const_net_0, -- tied to X"0" from definition
        PREADYS6   => VCC_net, -- tied to '1' from definition
        PSLVERRS6  => GND_net, -- tied to '0' from definition
        PRDATAS7   => PRDATAS7_const_net_0, -- tied to X"0" from definition
        PREADYS7   => VCC_net, -- tied to '1' from definition
        PSLVERRS7  => GND_net, -- tied to '0' from definition
        PRDATAS8   => PRDATAS8_const_net_0, -- tied to X"0" from definition
        PREADYS8   => VCC_net, -- tied to '1' from definition
        PSLVERRS8  => GND_net, -- tied to '0' from definition
        PRDATAS9   => PRDATAS9_const_net_0, -- tied to X"0" from definition
        PREADYS9   => VCC_net, -- tied to '1' from definition
        PSLVERRS9  => GND_net, -- tied to '0' from definition
        PRDATAS10  => PRDATAS10_const_net_0, -- tied to X"0" from definition
        PREADYS10  => VCC_net, -- tied to '1' from definition
        PSLVERRS10 => GND_net, -- tied to '0' from definition
        PRDATAS11  => PRDATAS11_const_net_0, -- tied to X"0" from definition
        PREADYS11  => VCC_net, -- tied to '1' from definition
        PSLVERRS11 => GND_net, -- tied to '0' from definition
        PRDATAS12  => PRDATAS12_const_net_0, -- tied to X"0" from definition
        PREADYS12  => VCC_net, -- tied to '1' from definition
        PSLVERRS12 => GND_net, -- tied to '0' from definition
        PRDATAS13  => PRDATAS13_const_net_0, -- tied to X"0" from definition
        PREADYS13  => VCC_net, -- tied to '1' from definition
        PSLVERRS13 => GND_net, -- tied to '0' from definition
        PRDATAS14  => PRDATAS14_const_net_0, -- tied to X"0" from definition
        PREADYS14  => VCC_net, -- tied to '1' from definition
        PSLVERRS14 => GND_net, -- tied to '0' from definition
        PRDATAS15  => PRDATAS15_const_net_0, -- tied to X"0" from definition
        PREADYS15  => VCC_net, -- tied to '1' from definition
        PSLVERRS15 => GND_net, -- tied to '0' from definition
        PRDATAS16  => PRDATAS16_const_net_0, -- tied to X"0" from definition
        PREADYS16  => VCC_net, -- tied to '1' from definition
        PSLVERRS16 => GND_net, -- tied to '0' from definition
        IADDR      => IADDR_const_net_0, -- tied to X"0" from definition
        -- Outputs
        PRDATA     => my_mss_top_0_FIC_2_APB_MASTER_PRDATA,
        PREADY     => my_mss_top_0_FIC_2_APB_MASTER_PREADY,
        PSLVERR    => my_mss_top_0_FIC_2_APB_MASTER_PSLVERR,
        PADDRS     => CoreAPB3_0_APBmslave0_PADDR,
        PWRITES    => CoreAPB3_0_APBmslave0_PWRITE,
        PENABLES   => CoreAPB3_0_APBmslave0_PENABLE,
        PWDATAS    => CoreAPB3_0_APBmslave0_PWDATA,
        PSELS0     => CoreAPB3_0_APBmslave0_PSELx,
        PSELS1     => OPEN,
        PSELS2     => OPEN,
        PSELS3     => OPEN,
        PSELS4     => OPEN,
        PSELS5     => OPEN,
        PSELS6     => OPEN,
        PSELS7     => OPEN,
        PSELS8     => OPEN,
        PSELS9     => OPEN,
        PSELS10    => OPEN,
        PSELS11    => OPEN,
        PSELS12    => OPEN,
        PSELS13    => OPEN,
        PSELS14    => OPEN,
        PSELS15    => OPEN,
        PSELS16    => OPEN 
        );
-- my_mss_top_0
my_mss_top_0 : my_mss_top
    port map( 
        -- Inputs
        DEVRST_N            => DEVRST_N,
        FAB_RESET_N         => VCC_net,
        FIC_2_APB_M_PRDATA  => my_mss_top_0_FIC_2_APB_MASTER_PRDATA,
        FIC_2_APB_M_PREADY  => my_mss_top_0_FIC_2_APB_MASTER_PREADY,
        FIC_2_APB_M_PSLVERR => my_mss_top_0_FIC_2_APB_MASTER_PSLVERR,
        -- Outputs
        FIC_0_CLK           => my_mss_top_0_FIC_0_CLK,
        FIC_0_LOCK          => OPEN,
        INIT_DONE           => OPEN,
        MSS_READY           => my_mss_top_0_MSS_READY,
        FIC_2_APB_M_PADDR   => my_mss_top_0_FIC_2_APB_MASTER_PADDR,
        FIC_2_APB_M_PSEL    => my_mss_top_0_FIC_2_APB_MASTER_PSELx,
        FIC_2_APB_M_PENABLE => my_mss_top_0_FIC_2_APB_MASTER_PENABLE,
        FIC_2_APB_M_PWRITE  => my_mss_top_0_FIC_2_APB_MASTER_PWRITE,
        FIC_2_APB_M_PWDATA  => my_mss_top_0_FIC_2_APB_MASTER_PWDATA 
        );
-- RAM_with_wrapper_0
RAM_with_wrapper_0 : RAM_with_wrapper
    port map( 
        -- Inputs
        PCLK    => my_mss_top_0_FIC_0_CLK,
        PRESETN => my_mss_top_0_MSS_READY,
        PADDR   => CoreAPB3_0_APBmslave0_PADDR_0,
        PENABLE => CoreAPB3_0_APBmslave0_PENABLE,
        PWRITE  => CoreAPB3_0_APBmslave0_PWRITE,
        PWDATA  => CoreAPB3_0_APBmslave0_PWDATA_0,
        PSEL    => CoreAPB3_0_APBmslave0_PSELx,
        -- Outputs
        PRDATA  => CoreAPB3_0_APBmslave0_PRDATA,
        PREADY  => CoreAPB3_0_APBmslave0_PREADY,
        PSLVERR => CoreAPB3_0_APBmslave0_PSLVERR 
        );

end RTL;
