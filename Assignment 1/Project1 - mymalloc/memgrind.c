#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "mymalloc.h"

#define NUM_TESTS 10
#define NUM_ALLOCS 20

void test1() {
    for (int i = 0; i < NUM_TESTS; i++) {
        void* ptrs[NUM_ALLOCS];

        for (int j = 0; j < NUM_ALLOCS; j++) {
            ptrs[j] = my_malloc(1, __FILE__, __LINE__);
            if (ptrs[j] == NULL) {
                printf("Test 1: Memory allocation failed\n");
                return;
            }
        }

        for (int j = 0; j < NUM_ALLOCS; j++) {
            my_free(ptrs[j], __FILE__, __LINE__);
        }
    }
}

void test2() {
    for (int i = 0; i < NUM_TESTS; i++) {
        void* ptrs[NUM_ALLOCS];

        for (int j = 0; j < NUM_ALLOCS; j++) {
            ptrs[j] = my_malloc(1, __FILE__, __LINE__);
            if (ptrs[j] == NULL) {
                printf("Test 2: Memory allocation failed\n");
                return;
            }
        }

        for (int j = NUM_ALLOCS - 1; j >= 0; j--) {
            my_free(ptrs[j], __FILE__, __LINE__);
        }
    }
}

void test3() {
    for (int i = 0; i < NUM_TESTS; i++) {
        void* ptrs[NUM_ALLOCS];
        int numAllocated = 0;

        for (int j = 0; j < NUM_ALLOCS; j++) {
            int choice = rand() % 2;
            if (choice == 0 && numAllocated > 0) {
                int idx = rand() % numAllocated;
                my_free(ptrs[idx], __FILE__, __LINE__);
                ptrs[idx] = NULL;
                numAllocated--;
            } else {
                ptrs[numAllocated] = my_malloc(1, __FILE__, __LINE__);
                if (ptrs[numAllocated] == NULL) {
                    printf("Test 3: Memory allocation failed\n");
                    return;
                }
                numAllocated++;
            }
        }

        for (int j = 0; j < numAllocated; j++) {
            if (ptrs[j] != NULL) {
                my_free(ptrs[j], __FILE__, __LINE__);
            }
        }
    }
}

int main() {
    srand(time(NULL));

    test1();
    test2();
    test3();

    return 0;
}
