read_verilog /rshome/sunan.zou/nas/PowerAwareSynthesis/benchmarks/test_set/sqrt.v
synth
techmap
abc -liberty /rshome/sunan.zou/nas/PowerAwareSynthesis/netlist/compatible_gscl45nm.lib
clean
write_verilog /rshome/sunan.zou/dc_example/sqrt.v
