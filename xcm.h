#ifndef XXX_C_MACROS_H
#define XXX_C_MACROS_H

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define FATAL(fmt, ...)                                 \
    do {                                                \
        fprintf(stderr, "%s at <%s:%d>",                \
            (fmt), ##__VA_ARGS__, __FILE__, __LINE__);  \
        exit(1);                                        \
    } while (0)

/*
 * Dynamic array
 * Usage example:
 *  ```
 *      typedef struct {
 *          int *items;
 *          int count;
 *          int capacity;
 *      } Integers;
 *      Integers dyna;
 *
 *      DYNA_APPEND(dyna, 1);
 *      DYNA_APPEND(dyna, 2);
 *  ```
 */
#define DYNA_APPEND(da, item)                                           \
    do {                                                                \
        if ((da)->capacity <= (da)->count) {                            \
            (da)->capacity = (da)->capacity==0 ? 10 : 2*(da)->capacity; \
            (da)->items = realloc((da)->items,                          \
                    sizeof(*(da)->items)*(da)->capacity);               \
            assert((da)->items);                                        \
        }                                                               \
        (da)->items[(da)->count++] = (item);                            \
    } while (0)
#define DYNA_FOREACH(i, da) for (int i = 0; i < (da)->count; i++)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define NUM_VARGS(type, ...) (sizeof((type[]){__VA_ARGS__}) / sizeof(type))

/*
 * Get the offset of a struct member
 */
#define OFFSET_OF(type, member) ((size_t) &(((type *) 0)->member))

/*
 * A macro used to imitate 'defer' 
 * =1. Without macro
 *  ```
 *      if (false) {
 *          free(a);
 *          free(b);
 *          return 1;
 *      }
 *      free(a);
 *      free(b);
 *      return 0;
 *  ```
 * =2. With macro
 *  ```
 *      int status = 0; 
 *      if (false) RETURN_DEFER(1);
 *      defer:
 *          free(a);
 *          free(b);
 *          return status;
 *  ```
 */
#define RETURN_DEFER(code) do { status = (code); goto defer; } while (0)

#define SWAP(a, b) do { (a) ^= (b); (b) ^= (a); (a) ^= (b); } while (0)

/*
 * Create reference of a anonymous temparary variable
 * =1. Without macro
 *  ```
 *      void func(int *);
 *      int x = 10;
 *      func(&x);
 *  ```
 * =2. With macro
 *  ```
 *      func(TMP_REF(int, 10));
 *  ```
 */
#define TMP_REF(t, v) ((t[]){(v)})

#define UNUSED(x) ((void) x)

#define INVISIBLE __attribute__((visibility("hidden")))
#define VISIBLE __attribute__((visibility("default")))

#define INIT __attribute__((constructor))
#define FINI __attribute__((destructor))

#endif // XXX_C_MACROS_H
