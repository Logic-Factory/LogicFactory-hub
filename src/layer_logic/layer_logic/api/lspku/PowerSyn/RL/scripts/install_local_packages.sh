#!/bin/bash

echo "=== 开始安装本地包（可编辑模式）==="

# 确保在Conda环境中
source "$(conda info --base)/etc/profile.d/conda.sh"
conda activate rlgym || {
    echo "error: 无法激活rlgym环境"
    exit 1
}

cd ./sources/PowerAwareSynthesis/gym-genus
pip install -e .  # 可编辑模式安装
cd - > /dev/null

cd ./sources/PowerAwareSynthesis/netlist/abc/
make clean
make ABC_USE_PIC=1 ABC_USE_NO_READLINE=1 libabc.so -j12
cd - > /dev/null


cd ./sources/PowerAwareSynthesis/netlist/abc/ABC-python
LIBABC_PATH=$(readlink -f ../libabc.so)
swig -python ABC.i
gcc -fPIC $(python3-config --includes) \
  -I /usr/include \
  -I /usr/include/x86_64-linux-gnu \
  -I $(dirname "$LIBABC_PATH")/src \
  ABC_wrap.c -c -o ABC_wrap.o

g++ -shared -fPIC -o _ABC.so ABC_wrap.o "$LIBABC_PATH"
pip install .
cp -f ABC.py /opt/conda/envs/rlgym/lib/python3.7/site-packages/
cp -f _ABC.so /opt/conda/envs/rlgym/lib/python3.7/site-packages/
cd - > /dev/null


conda deactivate

cd ./sources/PowerAwareSynthesis/netlist/yosys
make clean || true
make config-gcc
make -j12
make install

if ! echo "$PATH" | grep -q "/usr/local/bin"; then
    echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.bashrc
    source ~/.bashrc
else
    echo "/usr/local/bin 已在 PATH 中，无需重复添加"
fi
yosys --version
cd - > /dev/null


echo "=== 本地包安装完成（可编辑模式）==="