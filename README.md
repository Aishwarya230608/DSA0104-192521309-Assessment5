# Assignment 5 – CO5: Reliable Software with Runtime Polymorphism and Exceptions

**Student:** R. Aishwarya  
**Register Number:** 192521309  
**Repository name:** `DSA01-192521309-Assignment5`  
**Nature:** Individual  
**Language:** C++17  
**Compiler:** g++ (record the exact version used on your machine with `g++ --version`)

## Important submission note
This package contains source code, design answers, reproducible input/output records, benchmark code, and terminal-style PNG evidence generated from the recorded executions in this environment. Re-run the programs on your college/lab machine and replace/add screenshots from your own terminal before submission. Benchmark timings are machine-dependent. The assignment requires progressive Git commits; this ZIP cannot create that history for you.

## Compile convention
Normal programs:
```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o main
./main
```
Optimized benchmark:
```bash
g++ -std=c++17 -O2 -Wall -Wextra benchmark.cpp -o benchmark
./benchmark
```
Address sanitizer (where supported):
```bash
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer main.cpp -o main_asan
./main_asan
```

## Folder guide
- `PartA/` – A1–A5 design, pseudocode, UML, vtable, exception strategy and prediction answers.
- `TaskB1/` – polymorphic bill hierarchy, complete-code solution and validation.
- `TaskB2/` – exception conditions, rethrowing, completed TODO program and RAII test.
- `TaskB3/` – virtual vs switch vs `std::variant` and exception/return-code benchmark.
- `TaskB4/` – extension example, sanitizer test and production decision.
- `TaskA2/`, `TaskA5/`, `TaskB2/` – separate prediction programs and their expected outputs.

## Progressive commit plan
Make at least one commit per task, for example:
```bash
git add PartA/TaskA1.md && git commit -m "Complete Task A1 design"
git add PartA/TaskA2.md TaskA2/ && git commit -m "Complete Task A2 binding investigation"
# Repeat for A3, A4, A5, B1, B2, B3 and B4.
```

## Task result summary
| Task | Result |
|---|---|
| A1 | Abstract Bill hierarchy, common interface, UML and processing pseudocode documented. |
| A2 | Early/late binding, vtable dispatch and virtual destructor explained; prediction program included. |
| A3 | Abstract payer hierarchy and extension design documented. |
| A4 | Error list, exception hierarchy and exception specifications documented. |
| A5 | Catch/rethrow plan and RAII stack-unwinding experiment included. |
| B1 | All four bill types tested with SelfPay, Insurance and GovernmentScheme; complete-code sample also executed. |
| B2 | Validation, ClaimError rethrow, invalid input and bad allocation demonstrations included. |
| B3 | Correctness and performance comparison program included; run locally for machine-specific measurements. |
| B4 | New bill and payer added as new derived classes; sanitizer-ready test included. |

## GitHub
Create a repository named exactly `DSA01-192521309-Assignment5`, upload the contents of this folder, and add the faculty as collaborator if private. Paste the working GitHub URL on the cover page and in the submission portal.
