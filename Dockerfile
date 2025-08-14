FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Shanghai

# 替换为阿里云镜像源
RUN sed -i 's/archive.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list && \
    sed -i 's/security.ubuntu.com/mirrors.aliyun.com/g' /etc/apt/sources.list

RUN apt-get update && apt-get upgrade -y --no-install-recommends apt-utils

# build essential
RUN apt-get install -y \
    software-properties-common \
    build-essential \
    wget \
    curl \
    cmake \
    ninja-build \
    git \
    autoconf \
    automake \
    libcrypt-dev \
    libc6-dev

# toolkit related libraries
RUN apt-get install -y \
    libreadline-dev \
    tcl-dev \
    pkg-config \
    bison \
    flex \
    rustc \
    cargo


RUN apt-get install -y \
    libboost-all-dev \
    libeigen3-dev \
    libgtest-dev \
    libgoogle-glog-dev \
    libyaml-cpp-dev \
    libcairo2-dev \
    libunwind-dev \
    libgmp-dev \
    libgmpxx4ldbl \
    libhwloc-dev \
    libffi-dev \
    libgflags-dev \
    libmetis-dev

RUN add-apt-repository ppa:ubuntu-toolchain-r/test -y \
    && apt-get update \
    && apt-get install -y gcc-10 g++-10

# python and distutils
RUN apt-get update && apt-get install -y \
    python3.8 \
    python3.8-dev \
    python3.8-distutils \
    python3-pip

# 新增：将python3软链接到python3.8
RUN ln -sf /usr/bin/python3.8 /usr/bin/python3 && \
    ln -sf /usr/bin/python3.8 /usr/bin/python

RUN python3.8 -m pip install --upgrade pip setuptools wheel

RUN python3.8 -m pip install matplotlib imageio

# rust and cargo
# you can use this mirror for faster download
ENV RUSTUP_DIST_SERVER=https://mirrors.tuna.tsinghua.edu.cn/rustup
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 60 --slave /usr/bin/g++ g++ /usr/bin/g++-10

# Anaconda3 installation
ENV CONDA_DIR=/opt/conda
# 关键修改：将系统路径放在Anaconda路径之前
ENV PATH="/usr/bin:/usr/sbin:/bin:/sbin:$CONDA_DIR/bin:/root/.cargo/bin"

RUN wget --quiet https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O ~/miniconda.sh && \
    /bin/bash ~/miniconda.sh -b -p $CONDA_DIR && \
    rm ~/miniconda.sh && \
    $CONDA_DIR/bin/conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/main && \
    $CONDA_DIR/bin/conda tos accept --override-channels --channel https://repo.anaconda.com/pkgs/r && \
    # Allow mamba installation
    conda install -y mamba -n base -c conda-forge && \
    # Clean up
    conda clean -ya


# 安装 Kissat SAT 求解器
RUN git clone https://github.com/arminbiere/kissat.git && \
    cd kissat && \
    ./configure && \
    make -j$(nproc) && \
    cp build/kissat /usr/bin/ && \
    cd .. && \
    rm -rf kissat

RUN kissat --version

WORKDIR /workspace

CMD ["bash"]