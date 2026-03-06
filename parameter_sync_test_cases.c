/**
 * One test: 30 structs (ParamRow) for HIL/SIL parameter sync.
 * Struct names: AVL, BMS, LC, PL, EFF, REG.
 * mem_address: random 32-bit-style addresses.
 */

#include "parameter_sync_test_cases.h"
#include <stdint.h>

#define P32(x) ((void *)(uintptr_t)(x))

static const ParamRow test_data[TEST_NUM_STRUCTS] = {
    { "REG", 0, 0, "reg0", P32(0x8a2f1000u), "float" },
    { "AVL", 0, 0, "av0", P32(0x3b4c2004u), "float" },
    { "PL", 0, 0, "pl0", P32(0x1d6e3008u), "int" },
    { "BMS", 0, 0, "bms0", P32(0x9f01800cu), "float" },
    { "LC", 0, 0, "lc0", P32(0x5c73a010u), "int" },
    { "EFF", 0, 0, "eff0", P32(0x2e94b014u), "float" },
    { "AVL", 0, 1, "av1", P32(0x7a05c018u), "float" },
    { "AVL", 0, 2, "av2", P32(0x4b16d01cu), "int" },
    { "BMS", 0, 1, "bms1", P32(0xcd27e020u), "float" },
    { "BMS", 0, 2, "bms2", P32(0x8e38f024u), "int" },
    { "LC", 0, 1, "lc1", P32(0x50490128u), "float" },
    { "EFF", 0, 1, "eff1", P32(0x215a102cu), "float" },
    { "EFF", 0, 2, "eff2", P32(0xf36b2030u), "float" },
    { "PL", 0, 1, "pl1", P32(0xb47c3034u), "int" },
    { "PL", 0, 2, "pl2", P32(0x658d4038u), "float" },
    { "REG", 0, 1, "reg1", P32(0x379e503cu), "float" },
    { "REG", 0, 2, "reg2", P32(0xe8af6040u), "int" },
    { "AVL", 0, 3, "av3", P32(0x9ab07044u), "int" },
    { "AVL", 0, 4, "av4", P32(0x5cc18048u), "float" },
    { "BMS", 0, 3, "bms3", P32(0x1dd2904cu), "float" },
    { "LC", 0, 2, "lc2", P32(0xdfe3a050u), "int" },
    { "EFF", 0, 3, "eff3", P32(0xa0f4b054u), "float" },
    { "PL", 0, 3, "pl3", P32(0x6205c058u), "int" },
    { "REG", 0, 3, "reg3", P32(0x2316d05cu), "float" },
    { "AVL", 0, 5, "av5", P32(0xe427e060u), "float" },
    { "BMS", 0, 4, "bms4", P32(0xa538f064u), "float" },
    { "LC", 0, 3, "lc3", P32(0x66490068u), "int" },
    { "EFF", 0, 4, "eff4", P32(0x285a106cu), "float" },
    { "PL", 0, 4, "pl4", P32(0xe96b2070u), "int" },
    { "REG", 0, 4, "reg4", P32(0xab7c3074u), "float" },
};

TestView get_test(void) {
    TestView v = {
        .rows = test_data,
        .count = TEST_NUM_STRUCTS,
    };
    return v;
}
