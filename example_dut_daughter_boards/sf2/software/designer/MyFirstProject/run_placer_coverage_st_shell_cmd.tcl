read_sdc -scenario "place_and_route" -netlist "user" -pin_separator "/" -ignore_errors {C:/Users/sdamkjar/Documents/albertasat/TRIUMF/Software/SMARTFUSION2_TEST/MyFirstProject/designer/MyFirstProject/place_route.sdc}
set_options -tdpr_scenario "place_and_route" 
save
set_options -analysis_scenario "place_and_route"
set coverage [report \
    -type     constraints_coverage \
    -format   xml \
    -slacks   no \
    {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\designer\MyFirstProject\MyFirstProject_place_and_route_constraint_coverage.xml}]
set reportfile {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\designer\MyFirstProject\coverage_placeandroute}
set fp [open $reportfile w]
puts $fp $coverage
close $fp
