Run this command: ```gcc -fcommon a.c b.c -o prog.out```

Here linking fails. Both files define strong symbols with the same name.

The function `main` is present in both files. Similarly, the variable name `int_one` is initialised in both files as well.