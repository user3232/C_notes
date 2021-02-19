

# References

* C language standard:
  * http://www.open-std.org/jtc1/sc22/wg14/www/standards.html
  * [offline](references/C11_language_standard_-_n1570.pdf)
* ...


# Accessing Code from Other Files

If object .o use dynamic libraries, those can be listed
using `ldd object.o`. Command ldd prints shared object dependencies.


# Declarations

Everything before use must defined, but if only pointers are
used it may be declared, because pointers are different
entities with known properties (every pointer have same size
and structure on machine).

Functions are pointers, so declaration is enough to use function
until definition appears.

Structures are not only pointers, so after declaration,
only pointers to structure can be used (no instantation or
dereference possible).

## Static

Every variable outside functions is global, seen in
every module.

But:
* declaring global variable static, makes it private to module,
* declaring local  variable static, makes it private to function.


## Functions from Other Files

To perform a call, you have to add the called function’s
prototype to the current file.

Each code file is a separate module and thus is compiled
independently, just as in assembly. A .c file is translated
into an object file (ELF).

All functions becomes global symbols.

Linker is responsible of correct addressing.


## Data in Other Files

If there is a global variable defined in other .c file that
we want to address, it should be declared, preferably, but
not necessarily, with `extern` keyword. You should not
initialize extern variables; otherwise, compiler issues a
warning.

**The C standard marks the keyword extern as optional.**
**But it is very usefull for documentation.**

It works that every .c file mapped to .o file have
have global address of variable (assembly of .o name
this global common C for owner, and other .o files
mark it as global data D).

Linker is responsible to create one variable in executable
and provide correct address and check that it is only
once initialized. 


## Linkage

An identifier declared in different scopes or in the same
scope more than once can be made to refer to the same object
or function by a process called linkage.

**Each identifier (variable or a function name)** 
**has an attribute called linkage.**:
* No linkage, which corresponds to local (to a block) variables.
* External linkage, which makes an identifier available to
  all modules that might want to touch it. This is the case
  for global variables and any functions.
  * All instances of a particular name with external linkage
    refer to the same object in the program.
  * All objects with external linkage must have one and only
    one definition. However, the number of declarations in
    different files is not limited.
* Internal linkage, which restricts the visibility of the
  identifier to the .c file where it was defined.
  
Language entities and the linkage types:
* Regular functions and global variables — external linkage.
* Static functions and static global variables — internal linkage.
* Local variables (static or not) — internal linkage.


# Syntax elements

## Pointer Arithmetic and void*

For `void*` pointer pointer arithmetic is forbidden.
`void*` only stores memory location.

```C
void*  a = (void*)4;
short* b = (short*) a;
b ++;                   /* correct, b = 6 */
b = a;                  /* correct */
a = b;                  /* correct */
```

For (not `void*`) pointers only following operations are
allawed:

* Add or subtract integers (also negatives)
  * The size of the element we are pointing at matters. By
    adding or subtracting an integer value X from the
    pointer of type T * , we, in fact, change it by 
    `X * sizeof(T)`.
* Take its own address. If the pointer is a variable, it is
  located somewhere in memory too. So, it has an address on
  its own! Use the & operator to take it.
* Dereference, which is a basic operation that we have also
  seen. We are taking a data entry from memory starting at
  the address, stored in the given pointer.  The * operator
  does it.
* Compare (with <, >, == and alike)
  * We can compare two pointers. The result is only defined
    if they both point to the same memory block (e.g., at
    different elements of the same array). Otherwise the
    result is random, undefined by the language standard.
* Subtract another pointer.
  * If and only if we have two pointers, which are certainly
    pointing at the contiguous memory block, then by
    subtracting a smaller valued one from a greater valued
    one we get the amount of elements between them. For
    pointers x and y, we are talking about a range of
    elements from *x inclusive to *y exclusive (so x − x =
    0).
  * Starting from C99, the type of the expression `ptr2 - ptr1` 
    is a special type `ptrdiff_t`. It is a signed type of
    the same size as size_t.
  * Note, that the result is different from the amount of
    bytes between * x and * y! Result of subtraction is the
    amount of bytes divided by an element size.
  * `ptrdiff_t` should always go in par with size_t, because
    only then their sizes are guaranteed to be the same


# Semantics

Benjamin C. Pierce. Types and programming languages.
Cambridge, MA: MIT Press, 1st ed. 2002.

Glynn Winskel. The formal semantics of programming
languages: an introduction. Cambridge, MA: MIT Press. 1993.


The language semantics is a correspondence between the
sentences as syntactical constructions and their meaning.
Each sentence is usually described as a type of node in the
program abstract syntax tree. This description is performed
in one of the following ways:

