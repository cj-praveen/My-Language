#ifndef _HEAP_STR_H
#define _HEAP_STR_H

#include <stddef.h>

#define S_INITIALSIZE 16

typedef struct {
    size_t size;
    size_t capacity;
    char* as;
} HeapString;

HeapString HS_alloc(void);
void HS_free(HeapString* str);
void HS_putc(HeapString* str, char c);
void HS_clear(HeapString* str);

#endif // !_HEAP_STR_H
