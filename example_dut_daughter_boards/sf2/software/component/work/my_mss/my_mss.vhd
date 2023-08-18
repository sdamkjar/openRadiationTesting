----------------------------------------------------------------------
-- Created by SmartDesign Thu Sep 20 14:32:32 2018
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
-- my_mss entity declaration
----------------------------------------------------------------------
entity my_mss is
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
end my_mss;
----------------------------------------------------------------------
-- my_mss architecture body
----------------------------------------------------------------------
architecture RTL of my_mss is
----------------------------------------------------------------------
-- Component declarations
----------------------------------------------------------------------
-- CoreResetP   -   Actel:DirectCore:CoreResetP:7.1.100
component CoreResetP
    generic( 
        DDR_WAIT            : integer := 200 ;
        DEVICE_090          : integer := 0 ;
        DEVICE_VOLTAGE      : integer := 2 ;
        ENABLE_SOFT_RESETS  : integer := 0 ;
        EXT_RESET_CFG       : integer := 0 ;
        FDDR_IN_USE         : integer := 0 ;
        MDDR_IN_USE         : integer := 0 ;
        SDIF0_IN_USE        : integer := 0 ;
        SDIF0_PCIE          : integer := 0 ;
        SDIF0_PCIE_HOTRESET : integer := 1 ;
        SDIF0_PCIE_L2P2     : integer := 1 ;
        SDIF1_IN_USE        : integer := 0 ;
        SDIF1_PCIE          : integer := 0 ;
        SDIF1_PCIE_HOTRESET : integer := 1 ;
        SDIF1_PCIE_L2P2     : integer := 1 ;
        SDIF2_IN_USE        : integer := 0 ;
        SDIF2_PCIE          : integer := 0 ;
        SDIF2_PCIE_HOTRESET : integer := 1 ;
        SDIF2_PCIE_L2P2     : integer := 1 ;
        SDIF3_IN_USE        : integer := 0 ;
        SDIF3_PCIE          : integer := 0 ;
        SDIF3_PCIE_HOTRESET : integer := 1 ;
        SDIF3_PCIE_L2P2     : integer := 1 
        );
    -- Port list
    port(
        -- Inputs
        CLK_BASE                       : in  std_logic;
        CLK_LTSSM                      : in  std_logic;
        CONFIG1_DONE                   : in  std_logic;
        CONFIG2_DONE                   : in  std_logic;
        FAB_RESET_N                    : in  std_logic;
        FIC_2_APB_M_PRESET_N           : in  std_logic;
        FPLL_LOCK                      : in  std_logic;
        POWER_ON_RESET_N               : in  std_logic;
        RCOSC_25_50MHZ                 : in  std_logic;
        RESET_N_M2F                    : in  std_logic;
        SDIF0_PERST_N                  : in  std_logic;
        SDIF0_PRDATA                   : in  std_logic_vector(31 downto 0);
        SDIF0_PSEL                     : in  std_logic;
        SDIF0_PWRITE                   : in  std_logic;
        SDIF0_SPLL_LOCK                : in  std_logic;
        SDIF1_PERST_N                  : in  std_logic;
        SDIF1_PRDATA                   : in  std_logic_vector(31 downto 0);
        SDIF1_PSEL                     : in  std_logic;
        SDIF1_PWRITE                   : in  std_logic;
        SDIF1_SPLL_LOCK                : in  std_logic;
        SDIF2_PERST_N                  : in  std_logic;
        SDIF2_PRDATA                   : in  std_logic_vector(31 downto 0);
        SDIF2_PSEL                     : in  std_logic;
        SDIF2_PWRITE                   : in  std_logic;
        SDIF2_SPLL_LOCK                : in  std_logic;
        SDIF3_PERST_N                  : in  std_logic;
        SDIF3_PRDATA                   : in  std_logic_vector(31 downto 0);
        SDIF3_PSEL                     : in  std_logic;
        SDIF3_PWRITE                   : in  std_logic;
        SDIF3_SPLL_LOCK                : in  std_logic;
        SOFT_EXT_RESET_OUT             : in  std_logic;
        SOFT_FDDR_CORE_RESET           : in  std_logic;
        SOFT_M3_RESET                  : in  std_logic;
        SOFT_MDDR_DDR_AXI_S_CORE_RESET : in  std_logic;
        SOFT_RESET_F2M                 : in  std_logic;
        SOFT_SDIF0_0_CORE_RESET        : in  std_logic;
        SOFT_SDIF0_1_CORE_RESET        : in  std_logic;
        SOFT_SDIF0_CORE_RESET          : in  std_logic;
        SOFT_SDIF0_PHY_RESET           : in  std_logic;
        SOFT_SDIF1_CORE_RESET          : in  std_logic;
        SOFT_SDIF1_PHY_RESET           : in  std_logic;
        SOFT_SDIF2_CORE_RESET          : in  std_logic;
        SOFT_SDIF2_PHY_RESET           : in  std_logic;
        SOFT_SDIF3_CORE_RESET          : in  std_logic;
        SOFT_SDIF3_PHY_RESET           : in  std_logic;
        -- Outputs
        DDR_READY                      : out std_logic;
        EXT_RESET_OUT                  : out std_logic;
        FDDR_CORE_RESET_N              : out std_logic;
        INIT_DONE                      : out std_logic;
        M3_RESET_N                     : out std_logic;
        MDDR_DDR_AXI_S_CORE_RESET_N    : out std_logic;
        MSS_HPMS_READY                 : out std_logic;
        RESET_N_F2M                    : out std_logic;
        SDIF0_0_CORE_RESET_N           : out std_logic;
        SDIF0_1_CORE_RESET_N           : out std_logic;
        SDIF0_CORE_RESET_N             : out std_logic;
        SDIF0_PHY_RESET_N              : out std_logic;
        SDIF1_CORE_RESET_N             : out std_logic;
        SDIF1_PHY_RESET_N              : out std_logic;
        SDIF2_CORE_RESET_N             : out std_logic;
        SDIF2_PHY_RESET_N              : out std_logic;
        SDIF3_CORE_RESET_N             : out std_logic;
        SDIF3_PHY_RESET_N              : out std_logic;
        SDIF_READY                     : out std_logic;
        SDIF_RELEASED                  : out std_logic
        );
