cmake_minimum_required(VERSION 3.10)
project(RL_command)

# 设置默认构建类型
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# 添加自定义目标
add_custom_target(install_all
    COMMENT "Installing all dependencies"
    DEPENDS install_conda_env install_local_packages install_pytorch
)

# 添加子目录
add_subdirectory(scripts)