# `calculate_power_api` Function Documentation

## Overview

The `calculate_power_api` function is designed to calculate various power values for a given circuit, including static power, dynamic power, internal power, wire power, and total power. It achieves this by reading the circuit's netlist and technology library files, performing necessary preprocessing, probability calculations, and timing analysis.

## Function Prototype

```cpp
std::vector<double> PASyn::calculate_power_api(std::string &input, std::string &technology_input, bool gym_using = false);
```

## Input Parameters

- `std::string &input`:
  - **Description**: Path to the input netlist file.
  - **Format**: Typically a `.blif` file path, e.g., `"design.blif"`.
  - **Purpose**: Provides structural information of the circuit, including nodes, inputs, and outputs.

- `std::string &technology_input`:
  - **Description**: Path to the technology library file.
  - **Format**: Typically a `.lib` file path, e.g., `"technology.lib"`.
  - **Purpose**: Provides technology-specific parameters such as cell delays, power consumption, and capacitances.

- `bool gym_using` (Optional):
  - **Description**: Boolean value indicating whether to use Gym (reinforcement learning environment).
  - **Values**: `true` or `false`.
  - **Default**: `false`.
  - **Purpose**: Determines whether to enable Gym-related functionalities.

## Return Value

- **Type**: `std::vector<double>`
- **Contents**:
  - `result[0]`: Static power (in watts, converted from micro-watts by multiplying by \(1e-6\)).
  - `result[1]`: Dynamic power.
  - `result[2]`: Internal power.
  - `result[3]`: Wire power.
  - `result[4]`: Total power (sum of static, dynamic, internal, and wire powers).

## Example Usage

```cpp
#include "netlist.h"

std::vector<double> power_result = PASyn::calculate_power_api("design.blif", "technology.lib", false);

// Accessing the results
std::cout << "Static Power: " << power_result[0] << " W" << std::endl;
std::cout << "Dynamic Power: " << power_result[1] << " W" << std::endl;
std::cout << "Internal Power: " << power_result[2] << " W" << std::endl;
std::cout << "Wire Power: " << power_result[3] << " W" << std::endl;
std::cout << "Total Power: " << power_result[4] << " W" << std::endl;
```

## Notes

- **File Paths**: Ensure the paths to the netlist and technology library files are correct.
- **File Formats**: The netlist should be in `.blif` format, and the technology library should be in `.lib` format.
- **Dependencies**: The function relies on `read_liberty` and `read_blif` functions for file reading. Make sure these functions are properly defined and implemented.

Using `calculate_power_api`, you can conveniently calculate various power metrics for circuit analysis and optimization.