end component;
-- my_mss_FCCC_0_FCCC   -   Actel:SgCore:FCCC:2.0.201
component my_mss_FCCC_0_FCCC
    -- Port list
    port(
        -- Inputs
        RCOSC_25_50MHZ : in  std_logic;
        -- Outputs
        GL0            : out std_logic;
        LOCK           : out std_logic
        );
end component;
-- my_mss_MSS
component my_mss_MSS
    -- Port list
    port(
        -- Inputs
        FIC_2_APB_M_PRDATA     : in  std_logic_vector(31 downto 0);
        FIC_2_APB_M_PREADY     : in  std_logic;
        FIC_2_APB_M_PSLVERR    : in  std_logic;
        MCCC_CLK_BASE          : in  std_logic;
        MCCC_CLK_BASE_PLL_LOCK : in  std_logic;
        MSS_RESET_N_F2M        : in  std_logic;
        -- Outputs
        FIC_2_APB_M_PADDR      : out std_logic_vector(15 downto 2);
        FIC_2_APB_M_PCLK       : out std_logic;
        FIC_2_APB_M_PENABLE    : out std_logic;
        FIC_2_APB_M_PRESET_N   : out std_logic;
        FIC_2_APB_M_PSEL       : out std_logic;
        FIC_2_APB_M_PWDATA     : out std_logic_vector(31 downto 0);
        FIC_2_APB_M_PWRITE     : out std_logic;
        MSS_RESET_N_M2F        : out std_logic
        );
