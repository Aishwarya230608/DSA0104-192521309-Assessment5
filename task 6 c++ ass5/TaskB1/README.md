# B1 execution
Compile: `g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o main`
Expected/observed output is in `output.txt` and `screenshots/output.png`.
Hand check: OP = 500 + 1,200 = 1,700. IP = 3 × 2,500 + 40,000 = 47,500. Grand total = 49,200.
Removing `virtual` from pure virtual `total()` makes the base declaration non-virtual; `= 0` is only valid for virtual functions, so compilation fails. Removing the virtual destructor makes deletion through `Bill*` undefined behaviour.
