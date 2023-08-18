open_project -project {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\designer\MyFirstProject\MyFirstProject_fp\MyFirstProject.pro}
set_programming_file -name {M2S010} -file {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\designer\MyFirstProject\MyFirstProject.ipd}
enable_device -name {M2S010} -enable 1
set_programming_action -action {PROGRAM} -name {M2S010} 
run_selected_actions
set_programming_file -name {M2S010} -no_file
save_project
close_project
