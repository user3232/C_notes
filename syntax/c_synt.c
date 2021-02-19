/* 
Compiler flags to support standard:
    --std=c89
    --std=c99
To disable nonstandard extensions:
    -pedantic-errors
warnings -> errors
    -Werror
To compile this:
    $ gcc -o main -ansi -pedantic-errors -Werror c_synt.c
 */

/* 
 *  MODULE STRUCTURE:
 *  * includes
 *  * data types definitions
 *  * global variables
 *  * functions
 */

/* 
 * In case of angle brackets, the file is searched in a set
 * of predefined directories. For GCC it is usually:
 * 
 * * /usr/local/include
 * * <libdir>/gcc/target/version/include
 *
 *   Here <libdir> stands for the directory that holds
 *   libraries (a GCC setting) and is usually /usr/lib or
 *   /usr/local/lib by default.
 *
 * * /usr/target/include
 * * /usr/include
 * * Using the -I key one can add directories to this list.
 *   You can make a special include/ directory in your
 *   project root and add it to the GCC include search list.
 *
 * In case of quotes, the files are also searched in the
 * current directory.
 *
 */


#include <stdio.h>
/* for: printf, puts */
#include <stdbool.h>
/* for: bool */
#include <stdint.h>
/* for crossplatfor types: uint8_t, int_64_t, etc... */
#include <inttypes.h>
/* for printf scanf with crossplatform types */

/* 
 * Preprocessor output can be seen using:
 * $ gcc -E filename.c
 * To add definition (with value 1) to gcc:
 * $ gcc -D C99 -o main c_synt.c
 * To add definition (with value 1) to gcc:
 * $ gcc -D C99=1 -o main c_synt.c
 */



void int_types(void) {
    char number = 5;                            /* 1 Byte */
    char symbol_code = 'x';        
    char null_terminator = '\0';   

    int signed_int = 5;                         /* machine (word) dependent */
    signed int explicitly_signed_int = 5;       
    unsigned int explicitly_unsigned_int = 5;   

    short signed_short = 6;                     /* 2 Byte */
    signed short explicitly_signed_short = 6;   
    unsigned short explicitly_unsigned_short = 6;

    long signed_long = 7L;                      /* 4 Byte or 8 byte */
    signed long explicitly_signed_long = 7L;
    unsigned long explicitly_unsigned_long = 7UL;

#ifdef C99
    long long signed_realy_long = 8L;     /*8 byte - added with C99 */
    signed long long explicitly_signed_realy_long = 8L;
    unsigned long long explicitly_unsigned_realy_long = 8L;
#endif    

    bool bool_true_is_int = true;   /* = 1 (or not 0) */
    bool bool_false_is_int = false; /* = 0 */

    5;                                          /* immediate is int */
    5u;                                         /* immediate is unsigned int */
    5l;                                         /* immediate is long */
    5ul;                                        /* immediate is unsigned long */

    return ;
}

void floating_types(void) {
    /* Floating numbers are more precise */ 
    /* near 0 and less precise for big values */

    float just_float = 3.13;        /* 4 Bytes */
    double ordinary_double = 3.14;  /* 8 Bytes */

    long double c99_long_double = 3.15;  /* 80 Bits */
    return ; 
}


void string_types(void) {
    /* String literals are automatically null terminated. */
    /* 
     * The type of string literals is char*. Modifying them,
     * however, while being syntactically possible (e.g.,
     * "hello"[1] = 32), yields an undefined result. It is
     * one of the cases of undefined behavior in C
     */

    /* Strings literals become concatenced: */
    char const* string = "YO yo" " whats up"
    " who knows this will work? .."; 
    /* = "YO yo whats up who knows this will work? .." */
    /* alternatively */
    char const equivalent_string_declaration[] = 
        "YO yo whats up who knows this will work? ..";

    puts("");
    puts("******************************");
    puts("Lets print some strings:");
    puts("******************************");
    puts("");

    printf("%s\n", string);
    printf("%s\n", equivalent_string_declaration);

    return ; 
}


