CS214 Fall 2023
Project 1: my little malloc() <br>
'David Menendez'

Team Members:
- Zeel Patel (netID: zap19)
- Shreya Vyas (netID: sv693)

## Test Plan


### 1. Correctness Testing


**Test 1: Memory Allocation**
- Verify if `my_malloc()` successfully allocates memory.
- **Expected Result:** Memory allocation should occur without errors.


**Test 2: Memory Overlapping**
- Check if objects allocated by `my_malloc()` do not overlap.
- **Expected Result:** Allocated objects should not overlap each other in memory.


**Test 3: Memory Deallocation**
- Ensure that `my_free()` can correctly deallocate memory allocated by `my_malloc()`.
- **Expected Result:** Memory should be deallocated properly without any memory leaks.


### 2. Performance Testing (memgrind.c)


**Task 1: Test1 - Repeated Allocation and Deallocation**
- Allocate and deallocate 1-byte objects in a loop using `test1()` in memgrind.c.
- **Expected Result:** Measure the time taken and report the average duration. Ensure that `my_malloc()` and `my_free()` handle repeated allocations and deallocations effectively.


**Task 2: Test2 - Reverse Allocation and Deallocation**
- Allocate and deallocate 1-byte objects in reverse order using `test2()` in memgrind.c.
- **Expected Result:** Measure the time taken and report the average duration. Confirm that `my_malloc()` and `my_free()` handle reverse allocations and deallocations correctly.


**Task 3: Test3 - Random Allocation and Deallocation**
- Randomly allocate and deallocate 1-byte objects using `test3()` in memgrind.c.
- **Expected Result:** Measure the time taken and report the average duration. Validate that `my_malloc()` and `my_free()` can handle random allocations and deallocations efficiently.


## Design Notes


The implementation utilizes a memory allocation system with a linked list structure as seen in the `mymalloc.c` code. The `my_malloc()` function ensures correct memory allocation and error handling. The `my_free()` function effectively deallocates memory blocks and updates the available memory.


For Task 1 and Task 2, note that the minimum chunk size is 16 bytes due to alignment requirements, potentially impacting simultaneous allocations. This may result in a larger memory footprint than the number of requested allocations. Task 3 tests the ability of the implementation to handle random allocations and deallocations effectively.

