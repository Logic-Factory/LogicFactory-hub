# 使用说明

## 前置条件
- 已安装 anaconda3
- 已安装 yosys

## 操作步骤
1. 进入项目目录
   ```bash
   cd logicfactory_tool/PowerSyn/RL
   ```

2. 编译
   ```bash
   make
   ```

3. 激活环境
   ```bash
   conda activate rlgym
   ```

4. 进入网络目录
   ```bash
   cd logicfactory_tool/PowerSyn/RL/sources/PowerAwareSynthesis/network
   ```

5. 训练模型
   ```bash
   python train.py (--arg,详见logicfactory_tool/PowerSyn/RL/sources/PowerAwareSynthesis/network/arguments.py)
   ```

6. 测试模型
   ```bash
   python test.py (--arg,详见logicfactory_tool/PowerSyn/RL/sources/PowerAwareSynthesis/network/arguments.py)
   ```