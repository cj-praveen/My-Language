#include <stddef.h>
#include <string.h>

#include "./string_view.h"

int SV_eq(StringView a, StringView b) {
    if (a.size != b.size) {
        return 0;
    }
    return memcmp(a.data, b.data, a.size) == 0;
}

int SV_in(const StringView* arr, size_t n, StringView b) {
    for (size_t i = 0; i < n; ++i) {
        if (SV_eq(arr[i], b)) {
            return i;
        }
    }

    return -1;
}
