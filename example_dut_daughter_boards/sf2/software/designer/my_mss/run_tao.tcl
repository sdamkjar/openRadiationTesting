set_family {SmartFusion2}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\Actel\DirectCore\CoreResetP\7.1.100\rtl\vhdl\core\coreresetp_pcie_hotreset.vhd}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\Actel\DirectCore\CoreResetP\7.1.100\rtl\vhdl\core\coreresetp.vhd}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\work\my_mss\FCCC_0\my_mss_FCCC_0_FCCC.vhd}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\work\my_mss_MSS\my_mss_MSS.vhd}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\work\my_mss\OSC_0\my_mss_OSC_0_OSC.vhd}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\work\my_mss\my_mss.vhd}
set_top_level {my_mss}
map_netlist
check_constraints {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\constraint\synthesis_sdc_errors.log}
write_fdc {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\designer\my_mss\synthesis.fdc}
