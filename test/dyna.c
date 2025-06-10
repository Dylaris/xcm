#include "xcm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    char **items;
    int count;
    int capacity;
} name_array_t;

int main(void)
{
    name_array_t names = {0};

    DYNA_APPEND(&names, "jack");
    DYNA_APPEND(&names, "forger");
    DYNA_APPEND(&names, "tom");
    DYNA_APPEND(&names, "ben");
    DYNA_APPEND(&names, "peter");

    DYNA_FOREACH(x, &names) {
        char *name = names.items[x];
        printf("%s\n", name);
    }

    free(names.items);

    return 0;
}
