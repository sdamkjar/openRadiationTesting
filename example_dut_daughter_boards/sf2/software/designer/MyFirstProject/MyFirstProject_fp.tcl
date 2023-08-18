new_project \
         -name {MyFirstProject} \
         -location {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\designer\MyFirstProject\MyFirstProject_fp} \
         -mode {chain} \
         -connect_programmers {FALSE}
add_actel_device \
         -device {M2S010} \
         -name {M2S010}
enable_device \
         -name {M2S010} \
         -enable {TRUE}
save_project
close_project
