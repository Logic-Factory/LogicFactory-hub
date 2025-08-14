import fcntl
import os
import time
import gym
import shutil
import numpy as np
from gym import spaces
from gym import utils
import subprocess
from ABC import *
from .utils import *


class GenusEnv(gym.Env, utils.EzPickle):
    def __init__(self, lib_file, obs_dim=81, action_dim=18, history_size=6, feature_mode="normal"):
        super().__init__()
        self.history_size = history_size
        self.abc = None
        self.observation = None
        self.reward = 0
        self.done = False
        self.info = None
        self.size = 0
        self.depth = 0
        self.power = 0
        self.edge = 0
        self.file_path = None
        self.file_name = None
        self.obs_dim = obs_dim
        self.quotient_1 = 3
        # self.quotient_2 = 0
        self.quotient_2 = 4
        self.history_action = [-1 for _ in range(history_size)]
        self.history_reward = [2 for _ in range(history_size)]
        self.action_space = spaces.Discrete(action_dim)
        self.log_file = './test_case/share/log_file'
        self.lib_file = lib_file
        self.feature_mode = feature_mode
        self.actions = {
            0: 'balance',
            1: 'rewrite',
            2: 'rewrite -z',
            3: 'refactor',
            4: 'refactor -z',
            5: 'balance -l',
            6: 'rewrite -l',
            7: 'rewrite -z -l',
            8: 'refactor -l ',
            9: 'refactor -z -l',
            10: 'resub',
            11: 'resub -z',
            12: 'dc2',
            13: 'dc2 -p',
            14: 'dc2 -b',
            15: 'strash',
            16: 'strash',
            17: 'strash',
            # 15: 'iresyn',
            # 16: 'irewrite',
            # 17: 'irewrite -z',
            18: 'resyn',
            19: 'resyn2'
        }
        self.observation_space = spaces.Box(
            low=np.array([0 for _ in range(obs_dim + 1)] + [-1 for _ in range(history_size * 2)]),
            high=np.array([0x7fffffff for _ in range(obs_dim + 1)] + [10 for _ in range(history_size * 2)]),
            dtype=np.float64)

        self.seq_length = 0

    def stop(self):
        abc_end(self.abc)

    def step(self, action, trace_dir=None, num_iter=0):
        self.info, result_file = self.run_command(self.actions[action], trace_dir, num_iter)
        [size, depth, power] = list(self.info.values())[:3]
        reward = ((self.size - size) / self.size + self.quotient_1 * (
                self.depth - depth) / self.depth + self.quotient_2 * (self.power - power) / self.power) * 10
        t1 = time.clock()
        # obs = [random.random() for _ in range(self.obs_dim)]
        obs = get_feature(result_file, self.feature_mode)
        t2 = time.clock()
        # print('feature time is :%s ms' % ((t2 - t1) * 1000))
        obs.append(self.seq_length)
        obs += self.history_action + self.history_reward
        self.history_action.pop(0)
        self.history_action.append(int(action))
        self.history_reward.pop(0)
        if reward == 0:
            self.history_reward.append(0)
        elif reward < 0:
            self.history_reward.append(-1)
            # reward = reward - self.seq_length
        else:
            self.history_reward.append(1)
            reward = reward * pow(0.95, self.seq_length)
            if reward < 1e-7:
                reward = 0
        self.seq_length += 1
        self.size = size
        self.depth = depth
        self.power = power
        with open(self.log_file, 'a') as f:
            f.write(str(action))
            f.write(" ")
            f.write(str(size))
            f.write(" ")
            f.write(str(depth))
            f.write(" ")
            f.write(str(power))
            f.write(" ")
            f.write(str(reward))
            f.write("\n")
            f.close()
        return np.array(obs), reward, self.done, self.info

    def setup(self, filename):
        if self.abc is not None:
            abc_end(self.abc)
        self.abc = abc_start()
        self.file_path = filename
        self.file_name = os.path.basename(filename).split('.')[0]
        abc_read(self.abc, self.file_path)
        self.info, _ = self.run_command('strash')
        [self.size, self.depth, self.power] = list(self.info.values())[:3]

    def reset(self, return_info=False):
        if self.abc is not None:
            abc_end(self.abc)
        self.abc = abc_start()
        abc_read(self.abc, self.file_path)
        info, result_file = self.run_command('strash ')
        [self.size, self.depth, self.power] = list(info.values())[:3]
        self.info = [self.size, self.depth, self.power]
        #obs = [random.random() for _ in range(self.obs_dim)]
        obs = get_feature(result_file, self.feature_mode)

        self.seq_length = 0
        obs.append(self.seq_length)
        self.history_action = [-1 for _ in range(self.history_size)]
        self.history_reward = [2 for _ in range(self.history_size)]
        obs += self.history_action + self.history_reward
        if return_info:
            return np.array(obs), info
        else:
            return np.array(obs)

    def write(self, output=None, write_format="blif"):
        output = self.file_path if output is None else output
        abc_write(self.abc, write_format, output)
        # NOTE: find some way to make sure os finished writing

    def run_command(self, cmd, trace_dir=None, num_iter=0):
        t1 = time.clock()
        abc_synthesis(self.abc, cmd)
        t2 = time.clock()
        #print('abc time is :%s ms' % ((t2 - t1) * 1000))
        line = print_state(self.abc)[1]
        tokens = regex.compile('[ =\n\r]+').split(line)
        size_index = tokens.index('and') + 1
        size = int(tokens[size_index])
        depth_index = tokens.index('lev') + 1
        depth = int(tokens[depth_index])

        post_syn_file = "./test_case/share/PAS_syn_" + self.file_name + str(os.getpid())
        t1 = time.clock()
        abc_write(self.abc, "verilog", post_syn_file + ".v")
        abc_write(self.abc, "blif", post_syn_file + ".blif")
        t2 = time.clock()
        #print('abc write_file is :%s ms' % ((t2 - t1) * 1000))

        post_map_file = "./test_case/share/PAS_map_" + self.file_name + str(os.getpid())
        technology_mapping(post_syn_file + ".blif", self.lib_file, post_map_file)
        # print(post_map_file, self.lib_file)
        leakage, switch, internal, wire, power = get_power(post_map_file, self.lib_file)
        os.remove(post_syn_file + ".v")
        os.remove(post_map_file)

        return {"size": size, "depth": depth, "power": power, "internal": internal, "switch": switch,
                "leakage": leakage}, post_syn_file + ".blif"

