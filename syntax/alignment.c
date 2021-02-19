/* $ gcc -o alignment -pedantic-errors -Werror alignment.c */
/* run with: */
/* ./alignment */

#include <stdio.h>
/* For printf */
#include <stdalign.h>
/* alignment aliases */

int main(void)
{
    alignas(8) short x; /* Aligns short at 8 Bytes */

    /* objects of struct X must be allocated at 4-byte boundaries */
    /* because X.n must be allocated at 4-byte boundaries */
    /* because int's alignment requirement is (usually) 4 */
    struct X
    {
        int n;  /* size: 4, alignment: 4 */
        char c; /* size: 1, alignment: 1 */
                /* three bytes padding */
    };          /* size: 8, alignment: 4 */

    /* every object of type struct sse_t will be aligned to 16-byte boundary */
    /* (note: needs support for DR 444) */
    struct sse_t
    {
        alignas(16) float sse_data[4];
    };

    /* every object of type struct data will be aligned to 128-byte boundary */
    struct data
    {
        char x;
        alignas(128) char cacheline[128]; /* over-aligned array of char,  */
                                          /* not array of over-aligned chars */
    };

    printf(
        "%zu\n",
        alignof(x) /* Compile time alignment computation */
    );
    printf("sizeof(struct X) = %zu\n", sizeof(struct X));
    printf("alignof(struct X) = %zu\n", alignof(struct X));
    printf(
        "sizeof(data) = %zu (1 byte + 127 bytes padding + 128-byte array)\n",
        sizeof(struct data));
    printf("alignment of sse_t is %zu\n", alignof(struct sse_t));

    return 0;
}