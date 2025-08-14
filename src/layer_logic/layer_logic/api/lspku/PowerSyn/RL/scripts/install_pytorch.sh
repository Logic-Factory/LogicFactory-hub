#!/bin/bash

echo "=== 开始安装PyTorch和相关库 ==="

# 加载conda环境配置
source "$(conda info --base)/etc/profile.d/conda.sh"

# 确保环境存在并激活
conda activate rlgym || {
    echo "error: 无法激活rlgym环境"
    exit 1
}

# 1. 安装CUDA版本的PyTorch（强制指定CUDA，避免歧义）
echo "安装PyTorch 1.10.0 + CUDA 11.1"
conda install -y pytorch==1.10.0 torchvision==0.11.0 torchaudio==0.10.0 cudatoolkit=11.1 \
    -c pytorch -c conda-forge  # 优先用pytorch源，conda-forge补充依赖


# 2. 安装gcc（版本保持11.2.0，确保编译兼容性）
conda install -c conda-forge -y gcc=11.2.0 gxx=11.2.0 libgcc-ng=11.2.0 libgomp=11.2.0

# 3. 安装mpi4py
echo "安装mpi4py"
conda install -c conda-forge -y mpi4py

# 最终验证
echo "验证安装结果:"
python -c "import torch; print(f'PyTorch版本: {torch.__version__}'); print(f'CUDA可用: {torch.cuda.is_available()}')"
python -c "import mpi4py; print(f'mpi4py版本: {mpi4py.__version__}')"

echo "=== 安装完成 ==="