void casts_are_your_friends(void) {
    /* But be careful with segmentation faults */
    long d= 4;
    double e = 10.5 * (float)d; /* now d is a double */

    int f = 129;
    char g = (char)f; /* sets char with code 129 */

    /* When not sure */
    int a = 5;
    char b = 'w';
    unsigned long c = 15;
    long x = (long)a + (long)b + (long)c;

    return ;
}


int pointers_are_your_friends(int ints[], size_t sz) {
    /* pointer points to entity of some type */
    /* but every pointer is just number, on 64x86 it is 8 Byte */

    /* for every name, we can take: */
    /* address of this name using '&' */
    /* value of this name threated as pointer using '*' */

    int a = 10;
    void* pa = &a;  /* void* is type of pointer to be cast */
                    /* to other type */
    int x = 10;
    int* px = &x;   /* Took address of 'x' and assigned it to 'px' */
    *px = 42;       /* We modified 'x' here! */

    

    if ( sz == 0 ) return -1;
    return ints[0];
}

void arrays_and_initializators(void) {

    /* 
     * the arrays are just continuous memory regions holding
     * the data of the same type. There is no information
     * about type itself or about the array length. It is
     * fully a programmer’s responsibility to never address
     * an element outside an allocated array.
     *
     * Whenever you write the allocated array’s name, you
     * are actually referring to its address. You can think
     * about it as a constant pointer value.
     */

    /* This array's size is computed by compiler */
    int arr[] = {1,2,3,4,5};    /* arr actuall type is int* */
    /* This array is initialized with zeros, its size is 256 bytes */
    long array[32] = {0};       /* array actuall type is int* */
    /* 
     * As the amount of elements should be fixed, it cannot
     * be read from a variable.
     */

    /* You can address elements by index. Indices start from 0. */
    int first = array[0];       /* *array will be evaluated to first element */

#ifdef C99
    int a[8] = { [5] = 29, [1] = 15 };    /* C99 */
    /* -> {0, 15, 0, 0, 0, 29, 0, 0} */
    
    enum colors {
        RED,
        GREEN,
        BLUE,
        MAGENTA,
        YELLOW
    };
    int good[5] = { [ RED ] = 1, [ MAGENTA ] = 1 };
#endif

    return ;
}

typedef double (fun_int_to_double)(int);
/* function declaration of circle_area function using typedef! */
fun_int_to_double circle_area; 
/* function declaration of applay function */
double apply(fun_int_to_double*, int);

void functional_types(void) {

    puts("");
    puts("******************************");
    puts("Function types and higher oder functions:");
    puts("******************************");
    puts("");


    printf("%.2f\n", apply(&circle_area, 10));

    return ;
}

/* function definition or circle_area! */
double circle_area(int r) {
    return 3.14 * (double)r;
}

double apply(fun_int_to_double* f, int x) {
    return f(x);
}


void what_size(void) {
    /* sizeof operator computes in compile time */

    long static_array[] = { 1, 2, 3 };

    puts("");
    puts("******************************");
    puts("Lets print some sizes:");
    puts("******************************");
    puts("");


    printf("Sizeof(long) = %lu\n", sizeof(long));
    /* on 64 bit computer long is 8 Byte */
    printf( "Sizeof(static_array) = %lu\n", sizeof( static_array    ) ); 
    /* output: 24 */
    printf( "Sizeof(static_array[0]) = %lu\n", sizeof( static_array[0] ) ); 
    /* output: 8 */


    return ;
}

