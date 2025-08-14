# Exact SSV API Documentation

## Introduction

The `exact::SSV` class provides functionality for encoding and decoding logic functions using the Symmetric Symmetry Verification (SSV) method. This class is designed to facilitate the encoding of logic functions into a logic formula and the decoding of results from a solver.

## Class: `exact::SSV`

### Function: `encode`

- **Description**: Encodes the logic functions into a logic formula.
- **Return Value**: An `exact::Encoding` object representing the encoded logic formula.
- **Parameter**:
  - `bool mark_variable`: A boolean indicating whether to mark variables in the output.
- **Usage**:
  ```cpp
  exact::SSV ssv_instance(functions, technology, r, non_trivial, all_steps, no_replication, lexicographical_step, lexicographical_op, ordered_symmetric);
  exact::Encoding encoded_formula = ssv_instance.encode(true);
  ```

### Function: `decode`

- **Description**: Decodes the solver's output from a file and writes the decoded results to another file.
- **Parameters**:
  - `std::string input_file`: The path to the input file containing the solver's output.
  - `std::string output_file`: The path to the output file where the decoded results will be saved.
- **Usage**:
  ```cpp
  ssv_instance.decode("solver_output.txt", "decoded_results.blif");
  ```

## Example

### Encoding Example

```cpp
#include "exact.h"

int main() {
    // Define your logic functions
    std::vector<Boolean> functions = ...; // Replace with actual functions

    // Create an SSV instance
    exact::SSV ssv_instance(functions, exact::Technology(), 0, false, false, false, false, false, false);

    // Encode the functions
    exact::Encoding encoded_formula = ssv_instance.encode(true);

    // Use the encoded formula (e.g., write to a file)
    encoded_formula.write_to_file("encoded_formula.cnf");

    return 0;
}
```

### Decoding Example

```cpp
#include "exact.h"

int main() {
    // Create an SSV instance
    exact::SSV ssv_instance(functions, exact::Technology(), 0, false, false, false, false, false, false);

    // Decode the solver's output
    ssv_instance.decode("solver_output.txt", "decoded_results.blif");

    return 0;
}
```

## Notes

- **File Paths**: Ensure that the input and output file paths are correctly specified.
- **Dependencies**: The `exact::SSV` class relies on other components like `exact::Encoding` and `exact::Technology` for full functionality.

By utilizing the `exact::SSV` APIs, you can efficiently encode and decode logic functions for use in various applications.