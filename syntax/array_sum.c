/* Compile with: */
/* $ gcc -o array_sum_example -ansi -pedantic-errors -Werror array_sum.c */
/* run with: */
/* ./array_sum_example */

/* For printf */
#include <stdio.h>
/* For INT_MAX, INT_MIN */
#include <limits.h>

int array_sum(int const* array, size_t count ) {
    size_t i;
    int sum = 0;

    if(array == NULL)
        return -1; /* wrong (null) array pointer */

    for( i = 0; i < count; i++ ) {
        /*
         * clang and gcc 5 have builtins now overflows:
         * __builtin_add_overflow and
         * __builtin_mul_overflow 
         */
        if (
            (array[i] > 0 && sum > INT_MAX - array[i]) ||
            (array[i] < 0 && sum < INT_MIN - array[i])
        )
            return -1; /* overflow or underflow */
        
        sum = sum + array[i];
    }

    return sum;
}

int main( int argc, char** argv ) {
    /*  */
    int const array[] = {1,2,3,4,5};

    printf(
        "The sum is: %i\n", 
        array_sum(array, sizeof(array) / sizeof(int))
    );

    return 0;
}