void printf_patterns(void) {
    /* printf formating placeholders have construction: */
    /* %[parameter][flags][width][.precision][length]type */
    /* https://en.wikipedia.org/wiki/Printf_format_string */

    float floatPositiveInfinity = (1.f/0.f);
    float floatNegativeInfinity = -(1.f/0.f);
    float floatPositiveNaN = (0.f/0.f);
    float floatNegativeNaN = -(0.f/0.f);

    double doublePositiveInfinity = (1.0/0.0);
    double doubleNegativeInfinity = -(1.0/0.0);
    double doublePositiveNaN = (0.0/0.0);
    double doubleNegativeNaN = -(0.0/0.0);

    char* nts = "Null terminated string\0";
    char ch = 'a';
    short sh = 2;
    long longie = 10;

#ifdef C99
    int64_t i64 = -10;
    uint64_t u64 = 100;
#endif

    puts("");
    puts("******************************");
    puts("Lets print some print formatted text:");
    puts("******************************");
    puts("");

    printf("Signed int                                   = |%i|\n", -1);
    printf("Signed int                                   = |%d|\n", -1);
    printf("Signed int (right align, min 5 chars)        = |%*i|\n", 5, -1);
    printf("Signed int (left align, min 5 chars)         = |%-*i|\n", 5, -1);
    printf("Signed int (expl sign, 0 fill, min 5 chars)  = |%+05i|\n", 1);
    printf("Signed int (expl sign, 0 fill, min 5 chars)  = |%+0*i|\n", 5, 1);
    printf("Signed int (sign place, 0 fill, min 5 chars) = |% 0*i|\n", 5, 1);
#ifdef C99
    printf("Signed int (thousands group)       = |%'i|\n", 1000); /* C99 */
    printf("Signed int from short              = | %hi |\n", sh); /* C99 */
    printf("Signed int from char               = |%hhi|\n", ch); /* C99 */
    printf( "Signed 64-bit integer (int64_t):   = |%" PRIi64 "|\n", i64 );
    printf( "Unsigned 64-bit integer (uint64_t):= |%" PRIu64 "|\n", u64 );
#endif
    printf("Signed int from long                = |%li|\n", longie);
    printf("Unsigned int                        = |%u|\n", 3);
    printf("Unsigned int hex                    = |%x|\n", 3);
    printf("Unsigned int oct                    = |%o|\n", 3);
    printf("Char                                = |%c|\n", 65);
    printf("void*                               = |%p|\n", nts);
    printf("Float                               = |%f|\n", floatPositiveNaN);
    printf("Double                              = |%f|\n", doublePositiveNaN);
    printf("Double                              = |%f|\n", 3.14152);
    printf("Double exponential                  = |%e|\n", 3.14152);
    printf("Double smart                        = |%g|\n", 3.14152);

    printf("Double (6 digs prec, min 8 chars) = |%*.*g|\n", 8, 6, 3.14152111);
    printf("Double (6 digs prec, min 8 chars) = |%8.6g|\n", 3.14152111);

    printf("Null term string   = |%s|\n", nts);

}


void constants(void) {
    int mutable_data = 5;
    int const immutable_data = 10;

    int* mutable_pointer_to_mutable_data = &mutable_data;
    int const* mutable_pointer_to_immutable_data = &immutable_data;
    
    int* const immutable_pointer_to_mutable_data = &mutable_data;
    int const* const immutable_pointer_to_immutable_data = &immutable_data;


    puts("");
    puts("******************************");
    puts("Lets experiment with const:");
    puts("******************************");
    puts("");


    /* it could be overcome by explicit casting: */
    puts("Oryginally:");
    printf("immutable_data = %i\n", immutable_data);
    
    /* (int)immutable_data = 6; */ /* wont work but */
    printf("But after pointer casts and dereferences..\n");

    puts("We have:");
    *((int*)&immutable_data) = 7; /* this mutate immutable data */
    printf("immutable_data = %i\n", immutable_data);
    
    puts("Or:");
    *((int*)immutable_pointer_to_immutable_data) = 8; /* this also */
    printf("immutable_data = %i\n", immutable_data);

    return ;
}


void data_structures(void) {
    /* (For structures) typename = struct name */
    /* so keyword struct cannot be omitted: */
    /* struct name instance_name; */
    /* typedef struct struct_tag typedef_laybel; */ 
    /* But it hides that type is struct sth */

    struct pair {int a; int b;};
    struct pair p0 = {0}; /* all filds 0 initialized */
    struct pair p1; /* who knows */
    struct pair p2 = {1, 2}; /* array like */
#ifdef C99
    struct pair p3 = {.a = 1, .b = 2}; /* C99, named */
#endif
    /* Filds can be accessed: */
    p2.a = 6;
    p2.b = 7;

    return ;
}

