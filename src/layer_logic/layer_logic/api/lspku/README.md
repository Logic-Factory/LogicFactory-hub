# 逻辑综合工具 Tcl 命令文档

## 概述
本文档详细介绍了10个用于逻辑综合任务的Tcl命令，包括强化学习优化命令生成、精确综合方法、功耗驱动优化和功耗计算等功能，并提供了各命令的示例用法。

## 环境配置
#### 1. 克隆代码库
git clone https://github.com/Logic-Factory/LogicFactory.git

#### 2. 进入目录并初始化子模块
cd LogicFactory
git submodule update --init --recursive

#### 3. 构建 Docker 镜像
docker build -t logic-factory:latest .

#### 4. 运行容器（关键：添加 --gpus all 启用 GPU 访问, RL算子需要GPU支持）
docker run -it --gpus all -v ../LogicFactory-hub-pku:/workspace logic-factory:latest

#### 5. 进入容器后，正常构建
cd /workspace
mkdir -p build && cd build
cmake -G Ninja ..
ninja (or ninja > build.log 2>&1)
然后重启终端

#### 进入命令行界面 
./build/app/logicfactory

anchor set_domain lsils

## 命令使用说明

以下是10个逻辑综合与功耗分析命令的详细使用说明及示例：


---

### 1. `rl_gene_basic`
使用basic特征模式（obs_dim=14）进行强化学习优化命令生成

**参数说明：**
| 参数名            | 类型    | 必填 | 描述                                      |
|-------------------|---------|------|------------------------------------------|
| `-test_list`      | 字符串  | 是   | 测试电路列表文件路径                     |
| `-model`          | 字符串  | 是   | PPO模型文件路径                          |
| `-result_dir`     | 字符串  | 是   | 结果保存目录                             |
| `-test_dir`       | 字符串  | 是   | 测试电路目录                             |

**示例：**
```tcl
rl_gene_basic \
    -test_list "./test_case/RL_basic/test_set/test_list_small.txt" \
    -result_dir "./test_case/RL_basic/result" \
    -test_dir "./test_case/RL_basic/test_set"
```

---

### 2. `rl_gene_glitch`
使用glitch特征模式（obs_dim=89）进行强化学习优化命令生成

**参数说明：**  
*(参数与`rl_gene_basic`相同)*

**示例：**
```tcl
rl_gene_glitch \
    -test_list "./test_case/RL_glitch/test_set/test_list_small.txt" \
    -model "./models/ppo_glitch_model.pt" \
    -result_dir "./test_case/RL_glitch/result" \
    -test_dir "./test_case/RL_glitch/test_set"
```

---


### 3. `ditt`
使用DITT进行精确逻辑综合

**参数说明：**
| 参数名            | 类型    | 必填 | 描述                                      |
|-------------------|---------|------|------------------------------------------|
| `-functions`      | 字符串  | 是   | 布尔函数列表(十六进制字符串)              |
| `-r`              | 整型    | 是   | 综合步骤数                                |
| `-sat_output`     | 字符串  | 是   | SAT CNF编码保存路径                      |
| `-circuit_output` | 字符串  | 是   | 解码后电路保存路径                       |
| `-solver`         | 字符串  | 是   | SAT求解器(kissat)                |

**示例：**
```tcl
ditt \
    -functions "0001,0002,0003" \
    -r 1 \
    -sat_output "./test_case/ditt/output.cnf" \
    -circuit_output "./test_case/ditt/decoded_circuit.blif" \
    -solver "kissat"
```

---

### 4. `msv`
使用MSV方法进行精确逻辑综合

**参数说明：**  
*(参数与`ditt`相同)*

**示例：**
```tcl
msv \
    -functions "0001,0002,0003" \
    -r 1 \
    -sat_output "./test_case/msv/output.cnf" \
    -circuit_output "./test_case/msv/decoded_circuit.blif" \
    -solver "kissat"
```

---

### 5. `ssv`
使用SSV方法进行精确逻辑综合

**参数说明：**  
*(参数与`ditt`相同)*

**示例：**
```tcl
ssv \
    -functions "0001,0002,0003" \
    -r 1 \
    -sat_output "./test_case/ssv/output.cnf" \
    -circuit_output "./test_case/ssv/decoded_circuit.blif" \
    -solver "kissat"
```

---

