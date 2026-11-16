# Predictions written before execution (reference answers)

## A2 supplied program
`500 ~OPBill ~Bill`
Reason: virtual dispatch from `show()` to `OPBill::total()`, then derived and base destructors.

## A5 supplied program
`~f ~main caught 42`
Reason: stack unwinding destroys local guards in reverse scope order; execution after `f()` is skipped.

## B2 supplied program
`ok done caught negative [log too large] caught too large `
Reason: first item passes; second throws `invalid_argument` (not caught by the `out_of_range` handler in `process`); third throws `out_of_range`, gets logged and rethrown with `throw;`, then caught in `main`.
