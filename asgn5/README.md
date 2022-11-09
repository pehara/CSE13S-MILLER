This file contains the following:

##decrypt.c:
This file includes my implementation of my function for decrypt alongside with the main function. Within this function, the user is able to parse the commands:
    -i: specifies the input file to encrypt (default: stdin).
-o: specifies the output file to encrypt (default: stdout).
-n: specifies the file containing the public key (default: rsa.pub).
-v: enables verbose output.

##encrypt.c:
-h: displays program synopsis and usage.
This file includes my implementation and main() function for the encrypt program.
-i: specifies the input file to encrypt (default: stdin).
-o: specifies the output file to encrypt (default: stdout).
-n: specifies the file containing the public key (default: rsa.pub).
-v: enables verbose output.
-h: displays program synopsis and usage.

##keygen.c:
This contains the implementation and main() function for the keygen program.
-b: specifies the minimum bits needed for the public modulus n(default: 1024).
-i: specifies the number of Miller-Rabin iterations for testing primes (default: 50).
-n pbfile: specifies the public key file (default: rsa.pub).
-d pvfile: specifies the private key file (default: rsa.priv).
-s: specifies the random seed for the random state initialization (default: the seconds since the UN I X epoch, given by time(NULL)).
-v: enables verbose output.
-h: displays program synopsis and usage.

##numtheory.c: 
This contains the implementations of the number theory functions.

##numtheory.h: 
This specifies the interface for the number theory functions.

##randstate.c: 
This contains the implementation of the random state interface for the RSA library and number theory functions.

##randstate.h: 
This specifies the interface for initializing and clearing the random state.

##rsa.c: 
This contains the implementation of the RSA library.

##rsa.h: 
This specifies the interface for the RSA library.

##Makefile:
CC = clang must be specified.
CFLAGS = -Wall -Wextra -Werror -Wpedantic must be specified.
pkg-config to locate compilation and include flags for the GMP library must be used.
make must build the encrypt, decrypt, and keygen executables, as should make all.
make decrypt should build only the decrypt program.
make encrypt should build only the encrypt program.
make keygen should build only the keygen program.
make clean must remove all files that are compiler generated.
make format should format all your source code, including the header files.

##README.md: 
This must use proper Markdown syntax and describe how to use your program and Makefile. It should also list and explain any command-line options that your program accepts. Any false positives reported by scan-build should be documented and explained here as well. Note down any known bugs or errors in this file as well for the graders.

##DESIGN.pdf: 
This document must be a proper PDF. This design document must describe your design and design process for your program with enough detail such that a sufficiently knowl- edgeable programmer would be able to replicate your implementation. This does not mean copy-ing your entire program in verbatim. You should instead describe how your program works with supporting pseudocode

