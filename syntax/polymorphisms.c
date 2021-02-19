/* $ gcc -o polymorphisms -pedantic-errors -Werror polymorphisms.c */
/* run with: */
/* ./polymorphisms */


#include<stdio.h>
#include <stdbool.h>

/* *********************************** */
/* Parametric Polymorphism */
/* *********************************** */

/* Macros can be used to simulate parametric poly */

#define mystr hello
/* defines text substitution */
/* 
 * - substitution name is mystr
 * - substitution value are characters after name to
 *   end of line (which may be escaped by \<new line>)
 */

#define res(s) #s
/* Substitutions can have parameters */
/* 
 * Parameters are textualy substituted 
 * resulting text then is one more scaned
 * for substitutions.
 * 
 * Parameter reference can be substituted
 * with quotes if # is added before parameter
 * name.
 * 
 * Parameters can be concatenced with text
 * and threated as text to be once more 
 * scanned for substitutions.
 * 
 */


#define x1 "Hello"
#define x2 " World"
#define str(i) x##i
/* 
 * Parameter i is concatenced with x 
 * giving for example x1 which once more
 * will be scaned for substitutions
 * giving "Hello"
 * 
 */



#define pair(T) pair_##T
/* e.g. T = int -> pair_int */
#define any(T) pair_##T##_any
/* e.g. T = int -> pair_int_any */
#define DEFINE_PAIR(T) struct pair(T) {\
    T fst;\
    T snd;\
};\
bool any(T)(struct pair(T) pair, bool (*predicate)(T)) {\
    return predicate(pair.fst) || predicate(pair.snd); \
}
/* 
 * For T = int ->:
 * struct pair_int {
 *      int fst;
 *      int snd;
 * };
 * bool pair_int_any(struct pair_int pair, bool (*predicate)(int)) {
 *      return predicate(pair.fst) || predicate(pair.snd);
 * }
 */


DEFINE_PAIR(int)
bool is_positive( int x ) { return x > 0; }


void parametric_polymorphism(void) {
    puts(res(mystr));
    puts( str(1) );  /* str(1) -> x1 -> "Hello" */
    puts( str(2) );  /* str(2) -> x2 -> " World" */
    struct pair(int) obj;
    obj.fst = 1;
    obj.snd = -1;
    printf("%d\n", any(int)(obj, is_positive) );

    return ;
}


/* *********************************** */
/* Inclusion Polymorphism */
/* *********************************** */

/* 
 * Inclusion polymorphism is inheretance and classes 
 * which can be simulated by struct inclusion
 * and pointer casts (or void*).
 */

struct parent {
    const char* field_parent;
};
struct child {
    struct parent base;
    const char* field_child;
};
void parent_print( struct parent* this ) {
    printf( "%s\n", this->field_parent );
}


void inclusion_polymorphism(void) {
    struct child c;
    c.base.field_parent = "parent";
    c.field_child = "child";
    parent_print( (struct parent*) &c );

    return ;
}



/* *********************************** */
/* Overloading Polymorphism (C11) */
/* *********************************** */

/* 
 * The _Generic macro accepts an expression E and then many
 * association clauses, separated by a comma.  
 *
 * Each clause is of the form: 
 * 
 *   type_name: "string". 
 *
 * When instantiated, the type of E is checked against all
 * types in the associations list, and the corresponding
 * string to the right of colon will be the instantiation
 * result.
 * 
 */



#define print_fmt(x) (_Generic( (x), \
            int: "%d",\
            double: "%f",\
            default: "%x"))
#define print(x) printf( print_fmt(x), x ); puts("");

void overloading_polymorphism(void) {
    int x = 101;
    double y = 42.42;
    print(x);
    print(y);

    return;
}

/* 
 * https://stackoverflow.com/questions/4991707/how-to-find-my-current-compilers-standard-like-if-it-is-c90-etc
 */
void which_standard_is_used(void) {
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

int main(int argc, char** argv) {

    parametric_polymorphism();
    inclusion_polymorphism();
    overloading_polymorphism();

    return 0; /* normal exit code */
}