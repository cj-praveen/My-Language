#ifndef _STRING_VIEW_H
#define _STRING_VIEW_H

#include <stddef.h>
#include <stdlib.h>

typedef struct {
    size_t size;
    const char *data;
} StringView;

#define SV_New(size,data) (StringView) {(size), (data)}
#define SV_Fcstr(cstr)    (StringView) {(strlen(cstr)), (cstr)}

// printf macros for String_View
#define SV_Fmt "%.*s"
#define SV_Arg(sv) (int) (sv).size, (sv).data
// USAGE:
//   String_View name = ...;
//   printf("Name: "SV_Fmt"\n", SV_Arg(name));

int SV_eq(StringView a, StringView b);
int SV_in(const StringView* arr, size_t n, StringView b);

#endif // !_STRING_VIEW_H
