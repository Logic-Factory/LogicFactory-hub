# Exact SSV_Power Tool

## Introduction

The Exact SSV_Power tool is designed for exact power estimation of boolean functions. It generates and solves constraint satisfaction problems (CSPs) related to power consumption using encoding methods and solvers.

## Features

  * **Exact Power Estimation** : Estimates the power consumption of boolean functions based on input probability distributions.
  * **Constraint Encoding** : Encodes boolean functions and their power-related constraints into a specific format (e.g., SMT-LIB) for use with solvers like Z3.
  * **Netlist Library Generation** : Generates a netlist library containing multiple boolean functions and their power information for use in circuit synthesis and optimization.

## Installation

### Prerequisites

  * A C++ compiler supporting C++17 (e.g., GCC 10 or later)
  * CMake (version 3.12 or later)
  * Z3 solver (for constraint solving)

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

  * To generate a netlist library with power information:

     * `exact::generate_netlist_library_power("output_library.txt", num_inputs, num_classes);`

### Parameters

  * **`output_file`** : Path to the output netlist library file.
  * **`num_inputs`** : Number of inputs of the boolean functions.
  * **`num_classes`** : Number of power consumption classes.
  * **`average`** (optional): Whether to compute average power. Defaults to `true`.
  * **`start_index`** (optional): Starting index for reading boolean functions from the input file. Defaults to `0`.
  * **`partition_size`** (optional): Number of boolean functions to process in each partition. Defaults to `INT16_MAX`.

### Example

  * To generate a netlist library for boolean functions with 4 inputs and 2 power classes:

     * `exact::generate_netlist_library_power("power_netlist.txt", 4, 2);`

### Functions

  * **`SSV_Power`** : Constructor for the SSV_Power class, which takes a vector of boolean functions as input.
  * **`encode`** : Encodes the boolean function and its power constraints into an SMT-LIB format.
  * **`generate_netlist_library_power`** : Generates a netlist library file containing power information for multiple boolean functions.

## Note

  * The tool assumes that the input boolean functions are provided in a specific format (e.g., hexadecimal strings).
  * The performance and accuracy of power estimation depend on the input parameters and the complexity of the boolean functions.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

  * Z3 solver (https://github.com/Z3Prover/z3)