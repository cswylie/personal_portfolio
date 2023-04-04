### README

This program will calculate arithmetic for large integers, adding, subtracting, and multiplying them as necessary. Arithmetic will take two numbers, A & B, seperated by an empty line in a textfile and compute: 𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴𝐵, 𝐴2, 𝐵2, 9𝐴^4 + 16𝐵^5

It takes two files, input and output, as the command line argument -> *./Arithmetic <input file> <output file>*

### Files Included:
- **List.cpp** - Main code for List ADT
- **List.h** - Header file for the List.cpp code.
- **ListTest.cpp** - Test client for the List ADT
- **Makefile** - Makefile to make executables
- **Arithmetic.cpp** - Main code for the shuffle executable *./Arithmetic*
- **BigInteger.cpp** - Main code for the BigInteger ADT
- **BigInteger.h** - Header code for the BigInteger.cpp code.
- **BigIntegerTest.cpp** - Test code for the BigInteger ADT
- **README.md** - Table of contents for all files

### Here is a list of all make commands:
- **make**              -       makes Arithmetic
- **make BigIntegerClient**  -  makes BigIntegerClient
- **make ListClient**     -     makes ListClient
- **make clean**          -     removes all binaries
- **make ArithmeticCheck**   -  runs Arithmetic in valgrind on in4 junk4
- **make BigIntegerCheck**   -  runs BigIntegerTest in valgrind
- **make ListCheck**     -      runs ListTest in valgrind