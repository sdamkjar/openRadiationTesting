set_component my_mss_OSC_0_OSC
# Microsemi Corp.
# Date: 2018-Sep-20 14:32:32
#

create_clock -ignore_errors -period 20 [ get_pins { I_RCOSC_25_50MHZ/CLKOUT } ]
