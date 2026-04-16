#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void* my_malloc(size_t size, const char *file, int line);
void my_free(void *ptr, const char *file, int line);


#define malloc(s) my_malloc(s, __FILE__, __LINE__) 
#define free(p) my_free(p, __FILE__, __LINE)

#endif

