# Exact DITT API Documentation

## Introduction

This document describes the application programming interfaces (APIs) provided by the `exact::DITT` class for encoding and decoding logic functions using the Decision Diagram with Trivial Transformations (DITT) method.

## API Overview

### Class: `exact::DITT`

The `exact::DITT` class provides functionality for encoding logic functions into a logic formula and decoding the results from a solver.

## Functions

### Function: `encode`

- **Description**: Encodes the logic functions into a logic formula.
- **Return Value**: Returns an `exact::Encoding` object representing the encoded logic formula.
- **Parameters**:
  - `bool mark_variable`: Indicates whether to mark variables in the output.
- **Usage**:
  ```cpp
  exact::DITT ditt_instance(functions, technology, r, non_trivial, all_steps, no_replication, lexicographical_step, lexicographical_op, ordered_symmetric);
  exact::Encoding encoded_formula = ditt_instance.encode(true);
  ```

### Function: `decode`

- **Description**: Decodes the results from a solver's output file and writes the decoded results to an output file.
- **Parameters**:
  - `std::string input_file`: Path to the input file containing the solver's output.
  - `std::string output_file`: Path to the output file where the decoded results will be written.
- **Usage**:
  ```cpp
  ditt_instance.decode("solver_output.txt", "decoded_results.blif");
  ```

## Example

### Encoding Example

```cpp
#include "exact.h"

int main() {
    // Define your logic functions
    std::vector<Boolean> functions = ...; // Replace with actual functions

    // Create a DITT instance
    exact::DITT ditt_instance(functions, exact::Technology(), 0, false, false, false, false, false, false);

    // Encode the functions
    exact::Encoding encoded_formula = ditt_instance.encode(true);

    // Use the encoded formula (e.g., write to a file)
    encoded_formula.write_to_file("encoded_formula.cnf");

    return 0;
}
```

### Decoding Example

```cpp
#include "exact.h"

int main() {
    // Create a DITT instance
    exact::DITT ditt_instance(functions, exact::Technology(), 0, false, false, false, false, false, false);

    // Decode the solver's output
    ditt_instance.decode("solver_output.txt", "decoded_results.blif");

    return 0;
}
```

## Notes

- **Input/Output Files**: Ensure the input and output file paths are correctly specified.
- **Dependencies**: The `exact::DITT` class relies on other components like `exact::Encoding` and `exact::Technology` for proper functionality.

By using the `exact::DITT` APIs, you can effectively encode and decode logic functions for use in your applications.