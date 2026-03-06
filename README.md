# HIL Parameter Sync

Syncs parameter structs for Formula SAE HIL/SIL test cases.

## What it does

1. Loads 30 parameter structs (name, id, param#, param name, memory address, datatype).
2. Sorts by struct name (AVL, BMS, EFF, LC, PL, REG).
3. Counts params per name and gets start/end indices.
4. Assigns identifiers by order (AVL=0, BMS=1, …).
5. Sorts within each name by parameter number.
6. Prints the result with 32-bit memory addresses.

## Build & run

```bash
gcc -Wall -Wextra -o sort_test main.c parameter_sync_test_cases.c
./sort_test
```

## Files

- `main.c` — sort pipeline and output
- `parameter_sync_test_cases.c` / `.h` — test data (30 structs, 32-bit addresses)
# 2D-Array-Testing
