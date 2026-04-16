#include "mymalloc.h"

#define MEMLENGTH 512

typedef struct MemBlock
{
    void *address;         
    size_t length;         
    struct MemBlock *next; 
} mem_t;

static double mem[MEMLENGTH];
static mem_t *header = NULL;
static size_t remainderMem = MEMLENGTH * sizeof(double);

void newMemBlock(mem_t *temp, size_t l, int i)
{
    temp->address = (char *)&mem[i];
    temp->length = l;
    temp->next = NULL;
}

void calcMem(int x)
{
    mem_t *initial = header;
    size_t usedMem = 0;

    while (initial != NULL)
    {
        usedMem += initial->length;
        initial = initial->next;
    }

    if (x == 0 || x == 1)
    {
        printf("The used memory: %lu  ", (unsigned long)usedMem);
        remainderMem = MEMLENGTH * sizeof(double) - usedMem;
        printf("The new memory: %lu\n", (unsigned long)remainderMem);
    }
}

void *my_malloc(size_t l, const char *file, int line)
{
    if (l <= 0)
    {
        printf("ERROR: %s, line %d - Invalid memory allocation request\n", file, line);
        return NULL;
    }

    size_t aligned_length = (l + 7) & ~7;

    if (aligned_length > remainderMem)
    {
        printf("ERROR: %s, line %d - Insufficient memory available\n", file, line);
        return NULL;
    }

    mem_t *current = header;

    while (current != NULL)
    {
        if (current->length >= aligned_length)
        {
            if (current->length > aligned_length)
            {
                mem_t *new_block = (mem_t *)((char *)current + aligned_length);
                new_block->next = current->next;
                new_block->length = current->length - aligned_length;
                current->length = aligned_length;
                current->next = new_block;
            }

            current->length *= -1;

            remainderMem -= aligned_length;

            return current->address;
        }

        current = current->next;
    }

    if (aligned_length <= remainderMem)
    {
        current = (mem_t *)mem;
        current->address = (char *)mem;
        current->length = aligned_length;
        current->next = header;

        current->length *= -1;

        remainderMem -= aligned_length;

        header = current;

        return current->address;
    }

    printf("ERROR: %s, line %d - Failed to allocate memory\n", file, line);
    return NULL;
}

void my_free(void *ptr, const char *file, int line)
{
    if (ptr == NULL)
    {
        printf("ERROR: %s, line %d - Attempt to free a NULL pointer\n", file, line);
        return;
    }
    mem_t *initial = header;
    mem_t *before = NULL;
    while (initial != NULL)
    {
        if (initial->address == ptr)
        {
            if (before == NULL)
            {
                header = initial->next;
            }
            else
            {
                before->next = initial->next;
            }
            remainderMem += initial->length < 0 ? -initial->length : 0;
            calcMem(1);
            return;
        }
        before = initial;
        initial = initial->next;
    }
    printf("ERROR: %s, line %d - Attempt to free a pointer that has not been allocated\n", file, line);
}






















