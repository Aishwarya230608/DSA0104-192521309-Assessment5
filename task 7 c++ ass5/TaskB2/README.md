# B2 error engineering
The validation loop prints `ok done` for 100; negative input throws `invalid_argument` and is caught by the outer `std::exception` handler (no log); 2e6 throws `out_of_range`, is logged in `process`, rethrown with `throw;`, then caught by `main`.
The completed claim program checks negatives first, then cover. `throw;` rethrows the same dynamic exception object. `throw e;` creates a new exception from the static type of `e` (slicing can occur when caught through a base reference).
`raii.cpp` proves that a `unique_ptr` releases its resource while unwinding.
