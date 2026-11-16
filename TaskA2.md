# Task A2 – Understand Runtime Binding

## A2.1 Early and late binding
Early binding selects a function using the static type at compile time. A non-virtual call through `Bill*` is resolved as a `Bill` call. Late binding applies to virtual functions: at run time, the object's dynamic type selects the final overrider. Thus `b->total()` calls `OPBill::total()` when `b` points to an `OPBill`.

## A2.2 Conceptual vtables
| Class | `total()` slot | destructor slot |
|---|---|---|
| `Bill` | pure virtual entry (no object of this abstract class) | `Bill::~Bill` |
| `OutPatientBill` | `OutPatientBill::total` | `OutPatientBill::~OutPatientBill` then base destructor |
| `InPatientBill` | `InPatientBill::total` | `InPatientBill::~InPatientBill` then base destructor |

A typical object stores a hidden vptr pointing to its class's vtable. `b->total()` looks up the `total` slot through that vptr and invokes the derived override. Exact vtable layout is compiler ABI-specific; this is a conceptual diagram, not a mandated memory layout.

## A2.3 Virtual destructor
Deleting a derived object through `Bill*` must run the derived destructor and then the base destructor. A virtual base destructor enables this. Without it, deleting a derived object through a base pointer is undefined behaviour; sanitizer diagnostics are expected on common toolchains, but exact diagnostics depend on compiler/runtime.

## Prediction program
For the supplied `OPBill` program, predicted output:
```text
500 ~OPBill ~Bill
```
`show()` is non-virtual, but its body calls the virtual function `total()`. The call is dispatched using the dynamic type of `*this`, so `OPBill::total()` returns 500. Deletion runs `~OPBill` followed by `~Bill`.

If `virtual` is removed from `~Bill`, `delete b` has undefined behaviour because the dynamic type differs from the static pointer type. Do not rely on a particular output; AddressSanitizer/UBSan may report an invalid delete or other issue, and some builds may appear to run. A clean run does not make the program valid.

## Alternative: dynamic_cast
Without virtual `total()`, code can test each concrete type with `dynamic_cast` and call its concrete calculation. For k possible types, a chain may perform up to k checks per bill, so O(k) dispatch work per bill versus one virtual dispatch O(1). The object typically no longer needs a vptr solely for `total`, but RTTI and class metadata still exist. The cast-based code must be updated whenever a new type is added.