end component;
-- my_mss_OSC_0_OSC   -   Actel:SgCore:OSC:2.0.101
component my_mss_OSC_0_OSC
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
signal CoreResetP_0_RESET_N_F2M                        : std_logic;
signal FIC_0_CLK_0                                     : std_logic;
signal FIC_0_LOCK_net_0                                : std_logic;
signal FIC_2_APB_MASTER_0_PADDR                        : std_logic_vector(15 downto 2);
signal FIC_2_APB_MASTER_0_PENABLE                      : std_logic;
signal FIC_2_APB_MASTER_0_PSELx                        : std_logic;
signal FIC_2_APB_MASTER_0_PWDATA                       : std_logic_vector(31 downto 0);
signal FIC_2_APB_MASTER_0_PWRITE                       : std_logic;
signal INIT_DONE_net_0                                 : std_logic;
signal MSS_READY_net_0                                 : std_logic;
signal my_mss_MSS_0_FIC_2_APB_M_PRESET_N               : std_logic;
signal my_mss_MSS_0_MSS_RESET_N_M2F                    : std_logic;
signal OSC_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC : std_logic;
signal OSC_0_RCOSC_25_50MHZ_O2F                        : std_logic;
signal POWER_ON_RESET_N                                : std_logic;
signal FIC_0_CLK_0_net_0                               : std_logic;
signal FIC_0_LOCK_net_1                                : std_logic;
signal MSS_READY_net_1                                 : std_logic;
signal INIT_DONE_net_1                                 : std_logic;
signal FIC_2_APB_MASTER_0_PADDR_net_0                  : std_logic_vector(15 downto 2);
signal FIC_2_APB_MASTER_0_PSELx_net_0                  : std_logic;
signal FIC_2_APB_MASTER_0_PENABLE_net_0                : std_logic;
signal FIC_2_APB_MASTER_0_PWRITE_net_0                 : std_logic;
signal FIC_2_APB_MASTER_0_PWDATA_net_0                 : std_logic_vector(31 downto 0);
----------------------------------------------------------------------
-- TiedOff Signals
----------------------------------------------------------------------
signal VCC_net                                         : std_logic;
signal GND_net                                         : std_logic;
signal SDIF0_PRDATA_const_net_0                        : std_logic_vector(31 downto 0);
signal SDIF1_PRDATA_const_net_0                        : std_logic_vector(31 downto 0);
signal SDIF2_PRDATA_const_net_0                        : std_logic_vector(31 downto 0);
signal SDIF3_PRDATA_const_net_0                        : std_logic_vector(31 downto 0);
signal PADDR_const_net_0                               : std_logic_vector(7 downto 2);
signal PWDATA_const_net_0                              : std_logic_vector(7 downto 0);

begin
----------------------------------------------------------------------
-- Constant assignments
----------------------------------------------------------------------
 VCC_net                  <= '1';
 GND_net                  <= '0';
 SDIF0_PRDATA_const_net_0 <= B"00000000000000000000000000000000";
 SDIF1_PRDATA_const_net_0 <= B"00000000000000000000000000000000";
 SDIF2_PRDATA_const_net_0 <= B"00000000000000000000000000000000";
 SDIF3_PRDATA_const_net_0 <= B"00000000000000000000000000000000";
 PADDR_const_net_0        <= B"000000";
 PWDATA_const_net_0       <= B"00000000";
