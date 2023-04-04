### README

This program will has two executables. The first will take an input file of words, seperated by newlines, and it will generate an outpute text file of an in-order and pre-order walk of the dictionary tree created by the list of words. The second executable will count the frequency of each word in an input file, adding them all to a dictionary. That dictionary will be printed to the provided outfile, listing every word in alphabetical order, each with a corresponding listed frequency of use in the input file.

Both files take two files, input and output, as the command line argument 
-> *./Order **input file** **output file***
-> *./WordFrequency **input file** **outpute file***


### Files Included:
- **WordFrequency.cpp** - Main code for the executable *./WordFrequency*
- **Order.cpp** - Main code for the executable *./Order*
- **Dictionary.cpp** - Main code for Dictionary ADT
- **Dictionary.h** - Header file for the Dictionary.cpp code.
- **DictionaryTest.cpp** - Test client for the Dictionary ADT
- **Makefile** - Makefile to make executables
- **README.md** - Table of contents for all files

### Here is a list of all make commands:
- **make**                    - makes WordFrequency
- **make DictionaryClient**   - makes DictionaryClient
- **make clean**              - removes all binaries
- **make WordFrequencyCheck** - runs WordFrequency under valgrind on Gutenberg.txt
- **make DictionaryCheck**    - runs DictionaryClient under valgrind