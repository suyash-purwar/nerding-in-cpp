Run this: `gcc -fcommon a.c b.c -o ./prog.out`

Note: Program will not compile without the `-fcommon` flag.

The `-fcommon` flag signals compiler to put uninitialised global variables in the `COMMON` section instead of `.bss` section.

In modern compilers, the `-fno-common` flag is used by default. It ensures that an error is raised whenever a duplicate global variable is declared. We are using `-fcommon` to disable this behaviour and want our linker to do the symbol resolution based on the rules.

In our program:
- File `a.c` defines a strong symbol ->`int x = 2902`
- File `b.c` defines a weak symbol -> `int x`. It also defines a function that mutates the value of this variable

As per the symbol resolution, the linker respects the declaration in `a.c`. So, variable `x` points to 2902 initially. In the main function, the function `some_random_function` is invoked which changes the value of variable `x` to 1000.
