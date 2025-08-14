message("lf_platform.")
add_library(lf_platform INTERFACE)

# 查找 Python 3.8 并添加头文件路径和库
find_package(Python3 3.8 REQUIRED COMPONENTS Development)
message(STATUS "Found Python 3.8: ${Python3_INCLUDE_DIRS}")

target_link_libraries(lf_platform INTERFACE
    lf_arch
    lf_logic
    lf_netlist
    lf_misc
    lf_utility
    lf_3rd_json
    ${Python3_LIBRARIES}  # 添加 Python 3.8 库
)

target_include_directories(lf_platform SYSTEM INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Python3_INCLUDE_DIRS}  # 添加 Python 3.8 头文件路径
)