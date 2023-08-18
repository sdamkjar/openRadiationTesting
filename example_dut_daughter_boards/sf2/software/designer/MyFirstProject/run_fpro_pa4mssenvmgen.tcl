set_device \
    -fam SmartFusion2 \
    -die PA4M1000_N \
    -pkg tq144
set_input_cfg \
	-path {C:/Users/sdamkjar/Documents/albertasat/TRIUMF/Software/SMARTFUSION2_TEST/MyFirstProject/component/work/MyFirstProject_MSS/ENVM.cfg}
set_output_efc \
    -path {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject\designer\MyFirstProject\MyFirstProject.efc}
set_proj_dir \
    -path {C:\Users\sdamkjar\Documents\albertasat\TRIUMF\Software\SMARTFUSION2_TEST\MyFirstProject}
gen_prg -use_init false
