# Exact Incremental Synthesis Tool

## Introduction

This tool provides functionality for exact incremental synthesis of boolean functions. It supports various methods for generating similar sub-functions and encoding boolean functions into CNF (Conjunctive Normal Form) for use with SAT solvers.

## Features

  * Generate similar sub-functions using methods like truncation, muting variables, or manual specification.
  * Encode boolean functions into CNF for use with SAT solvers.
  * Perform incremental encoding to identify differences between sub-function and current function encodings.

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

  * Run the tool with the desired options:

     * `./FastEX_incremental [options]`

### Options

  * `-p [num_inputs]` : Use the partial dataset with the specified number of inputs.
  * `-f [num_inputs]` : Use the full dataset with the specified number of inputs.

### Example

  * To run with a partial dataset for 4 inputs:

     * `./FastEX_incremental -p 4`

## Methods

### similar_sub_func

Generates a similar sub-function based on the specified method.

  * **Parameters** :

    * `original` : The original boolean function as a string.
    * `method` : The method to use for generating the similar sub-function (e.g., "trunc", "mute", "random", "manual").
    * `sub_n` : The number of inputs for the sub-function.
    * `option` : Additional options for the specified method.
    * `num_decomposable` : Number of decomposable variables (default is 0).
    * `random_tt` : Random truth table (default is empty).

  * **Returns** :

    * A pair consisting of the similar sub-function and an integer.

### incremental_encode

Performs incremental encoding to identify the differences between the sub-function and current function encodings.

  * **Returns** :

    * A pair of vectors containing the clauses to delete and add.

### encode_for_increment

Encodes the boolean function into CNF for incremental use.

  * **Parameters** :

    * `mark_variable` : Whether to mark variables in the encoding.

  * **Returns** :

    * An Encoding object representing the CNF encoding.

## Note

  * The tool assumes that the input boolean functions are provided in a specific format.
  * The performance may vary depending on the size and complexity of the boolean functions.

This README provides a basic overview of the Exact Incremental Synthesis Tool. For more detailed information, please refer to the code comments and documentation.