#!/bin/bash

echo "=== 开始创建Conda环境 ==="

# 检查conda是否安装
if ! command -v conda &> /dev/null; then
    echo "error: Conda未安装。请先安装Anaconda或Miniconda。"
    exit 1
fi


# 创建Conda环境（如果不存在）
if ! conda env list | grep -q "rlgym"; then
    echo "创建Conda环境: rlgym"
    conda env create -f ./gym.yml -n rlgym
fi

# 初始化conda
source "$(conda info --base)/etc/profile.d/conda.sh"

# 激活环境
conda activate rlgym || {
    echo "error: 无法激活rlgym环境，尝试重新创建"
    conda env remove -n rlgym --yes
    conda env create -f ./gym.yml -n rlgym
    conda activate rlgym
}



echo "=== Conda环境设置完成 ==="