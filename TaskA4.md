# Task A4 – Design the Exception Strategy

## A4.1 Errors and hierarchy
Possible errors:
- Negative consultation, room, procedure, medicine or package charge: invalid input.
- Claim amount above policy cover: claim rejected.
- Unknown government package code: package lookup failure.
- Missing patient record: record not found.
- Text supplied where a number is expected: `std::invalid_argument` from parsing.
- Impossibly large allocation: `std::bad_alloc`.

Suggested hierarchy:
```text
std::exception
└── std::runtime_error
    └── BillingError
        ├── InvalidChargeError
        ├── PatientRecordError
        ├── UnknownPackageError
        └── ClaimError
```
`std::bad_alloc` and parsing exceptions can be caught as standard library exceptions; they need not be forced into the application hierarchy.

## A4.2 Throwing and noexcept
May throw: constructors that validate input, bill calculations that validate, payer approval, package lookup, parsing, file opening/writing, and allocation. `main` or an application boundary catches exceptions and reports a clear message. Destructors, cleanup functions, and simple non-throwing accessors should be `noexcept` where appropriate. Destructors should not throw: during stack unwinding a second exception can call `std::terminate`, preventing orderly recovery.

## Alternative: return status
A function can return an enum such as `Status::Ok`, `NegativeAmount`, `ExceedsCover`, and write the result through an output parameter (or return a result structure). Normal execution avoids exception propagation and is predictable; error paths require every caller to inspect and forward the status/message. The result structure uses extra space for a status and possibly a message. Exceptions keep normal-path code simpler but are more expensive when thrown and caught.
