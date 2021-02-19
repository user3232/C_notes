/* 
 * build with:
 * $ gcc -c  -o mainlib.o mainlib.c    # build object
 * $ gcc -o main  mainlib.o dynlib.so  # build executable
 * 
 */


/* declare using function from other module */
extern void libfun( int value );

int global = 100;

int main( void ) {
    libfun( 42 );
    return 0;
}