* The current program state can be described with a set of
  logical formulas. Then each step of the abstract machine
  will transform these formulas in a certain way.
* Denotationally. Each language sentence is mapped into a
  mathematical object of a certain theory (e.g., domain
  theory). Then the program effects can be described in
  terms of this theory. It is of a particular interest when
  reasoning about program behavior of different programs
  written in different languages.
* Operationally. Each sentence produces a certain change of
  state in the abstract machine, which is subject to
  description. The descriptions in the C standard are
  informal but resemble the operational semantic description
  more than the other two.




## Streams

`man fread , fwrite , fprintf , fscanf , fopen , fclose , fflush`


# Pragmatics

<http://www.catb.org/esr/structure-packing/>

## Data Structure Padding

For structures, the alignment exists in two different senses:

* The alignment of the structure instance itself. It affects
  the address the structure starts at.
* The alignment of the structure fields. Compiler can
  intentionally introduce gaps between structure fields in
  order to make accesses to them faster. Data structure
  padding relates to this.

There are several instances in which we should be aware of it:

* You might want to change the trade-off between memory
  consumption and performance to lesser memory consumption.
  Imagine you are creating a million copies of structures
  and every structure wastes 30% of its size because of
  alignment gaps. Forcing the compiler to decrease these
  gaps will then lead to a memory usage gain of 30% which is
  nothing to sneeze at. It also brings benefits of better
  locality which can be far more beneficial than the
  alignment of individual fields.
* Reading file headers or accepting network data into
  structures should take possible gaps between structure
  fields into account. For example, the file header contains
  a field of 2 bytes and then a field of 8 bytes. There are
  no gaps between them. Now we are trying to read this
  header into a structure, as shown in Listing 12-12.

<https://en.wikipedia.org/wiki/Data_structure_alignment>

To maintain proper alignment the translator normally inserts
additional unnamed data members so that each member is
properly aligned. In addition, the data structure as a whole
may be padded with a final unnamed member. This allows each
member of an array of structures to be properly aligned.

Padding is only inserted when a structure member is followed
by a member with a larger alignment requirement or at the
end of the structure. By changing the ordering of members in
a structure, it is possible to change the amount of padding
required to maintain alignment.

Examples:
```Cpp
struct MixedData
{
    char Data1;
    short Data2;
    int Data3;
    char Data4;
};

struct MixedData_Compiled  /* After compilation in 32-bit x86 machine */
{
    char Data1;       /* 1 byte */
    char Padding1[1]; /* 1 byte for the following 'short' to be */ 
                      /* aligned on a 2 byte boundary assuming that the */ 
                      /* address where structure begins is an even number */
    short Data2;      /* 2 bytes */
    int Data3;        /* 4 bytes - largest structure member */
    char Data4;       /* 1 byte */
    char Padding2[3]; /* 3 bytes to make total size of the structure 12 bytes */
};


```

## Aligement in C11

C11 introduced a standardized way of alignment control. It
consists of:

* Two keywords:
  * _Alignas
  * _Alignof
* stdalign.h header file, which defines preprocessor aliases
  for _Alignas and _Alignof as alignas and alignof
* aligned_alloc function.


Alignment is only possible to the powers of 2: 1, 2, 4, 8, etc.


```Cpp

#include <stdio.h>
/* For printf */
#include <stdalign.h>
/* alignment aliases */

int main(void) {
  alignas( 8 ) short x; /* Aligns short at 8 Bytes */

  /* objects of struct X must be allocated at 4-byte boundaries */
  /* because X.n must be allocated at 4-byte boundaries */
  /* because int's alignment requirement is (usually) 4 */
  struct X {
    int n;  /* size: 4, alignment: 4 */
    char c; /* size: 1, alignment: 1 */
    /* three bytes padding */
  };  /* size: 8, alignment: 4 */ 

  /* every object of type struct sse_t will be aligned to 16-byte boundary */
  /* (note: needs support for DR 444) */
  struct sse_t
  {
    alignas(16) float sse_data[4];
  };

  /* every object of type struct data will be aligned to 128-byte boundary */
  struct data {
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
    sizeof(struct data)
  );
  printf("alignment of sse_t is %zu\n", alignof(struct sse_t));


  return 0;
}
```

### Some comment:

[See StackOverflow Applying alignas() to an entire struct in C](https://stackoverflow.com/questions/46518575/applying-alignas-to-an-entire-struct-in-c)

C11 is not very clear on these things, but a consensus has
emerged how this is to be interpreted. C17 will have some of
this clarified. The idea of not allowing types to be aligned
is that there should never be different alignment
requirements for compatible types between compilation units.
If you want to force the alignment of a struct type, you'd
have to impose an alignment on the first member. By that
you'd create an incompatible type.

