set_component my_mss_MSS
# Microsemi Corp.
# Date: 2018-Sep-20 14:31:14
#

create_clock -period 40 [ get_pins { MSS_ADLIB_INST/CLK_CONFIG_APB } ]
set_false_path -ignore_errors -through [ get_pins { MSS_ADLIB_INST/CONFIG_PRESET_N } ]
