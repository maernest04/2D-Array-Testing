#include "parameter_sync_test_cases.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int compare_by_name(const void *a, const void *b) {
    return strcmp(((const ParamRow *)a)->struct_name, ((const ParamRow *)b)->struct_name);
}

static int compare_by_param_number(const void *a, const void *b) {
    int na = ((const ParamRow *)a)->param_number;
    int nb = ((const ParamRow *)b)->param_number;
    return (na > nb) - (na < nb);
}

int main(void) {
    /* --- Load test data and sort by struct name --- */
    TestView test = get_test();
    ParamRow rows[TEST_NUM_STRUCTS];
    memcpy(rows, test.rows, test.count * sizeof(ParamRow));
    qsort(rows, test.count, sizeof(ParamRow), compare_by_name);

    printf("Sorted by struct name:\n");
    for (size_t i = 0; i < test.count; i++)
        printf("  %s  id=%d  param#=%d  %s  %s\n",
               rows[i].struct_name, rows[i].identifier, rows[i].param_number,
               rows[i].param_name, rows[i].datatype);

    /* --- Count each struct name --- */
    size_t counts[TEST_NUM_STRUCTS], num_groups = 0;
    for (size_t i = 0; i < test.count; ) {
        size_t n = 0;
        const char *name = rows[i].struct_name;
        while (i < test.count && strcmp(rows[i].struct_name, name) == 0)
            n++, i++;
        counts[num_groups++] = n;
    }

    printf("\nCount per struct name:\n");
    for (size_t g = 0, off = 0; g < num_groups; off += counts[g], g++)
        printf("  %s: %zu\n", rows[off].struct_name, counts[g]);

    /* --- Start and end index per struct name --- */
    size_t start[TEST_NUM_STRUCTS];
    start[0] = 0;
    for (size_t g = 1; g < num_groups; g++)
        start[g] = start[g - 1] + counts[g - 1];

    printf("\nStart and end index per struct name:\n");
    for (size_t g = 0; g < num_groups; g++)
        printf("  %s: start=%zu end=%zu\n", rows[start[g]].struct_name, start[g], start[g] + counts[g] - 1);

    /* --- Assign identifier by group order (AVL=0, BMS=1, ...) --- */
    for (size_t g = 0; g < num_groups; g++)
        for (size_t i = start[g]; i < start[g] + counts[g]; i++)
            rows[i].identifier = (int)g;

    /* --- Sort within each name by parameter number --- */
    for (size_t g = 0; g < num_groups; g++)
        qsort(rows + start[g], counts[g], sizeof(ParamRow), compare_by_param_number);

    printf("\nSorted by param number within each name (mem_address = 32-bit):\n");
    printf("  %-6s  %2s  %6s  %-8s  %-12s  %s\n", "name", "id", "param#", "param", "mem_address", "datatype");
    printf("  ------  --  ------  --------  ------------  -----\n");
    for (size_t i = 0; i < test.count; i++)
        printf("  %-6s  %2d  %6d  %-8s  %08lx       %s\n",
               rows[i].struct_name, rows[i].identifier, rows[i].param_number,
               rows[i].param_name, (unsigned long)(uintptr_t)rows[i].mem_address & 0xFFFFFFFFu, rows[i].datatype);

    return 0;
}
