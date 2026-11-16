# B3 measurement interpretation

Fill this table with the values from your own lab computer's `benchmark_output.txt`.

| N | Virtual (s) | Switch (s) | Variant (s) |
|---:|---:|---:|---:|
| 1,000 | | | |
| 1,000,000 | | | |
| 10,000,000 | | | |

| Invalid rate | Return code (s) | Exception (s) |
|---:|---:|---:|
| 0% | | |
| 1% | | |
| 50% | | |

Expected interpretation: all three bill-processing approaches are O(n). The virtual version has indirect dispatch and pointer/object locality costs; switch dispatch may benefit from contiguous tagged data; variant stores the largest alternative plus a discriminator and uses visitation. Exceptions are generally cheap when no exception is thrown but become increasingly expensive as the invalid rate rises. State only what your own measurements show.