----------------------------------------------------------------------
-- Top level output port assignments
----------------------------------------------------------------------
 FIC_0_CLK_0_net_0                <= FIC_0_CLK_0;
 FIC_0_CLK                        <= FIC_0_CLK_0_net_0;
 FIC_0_LOCK_net_1                 <= FIC_0_LOCK_net_0;
 FIC_0_LOCK                       <= FIC_0_LOCK_net_1;
 MSS_READY_net_1                  <= MSS_READY_net_0;
 MSS_READY                        <= MSS_READY_net_1;
 INIT_DONE_net_1                  <= INIT_DONE_net_0;
 INIT_DONE                        <= INIT_DONE_net_1;
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
-- CoreResetP_0   -   Actel:DirectCore:CoreResetP:7.1.100
CoreResetP_0 : CoreResetP
    generic map( 
        DDR_WAIT            => ( 200 ),
        DEVICE_090          => ( 0 ),
        DEVICE_VOLTAGE      => ( 2 ),
        ENABLE_SOFT_RESETS  => ( 0 ),
        EXT_RESET_CFG       => ( 0 ),
        FDDR_IN_USE         => ( 0 ),
        MDDR_IN_USE         => ( 0 ),
        SDIF0_IN_USE        => ( 0 ),
        SDIF0_PCIE          => ( 0 ),
        SDIF0_PCIE_HOTRESET => ( 1 ),
        SDIF0_PCIE_L2P2     => ( 1 ),
        SDIF1_IN_USE        => ( 0 ),
        SDIF1_PCIE          => ( 0 ),
        SDIF1_PCIE_HOTRESET => ( 1 ),
        SDIF1_PCIE_L2P2     => ( 1 ),
        SDIF2_IN_USE        => ( 0 ),
        SDIF2_PCIE          => ( 0 ),
        SDIF2_PCIE_HOTRESET => ( 1 ),
        SDIF2_PCIE_L2P2     => ( 1 ),
        SDIF3_IN_USE        => ( 0 ),
        SDIF3_PCIE          => ( 0 ),
        SDIF3_PCIE_HOTRESET => ( 1 ),
        SDIF3_PCIE_L2P2     => ( 1 )
        )
    port map( 
        -- Inputs
        RESET_N_M2F                    => my_mss_MSS_0_MSS_RESET_N_M2F,
        FIC_2_APB_M_PRESET_N           => my_mss_MSS_0_FIC_2_APB_M_PRESET_N,
        POWER_ON_RESET_N               => POWER_ON_RESET_N,
        FAB_RESET_N                    => FAB_RESET_N,
        RCOSC_25_50MHZ                 => OSC_0_RCOSC_25_50MHZ_O2F,
        CLK_BASE                       => FIC_0_CLK_0,
        CLK_LTSSM                      => GND_net, -- tied to '0' from definition
        FPLL_LOCK                      => VCC_net, -- tied to '1' from definition
        SDIF0_SPLL_LOCK                => VCC_net, -- tied to '1' from definition
        SDIF1_SPLL_LOCK                => VCC_net, -- tied to '1' from definition
        SDIF2_SPLL_LOCK                => VCC_net, -- tied to '1' from definition
        SDIF3_SPLL_LOCK                => VCC_net, -- tied to '1' from definition
        CONFIG1_DONE                   => VCC_net,
        CONFIG2_DONE                   => VCC_net,
        SDIF0_PERST_N                  => VCC_net, -- tied to '1' from definition
        SDIF1_PERST_N                  => VCC_net, -- tied to '1' from definition
        SDIF2_PERST_N                  => VCC_net, -- tied to '1' from definition
        SDIF3_PERST_N                  => VCC_net, -- tied to '1' from definition
        SDIF0_PSEL                     => GND_net, -- tied to '0' from definition
        SDIF0_PWRITE                   => VCC_net, -- tied to '1' from definition
        SDIF1_PSEL                     => GND_net, -- tied to '0' from definition
        SDIF1_PWRITE                   => VCC_net, -- tied to '1' from definition
        SDIF2_PSEL                     => GND_net, -- tied to '0' from definition
        SDIF2_PWRITE                   => VCC_net, -- tied to '1' from definition
        SDIF3_PSEL                     => GND_net, -- tied to '0' from definition
        SDIF3_PWRITE                   => VCC_net, -- tied to '1' from definition
        SOFT_EXT_RESET_OUT             => GND_net, -- tied to '0' from definition
        SOFT_RESET_F2M                 => GND_net, -- tied to '0' from definition
        SOFT_M3_RESET                  => GND_net, -- tied to '0' from definition
        SOFT_MDDR_DDR_AXI_S_CORE_RESET => GND_net, -- tied to '0' from definition
        SOFT_FDDR_CORE_RESET           => GND_net, -- tied to '0' from definition
        SOFT_SDIF0_PHY_RESET           => GND_net, -- tied to '0' from definition
        SOFT_SDIF0_CORE_RESET          => GND_net, -- tied to '0' from definition
        SOFT_SDIF0_0_CORE_RESET        => GND_net, -- tied to '0' from definition
        SOFT_SDIF0_1_CORE_RESET        => GND_net, -- tied to '0' from definition
        SOFT_SDIF1_PHY_RESET           => GND_net, -- tied to '0' from definition
        SOFT_SDIF1_CORE_RESET          => GND_net, -- tied to '0' from definition
        SOFT_SDIF2_PHY_RESET           => GND_net, -- tied to '0' from definition
        SOFT_SDIF2_CORE_RESET          => GND_net, -- tied to '0' from definition
        SOFT_SDIF3_PHY_RESET           => GND_net, -- tied to '0' from definition
        SOFT_SDIF3_CORE_RESET          => GND_net, -- tied to '0' from definition
        SDIF0_PRDATA                   => SDIF0_PRDATA_const_net_0, -- tied to X"0" from definition
        SDIF1_PRDATA                   => SDIF1_PRDATA_const_net_0, -- tied to X"0" from definition
        SDIF2_PRDATA                   => SDIF2_PRDATA_const_net_0, -- tied to X"0" from definition
        SDIF3_PRDATA                   => SDIF3_PRDATA_const_net_0, -- tied to X"0" from definition
        -- Outputs
        MSS_HPMS_READY                 => MSS_READY_net_0,
        DDR_READY                      => OPEN,
        SDIF_READY                     => OPEN,
        RESET_N_F2M                    => CoreResetP_0_RESET_N_F2M,
        M3_RESET_N                     => OPEN,
        EXT_RESET_OUT                  => OPEN,
        MDDR_DDR_AXI_S_CORE_RESET_N    => OPEN,
        FDDR_CORE_RESET_N              => OPEN,
        SDIF0_CORE_RESET_N             => OPEN,
        SDIF0_0_CORE_RESET_N           => OPEN,
        SDIF0_1_CORE_RESET_N           => OPEN,
        SDIF0_PHY_RESET_N              => OPEN,
        SDIF1_CORE_RESET_N             => OPEN,
        SDIF1_PHY_RESET_N              => OPEN,
        SDIF2_CORE_RESET_N             => OPEN,
        SDIF2_PHY_RESET_N              => OPEN,
        SDIF3_CORE_RESET_N             => OPEN,
        SDIF3_PHY_RESET_N              => OPEN,
        SDIF_RELEASED                  => OPEN,
        INIT_DONE                      => INIT_DONE_net_0 
        );