### 6. `ssv_incremental`
使用增量式SSV方法进行精确逻辑综合

**参数说明：**
| 参数名            | 类型    | 必填 | 描述                                      |
|-------------------|---------|------|------------------------------------------|
| `-num_inputs`     | 整数    | 是   | 布尔函数中的变量个数              |
| `-function`       | 字符串  | 是   | 单个布尔表达式                                |
| `-exp`            | 字符串  | 是   | 对应的逻辑表达式                                |
| `-output_file`    | 字符串  | 是   | 输出文件                              |

**示例：**
```tcl
ssv_incremental \
    -num_inputs 4 \
    -function "0001" \
    -exp "&A&&BCD" \
    -output_file "./test_case/ssv_incremental/output.blif"
```

---

### 7. `ssv_power`
生成功耗驱动优化的网表

**参数说明：**
| 参数名            | 类型    | 必填 | 描述                                      |
|-------------------|---------|------|------------------------------------------|
| `-input`          | 字符串  | 是   | 输入文件                           |
| `-output`         | 字符串  | 是   | 网表输出路径                           |
| `-num_inputs`     | 整型    | 是   | 输入变量数量                             |
| `-num_classes`    | 整型    | 是   | 输入概率离散化的类别数                   |
| `-average`        | 布尔    | 是   | 是否使用平均策略              |
| `-start_index`    | 整型    | 是   | 处理起始索引(默认:0)                     |
| `-partition_size` | 整型    | 是   | 最大处理函数数(默认:INT16_MAX)           |

**示例：**
```tcl
ssv_power \
    -input "./test_case/ssv_power/input.txt" \
    -output "./test_case/ssv_power/output.txt" \
    -num_inputs 4 \
    -num_classes 5 \
    -average 1 \
    -start_index 0 \
    -partition_size 100
```

---

### 8. `lut_rewrite`
使用最优库进行LUT重写

**参数说明：**
| 参数名            | 类型    | 必填 | 描述                                      |
|-------------------|---------|------|------------------------------------------|
| `-input`          | 字符串  | 是   | 输入BLIF文件路径(不含.blif扩展名)        |
| `-lib`            | 字符串  | 是   | 最优库文件路径                           |
| `-output_dir`     | 字符串  | 是   | 重写后网表输出目录                       |
| `-input_dir`      | 字符串  | 是   | BLIF文件输入目录                         |

**示例：**
```tcl
lut_rewrite \
    -input "adder" \
    -lib "./test_case/lut_rewrite/optimal_library_reserve.txt" \
    -output_dir "./test_case/lut_rewrite/result/" \
    -input_dir "./test_case/lut_rewrite/test_set/"
```

---

### 9. `tech_mapping`
使用切割枚举进行工艺映射

**参数说明：**
| 参数名            | 类型    | 必填 | 描述                                      |
|-------------------|---------|------|------------------------------------------|
| `-input`          | 字符串  | 是   | 输入网表文件(.blif)                      |
| `-output`         | 字符串  | 是   | 映射后网表输出文件(.v)                   |
| `-tech_lib`       | 字符串  | 是   | 工艺库文件(.lib)                         |

**示例：**
```tcl
tech_mapping \
    -input "./test_case/tech_mapping/input.blif" \
    -tech_lib "./test_case/tech_mapping/technology.lib" \
    -output "./test_case/tech_mapping/output.v"
```

---

### 10. `calculate_power`
计算网表的功耗

**参数说明：**
| 参数名            | 类型    | 必填 | 描述                                      |
|-------------------|---------|------|------------------------------------------|
| `-input`          | 字符串  | 是   | 输入网表文件(.blif)                      |
| `-tech_lib`       | 字符串  | 是   | 工艺库文件(.lib)                         |
| `-output`         | 字符串  | 否   | 功耗结果输出文件(为空则输出到控制台)     |

**示例：**
```tcl
calculate_power \
    -input "./test_case/calculate_power/input.blif" \
    -tech_lib "./test_case/calculate_power/technology.lib" \
    -output "./test_case/calculate_power/output.txt"
```

---

### 使用说明
1. **必填参数**：标记为"是"的参数必须提供
2. **文件路径**：建议使用绝对路径以确保兼容性
3. **SAT求解器**：支持`kissat`求解器

各命令的详细实现请参考对应类的源代码。