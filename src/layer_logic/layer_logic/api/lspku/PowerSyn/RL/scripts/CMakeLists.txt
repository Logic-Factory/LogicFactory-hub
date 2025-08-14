# 安装 Conda 环境（基础目标）
add_custom_target(install_conda_env
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/install_conda_env.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Creating Conda environment from gym.yml"
)

# 安装 PyTorch（依赖于 Conda 环境）
add_custom_target(install_pytorch
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/install_pytorch.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Installing PyTorch and geometric libraries"
)

# 添加依赖：PyTorch 安装必须在 Conda 环境之后
add_dependencies(install_pytorch install_conda_env)

# 安装本地包（依赖于 Conda 环境和 PyTorch）
add_custom_target(install_local_packages
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/install_local_packages.sh
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Installing local packages in editable mode"
)

# 添加依赖：本地包安装必须在 PyTorch 之后（从而也在 Conda 环境之后）
add_dependencies(install_local_packages install_pytorch)