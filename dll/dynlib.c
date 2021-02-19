/* 
 * build with:
 * $ gcc -c -fPIC -o dynlib.o  dynlib.c
 * $ gcc -o dynlib.so -shared dynlib.o
 * 
 * -c -> compile
 * -fPIC -> format Position Independent Code
 * -shared -> creates dll executable
 */
#include <stdio.h>

/* declare using data from other module */
extern int global;


void libfun(int value) {
    printf( "param: %d\n", value );
    printf( "global: %d\n", global );
}