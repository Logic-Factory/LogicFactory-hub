import gym
from arguments import get_args
from stable_baselines3 import PPO
import copy


def get_action(agent_type, obs=None, model=None, gym_env=None, temperatures=None, iter_info=None):
    if agent_type == 'PPO':
        assert model is not None and obs is not None
        action, _ = model.predict(obs)
        return action
    elif agent_type == 'random':
        assert gym_env is not None
        return gym_env.action_space.sample()
    elif agent_type == 'anneal':
        assert temperatures is not None and gym_env is not None
        env = copy.deepcopy(gym_env)
        action = env.action_space.sample()
        obs, reward, done, info = env.step(env.action_space.sample())
        env.stop()
        temperatures.current_t *= temperatures.cool_ratio
        if reward > 0 or temperatures.current_t >= temperatures.terminate_t:
            return action
        else:
            return -1
    elif agent_type == 'greedy':
        assert gym_env is not None
        best_reward = float('-inf')
        best_action = -1
        for i in range(gym_env.action_space.n):
            env = copy.deepcopy(gym_env)
            obs, reward, done, info = env.step(i)
            if reward > best_reward:
                best_reward = reward
                best_action = i
            env.stop()
        assert best_action != -1
        return best_action
    elif agent_type == 'abc_resyn':
        assert iter_info is not None
        a = [0, 1, 2, 0, 2, 0, 0, 1, 3, 0, 1, 2, 0, 4, 2, 0]
        return a[(iter_info['current_iters'] + iter_info['current_unchanged_iters']) % 16]
    else:
        raise NotImplementedError


def test_done(fixed_mode, iter_infos):
    iter_infos['total_iters'] += 1
    if fixed_mode:
        iter_infos['current_iters'] += 1
        if iter_infos['current_iters'] < iter_infos['max_iters']:
            return False
        else:
            return True
    else:
        if iter_infos['current_reward'] <= 0:
            iter_infos['current_unchanged_iters'] += 1
        else:
            iter_infos['current_unchanged_iters'] = 0
            iter_infos['current_iters'] += 1
        if iter_infos['current_unchanged_iters'] < iter_infos['converge_length']:
            return False
        else:
            return True


def main(arguments):
    if arguments.feature_mode == 'normal':
        obs_dim = 81
    elif arguments.feature_mode == 'glitch':
        obs_dim = 89
    elif arguments.feature_mode == 'basic':
        obs_dim = 14
    else:
        raise NotImplementedError
    fixed_mode = arguments.fixed_mode
    result_dir = arguments.result_dir
    result_log = arguments.result_log
    model = arguments.model_name
    test_dir = arguments.test_dir
    test_list = arguments.test_list
    seq_length = arguments.seq_length
    converge_length = arguments.converge_length
    temperatures = {'current_t': arguments.initial_t, 'terminate_t': arguments.terminate_t,
                    'cool_ratio': arguments.cool_ratio}

    env = gym.make('gym_genus:genus-v0', 
                   lib_file="./src/layer_logic/layer_logic/api/lspku/PowerSyn/RL/sources/PowerAwareSynthesis/netlist/gsc145nm.lib",
                   feature_mode=args.feature_mode, 
                   obs_dim=obs_dim)
    model = PPO.load(model, device='cpu') if arguments.agent_type == 'PPO' else None
    
    with open(test_list, 'r') as file:
        for line in file.readlines():
            with open(result_log, 'a') as result:
                env.setup(test_dir + '/' + line)
                result.write(line + "\n")
                obs, info = env.reset(return_info=True)
                info_str = ""
                for _ in info.values():
                    info_str += str(_) + " "
                result.write(info_str)
                result.write('\n')
                iter_infos = {'current_iters': 0, 'converge_length': converge_length, 'max_iters': seq_length,
                              'current_reward': 0, 'current_unchanged_iters': 0, 'total_iters': 0}
                while True:
                    action = get_action(arguments.agent_type, obs=obs, model=model, gym_env=env,
                                        temperatures=temperatures, iter_info=iter_infos)
                    #print(action)
                    if action == -1:
                        continue
                    obs, reward, done, info = env.step(action, arguments.trace_dir, iter_infos['total_iters'])
                    if arguments.trace_file is not None:
                        with open(arguments.trace_file, 'a') as trace:
                            info_str = ""
                            for _ in info.values():
                                info_str += str(_) + " "
                            trace.write(str(iter_infos['total_iters'])+" "+str(iter_infos['current_iters'])+" "+info_str+"\n")
                            trace.close()
                    iter_infos['current_reward'] = reward
                    if test_done(fixed_mode, iter_infos):
                        break
                    print(iter_infos['current_iters'])
                info_str = ""
                for _ in info.values():
                    info_str += str(_) + " "
                result.write(info_str)
                result.write('\n')
                result.write('seq_length: ' + str(iter_infos['current_iters']))
                result.write('\n')
                if result_dir != "":
                    env.write(result_dir + '/' + line)
                env.stop()
                result.close()
        file.close()


if __name__ == '__main__':
    args = get_args()  # Parse arguments from command line
    main(args)