-- FCCC_0   -   Actel:SgCore:FCCC:2.0.201
FCCC_0 : my_mss_FCCC_0_FCCC
    port map( 
        -- Inputs
        RCOSC_25_50MHZ => OSC_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC,
        -- Outputs
        GL0            => FIC_0_CLK_0,
        LOCK           => FIC_0_LOCK_net_0 
        );
-- my_mss_MSS_0
my_mss_MSS_0 : my_mss_MSS
    port map( 
        -- Inputs
        MCCC_CLK_BASE          => FIC_0_CLK_0,
        MSS_RESET_N_F2M        => CoreResetP_0_RESET_N_F2M,
        MCCC_CLK_BASE_PLL_LOCK => FIC_0_LOCK_net_0,
        FIC_2_APB_M_PRDATA     => FIC_2_APB_M_PRDATA,
        FIC_2_APB_M_PREADY     => FIC_2_APB_M_PREADY,
        FIC_2_APB_M_PSLVERR    => FIC_2_APB_M_PSLVERR,
        -- Outputs
        MSS_RESET_N_M2F        => my_mss_MSS_0_MSS_RESET_N_M2F,
        FIC_2_APB_M_PRESET_N   => my_mss_MSS_0_FIC_2_APB_M_PRESET_N,
        FIC_2_APB_M_PCLK       => OPEN,
        FIC_2_APB_M_PADDR      => FIC_2_APB_MASTER_0_PADDR,
        FIC_2_APB_M_PWDATA     => FIC_2_APB_MASTER_0_PWDATA,
        FIC_2_APB_M_PWRITE     => FIC_2_APB_MASTER_0_PWRITE,
        FIC_2_APB_M_PENABLE    => FIC_2_APB_MASTER_0_PENABLE,
        FIC_2_APB_M_PSEL       => FIC_2_APB_MASTER_0_PSELx 
        );
-- OSC_0   -   Actel:SgCore:OSC:2.0.101
OSC_0 : my_mss_OSC_0_OSC
    port map( 
        -- Inputs
        XTL                => GND_net, -- tied to '0' from definition
        -- Outputs
        RCOSC_25_50MHZ_CCC => OSC_0_RCOSC_25_50MHZ_CCC_OUT_RCOSC_25_50MHZ_CCC,
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
        POWER_ON_RESET_N => POWER_ON_RESET_N 
        );

end RTL;
