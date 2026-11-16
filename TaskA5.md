# Task A5 – Design Recovery and Rethrowing

## A5.1 Catch locations
- Low-level validation detects invalid values and throws a specific exception.
- A service-layer catch may log context (patient/bill identifier) and use `throw;` to preserve the original exception.
- The application boundary (`main` or request handler) catches `BillingError`, then `std::exception`, then `...` as a final safety net, and reports a safe message to the user.
- Do not catch and silently ignore an error. Log once at the chosen boundary to avoid duplicate logs.

## A5.2 Stack unwinding and RAII
When an exception leaves a scope, automatic objects in that scope are destroyed in reverse construction order. A `std::vector`, `std::string`, `std::unique_ptr`, lock guard or file-stream object releases its resource in its destructor. This is stack unwinding. RAII ties resource lifetime to object lifetime and prevents a missing `delete` in one of many catch blocks.

## Prediction program
For the supplied `Guard` program:
```text
~f ~main caught 42
```
`g` is destroyed first because it belongs to `f()` and `f()` exits by throwing. Then `m` is destroyed as the exception exits the `try` block. The statement `not printed` is after `f()` and is skipped because control transfers to a matching handler. The `catch(int)` handler prints `caught 42`.

## Alternative: manual delete in catch blocks
The work may be done with raw pointers and a `delete` in each error handler. Runtime complexity is still O(1) cleanup per resource, but every new failure path creates another place where cleanup must be remembered. If there are p exit/error paths and a resource is acquired before them, there can be up to p cleanup obligations; a missed one leaks. `unique_ptr`/containers centralize cleanup.
