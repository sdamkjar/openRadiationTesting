set_family {SmartFusion2}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\hdl\MyCounter.vhd}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\work\MyFirstProject_MSS\MyFirstProject_MSS.vhd}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\work\MyFirstProject\OSC_0\MyFirstProject_OSC_0_OSC.vhd}
read_vhdl -mode vhdl_2008 {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\component\work\MyFirstProject\MyFirstProject.vhd}
set_top_level {MyFirstProject}
map_netlist
check_constraints {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\constraint\synthesis_sdc_errors.log}
write_fdc {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\designer\MyFirstProject\synthesis.fdc}
