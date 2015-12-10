### To compile an ordinary c++ file using *cl*

`cl -EHsc <name-of-file>.cpp -Fe<name-of-output-file>.exe`

Example:
* `cl -EHsc BigInt.cpp -Fe'The output file.exe'` will create `The output file.obj` and `The output file.exe`.
* `cl -EHsc BigInt.cpp` will create `BigInt.obj` and `BigInt.exe`.

Note that the single-quotation marks are needed only if the output file has spaces in them. Do not add them for files that are just one word long.

### To run the executable

`'.\Name of Executable.exe'`

Example:
* `'.\The output file.exe'` will run the compiled executable of `BigInt.cpp` in the first example.
* `.\BigInt.exe` will run the compiled executable of `BigInt.cpp` in the second example.


Note that `cl` is the VC++ C/C++ optimizing compiler command.
