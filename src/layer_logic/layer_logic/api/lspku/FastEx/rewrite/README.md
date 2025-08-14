# Exact LUT Rewrite Tool

## Introduction

The Exact LUT Rewrite tool is designed for optimizing digital circuits by rewriting Lookup Tables (LUTs) based on a given netlist and library. It extracts truth tables from the netlist, initializes signal probabilities, and substitutes nodes with optimized sub-netlists from the library.

## Features

  * **LUT Extraction** : Extracts truth tables from LUT nodes in the netlist.
  * **Signal Probability Initialization** : Computes the probability of signals being high (1) for each node in the netlist.
  * **Node Substitution** : Replaces nodes in the netlist with optimized sub-netlists from a library based on truth tables and signal probabilities.
  * **Power Optimization** : Supports rewriting LUTs with consideration of power consumption.

## Installation

### Prerequisites

  * A C++ compiler supporting C++17 (e.g., GCC 10 or later)
  * CMake (version 3.12 or later)

### Compilation

  1. Clone the repository:

     * `git clone <repository-url>`

  2. Create a build directory and compile:

     * `mkdir build`
     * `cd build`
     * `cmake ..`
     * `make`

## Usage

### Basic Usage

  * To perform LUT rewriting on a netlist using a specified library:

     * `NET::lut_rewrite(netlist, "library_file.txt");`

  * To perform LUT rewriting with power optimization:

     * `NET::lut_rewrite_power(netlist, "library_file.txt");`

### Functions

  * **`extract_truth_table`** : Extracts the truth table from a given function in the netlist.
  * **`initialize_signal_probability`** : Initializes the signal probability for each node in the netlist.
  * **`substitute_node`** : Replaces a node in the netlist with a sub-netlist from the library based on the truth table and optionally signal probabilities.
  * **`negate`** : Negates the truth table string (used for canonicalization).
  * **`lut_rewrite`** : Performs LUT rewriting on the netlist using the provided library.
  * **`lut_rewrite_power`** : Performs LUT rewriting with power optimization using the provided library.

### Example

  * To rewrite LUTs in a netlist loaded from a file:

```cpp
NET::Netlist netlist;
NET::read_netlist("input_netlist.txt", netlist);
NET::lut_rewrite(netlist, "library.txt");
NET::write_netlist("output_netlist.txt", netlist);
```

  * To rewrite LUTs with power optimization:

```cpp
NET::Netlist netlist;
NET::read_netlist("input_netlist.txt", netlist);
NET::lut_rewrite_power(netlist, "power_library.txt");
NET::write_netlist("output_netlist.txt", netlist);
```

### Parameters

  * **`netlist`** : The netlist to be optimized.
  * **`library`** : Path to the library file containing optimized sub-netlists.

## Note

  * The tool assumes that the input netlist and library are in the correct format.
  * The performance of the optimization depends on the quality of the provided library.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

  * None