void data_unions(void) {
    /* Union can store one of its alternatives */
    /* Alternatives may be threated as different views on row data! */

    /* Keyword union cannot be omitted: */
    /* union name instance_name; */
    /* typedef union union_tag typedef_laybel; */ 
    /* But it hides that type is union */

    union int_or_chars {int x; char c[8];};
    union int_or_chars p0 = {0}; /* all filds 0 initialized */
    union int_or_chars p1; /* who knows */
    union int_or_chars p2 = {12345678}; /* to int */
#ifdef C99
    union int_or_chars p3 = {.x = 1}; /* C99, named */
    union int_or_chars p3 = {.c = "12345678"}; /* C99, named */
#endif
    union pixel {
        struct {
            char a,b,c;
        } named;
        char at[3];
    };
    union pixel pix;
    /* int type with values names: */
    enum light {
        LIGHT_RED,
        LIGHT_RED_AND_YELLOW,
        LIGHT_YELLOW,
        LIGHT_GREEN,
        LIGHT_NOTHING
    };
    enum light x_light = {LIGHT_RED};
    
    x_light = LIGHT_NOTHING;

    pix.named.a = 'a';
    pix.named.b = 'b';
    pix.named.c = 'c';
    pix.at[1] = (char)65;

    p1.c[4] = 'a';
    p1.x = 15;

    return ;
}


/* 
 * https://stackoverflow.com/questions/4991707/how-to-find-my-current-compilers-standard-like-if-it-is-c90-etc
 * https://stackoverflow.com/questions/15127522/how-to-ifdef-by-compilertype-gcc-or-vc
 */
void which_standard_is_used(void) {

#ifdef __clang__
/*code specific to clang compiler*/
#elif __GNUC__
/*code for GNU C compiler */
#elif _MSC_VER
/*usually has the version number in _MSC_VER*/
/*code specific to MSVC compiler*/
#elif __BORLANDC__
/*code specific to borland compilers*/
#elif __MINGW32__
/*code specific to mingw compilers*/
#endif


#ifdef __ANSI__
    puts("Using ANSI C");
#endif

#ifdef __STDC__
    puts("Using C89");
#   ifdef __STDC_VERSION__
        puts("Using C90");
#       if (__STDC_VERSION__ >= 199901L)
            puts("Using C99");
#       endif
#       if (__STDC_VERSION__ >= 201112L)
            puts("Using C11");
#       endif
#       if (__STDC_VERSION__ >= 201710L)
            puts("Using C18");
#       endif
#   endif
#endif
    return ;
}


/* 
 * 'main' is the entry point for the program, like _start in
 * assembly Actually, the hidden function _start is calling
 * 'main'.  'main' returns the 'return code' which is then
 * given to the 'exit' system.
 * 
 * Arguments are split by white spaces and passed as
 * null terminated strings in argv, count of arguments
 * is passed in argc, so for example:
 * $ ./main ls -l -a
 * will be passed as if:
 * char** argv = {"main\0", "ls\0", "-l\0", "-a\0"};
 * int    argc = 4;
 */
int main(int argc, char** argv)
{
    /* 
     * C is weakly typed, types are for interpretation not
     * documentation 
     */

    int x = 45;
    int arg_i = 0;

    which_standard_is_used();


    puts("");
    puts("******************************");
    puts("Lets print system passed arguments:");
    puts("******************************");
    puts("");

    printf("System passed %i arguments:\n", argc);
    /* iterate system passed arguments */
    arg_i = 0;
    while (arg_i < argc)
    {
        puts(argv[arg_i]);
        arg_i = arg_i + 1;
    }
    

    printf_patterns();
    what_size();
    constants();
    string_types();
    functional_types();

    return 0;
}


