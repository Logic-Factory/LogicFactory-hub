import argparse


def get_args():
    """
        Description:
        Parses arguments at command line.
        Parameters:
        None
        Return:
        args - the arguments parsed
    """
    parser = argparse.ArgumentParser()

    parser.add_argument('--model_name', dest='model_name', type=str, default=None)
    parser.add_argument('--test_dir', dest='test_dir', type=str, default=None)
    parser.add_argument('--test_list', dest='test_list', type=str, default=None)
    parser.add_argument('--epoch', dest='epoch', type=int, default=6)
    parser.add_argument('--action_length', dest='action_length', type=int, default=32)
    parser.add_argument('--log', dest='log', type=str, default=None)
    parser.add_argument('--fixed_mode', dest='fixed_mode', type=bool, default=True)
    parser.add_argument('--result_dir', dest='result_dir', type=str, default=None)
    parser.add_argument('--seq_length', dest='seq_length', type=int, default=32)
    parser.add_argument('--result_log', dest='result_log', type=str, default='./test_case/share/test_log.txt')
    parser.add_argument('--converge_length', dest='converge_length', type=int, default=32)
    parser.add_argument('--agent_type', dest='agent_type', type=str, default='PPO')
    parser.add_argument('--initial_t', dest='initial_t', type=float, default=100.0)
    parser.add_argument('--terminate_t', dest='terminate_t', type=float, default=0.01)
    parser.add_argument('--cool_ratio', dest='cool_ratio', type=float, default=0.2)
    parser.add_argument('--feature_mode', dest='feature_mode', type=str, default= None)
    parser.add_argument('--trace_dir', dest='trace_dir', type=str, default=None)
    parser.add_argument('--trace_file', dest='trace_file', type=str, default=None)
    args = parser.parse_args()

    return args
