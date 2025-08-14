# import gym_genus.envs.cmodule as cmodule
import regex
import os

def get_feature(netlist, mode="normal"):
    feature_file = './test_case/share/temp_feature_'+str(os.getpid())+'.txt'
    if mode == "normal":
        cmd = './src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/get_feature '+netlist+' '+ feature_file
        return_value = os.system(cmd)
        assert return_value == 0, "Error in getting feature"
        with open(feature_file, 'r') as file:
            feature = file.readline().strip().split()
        os.remove(feature_file)
        # print(feature)
        return [float(x) for x in feature]
    elif mode == "glitch":
        cmd = './src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/get_feature_glitch '+netlist+' '+ feature_file
        return_value = os.system(cmd)
        assert return_value == 0, "Error in getting feature"
        with open(feature_file, 'r') as file:
            feature = file.readline().strip().split()
        os.remove(feature_file)
        # print(feature)
        return [float(x) for x in feature]
    elif mode == 'basic':
        cmd = './src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/get_feature_basic '+netlist+' '+ feature_file
        return_value = os.system(cmd)
        assert return_value == 0, "Error in getting feature"
        with open(feature_file, 'r') as file:
            feature = file.readline().strip().split()
        os.remove(feature_file)
        # print(feature)
        return [float(x) for x in feature]
    else:
        raise NotImplementedError


# Get power detail from innovus power report
'''
def get_power(file_name):
    total_power = 0.0
    internal_power = 0.0
    switch_power = 0.0
    leakage = 0.0
    with open(file_name) as file:
        for line in file.readlines():
            if line.find("Subtotal") != -1:
                line = line.split()
                leakage = float(line[1])
                internal_power = float(line[2])
                switch_power = float(line[3])
                total_power = float(line[4])
            else:
                continue
        file.close()

    return total_power, internal_power, switch_power, leakage
'''


def technology_mapping(input_file, technology, output_file):
    generate_yosys_script(input_file, output_file, technology, './src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/yosys_script.ys')
    import os
    os.system('yosys -q -s ./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/yosys_script.ys')

def get_power(file_name, liberty_file):
    import os
    os.system('./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/network/get_power '+file_name+' '+liberty_file+' ./test_case/share/temp_power.txt')
    with open('./test_case/share/temp_power.txt', 'r') as file:
        line = file.readline().strip().split()
    os.remove('./test_case/share/temp_power.txt')
    return  float(line[0]), float(line[1]), float(line[2]), float(line[3]), float(line[4])

def generate_yosys_script(in_file, out_file, liberty, script_file, trace_dir=None, num_iter=0):
    with open(script_file, 'w') as file:
        file.write("read_blif " + in_file + "\n")
        file.write("techmap" + "\n")
        file.write("abc -liberty " + liberty + "\n")
        # file.write("abc -liberty " + liberty + " -fast" + "\n")
        file.write("clean\n")
        # file.write("write_verilog " + out_file + "\n")
        # if trace_dir is not None:
        #     file.write("write_blif " + out_file + '_' + str(num_iter) + "\n")
        # file.close()
        file.write("write_blif " + out_file + "\n")
        file.close()
        return


def genus_run_command(genus, cmd):
    genus.stdin.write(cmd)
    genus.stdin.flush()
    trace_line = genus.stdout.readline()
    if trace_line.split() != [] and trace_line.split()[0].find('Error') != -1:
        return 1
    while 'legacy_genus:/>' not in trace_line:
        genus.stdin.flush()
        line = genus.stdout.readline()
        trace_line += line
        # print(line, end='')
        if line.split() != [] and trace_line.split()[0].find('Error') != -1:
            return 1
        assert trace_line.find('Abnormal exit.') == -1
    return 0


def genus_wait_till_respond(genus):
    line = genus.stdout.readline()
    trace_line = line
    while 'legacy_genus:/>' not in trace_line:
        # print(line, end='')
        genus.stdin.flush()
        line += genus.stdout.readline()
        trace_line += line
        assert trace_line.find('Abnormal exit.') == -1
    return


def genus_remove_design(genus):
    assert genus_run_command(genus, "rm designs/* \n") == 0
    return


def genus_read_library(genus, lib_file):
    assert genus_run_command(genus, "set_attribute library " + lib_file + "\n") == 0
    return


def genus_elaborate(genus, design):
    assert genus_run_command(genus, "elaborate " + design + "\n") == 0


def genus_read_hdl(genus, file):
    assert genus_run_command(genus, "read_hdl " + file + "\n") == 0


def genus_report_power(genus, power_file):
    assert genus_run_command(genus, "report power > " + power_file + "\n") == 0

