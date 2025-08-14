# `technology_mapping_api` Function Documentation

## Overview

The `technology_mapping_api` function automates the technology mapping process for a given circuit. It reads a circuit's netlist and a technology library, performs technology mapping to optimize the circuit based on predefined criteria, and writes the optimized circuit to a Verilog file.

## Function Prototype

```cpp
void PASyn::technology_mapping_api(const std::string& input, const std::string& technology_input, const std::string& output);
```

## Input Parameters

- `const std::string& input`:
  - **Description**: Path to the input netlist file.
  - **Format**: Typically a `.blif` file path, e.g., `"design.blif"`.
  - **Purpose**: Provides the structural information of the circuit to be optimized.

- `const std::string& technology_input`:
  - **Description**: Path to the technology library file.
  - **Format**: Typically a `.lib` file path, e.g., `"technology.lib"`.
  - **Purpose**: Provides the technology-specific parameters and standard cells for optimization.

- `const std::string& output`:
  - **Description**: Path to the output Verilog file.
  - **Format**: A file path where the optimized circuit will be saved, e.g., `"optimized_design.v"`.
  - **Purpose**: Specifies where the optimized circuit description will be written.

## Output

- **File**: The function generates a Verilog file at the specified output path, containing the optimized circuit description.

## Example Usage

```cpp
#include "netlist.h"

PASyn::technology_mapping_api("design.blif", "technology.lib", "optimized_design.v");
```

## Notes

- **File Paths**: Ensure the input and output file paths are correctly specified.
- **File Formats**: The input netlist should be in `.blif` format, and the technology library should be in `.lib` format. The output will be in Verilog format.
- **Dependencies**: The function relies on other functions like `read_liberty`, `read_blif`, and `write_verilog` for file I/O operations. Make sure these functions are properly defined and implemented.

By using `technology_mapping_api`, you can efficiently perform technology mapping to optimize your circuit based on the provided technology library.