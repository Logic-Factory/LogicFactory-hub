from gym.envs.registration import register

register(
    id='genus-v0',
    entry_point='gym_genus.envs:GenusEnv',
)
