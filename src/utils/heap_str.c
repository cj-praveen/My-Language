#include <stdlib.h>
#include <stdio.h>

#include "./heap_str.h"

HeapString HS_alloc(void) {
    char* allocation = malloc(S_INITIALSIZE);
    if (allocation == NULL) {
        fprintf(stderr, "S_ERROR: Buy more RAM, XD");
        exit(69);
    }
    allocation[0] = 0;
    return (HeapString) {
        .size = 1,
        .capacity = 16,
        .as = allocation,
    };
}

void HS_free(HeapString* str) {
    free(str->as);
    str->size = 0;
    str->capacity = 0;
}

void HS_putc(HeapString* str, char c) {
    if (str->size >= str->capacity) {
        str->capacity *= 2;
        str->as = realloc(str->as, str->capacity);
        if (str->as == NULL) {
            fprintf(stderr, "S_ERROR: Buy more RAM, XD");
            exit(69);
        }
    }

    str->as[str->size - 1] = c;
    str->as[str->size] = 0;
    str->size += 1;
}

void HS_clear(HeapString* str) {
    str->size = 1;
    str->as[0] = 0;
}
