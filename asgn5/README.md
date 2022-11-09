This file contains the following:

##decrypt.c:
This file includes my implementation of my function for decrypt alongside with the main function. Within this function, the user is able to parse the commands:
using ./decrypt -case
-i: specifies the input file to encrypt (default: stdin).
-o: specifies the output file to encrypt (default: stdout).
-n: specifies the file containing the public key (default: rsa.pub).
-v: enables verbose output.

##encrypt.c:
This program contains the implementation of my function for encrypt alongside with the main function i have writtedn. With this the user can parse the following commands:
using ./encrypt -case
-h: displays program synopsis and usage.
This file includes my implementation and main() function for the encrypt program.
-i: specifies the input file to encrypt (default: stdin).
-o: specifies the output file to encrypt (default: stdout).
-n: specifies the file containing the public key (default: rsa.pub).
-v: enables verbose output.
-h: displays program synopsis and usage.

##keygen.c:
This contains the implementation and main() function for the keygen program.
using ./keygen -case
-b: specifies the minimum bits needed for the public modulus n(default: 1024).
-i: specifies the number of Miller-Rabin iterations for testing primes (default: 50).
-n pbfile: specifies the public key file (default: rsa.pub).
-d pvfile: specifies the private key file (default: rsa.priv).
-s: specifies the random seed for the random state initialization (default: the seconds since the UN I X epoch, given by time(NULL)).
-v: enables verbose output.
-h: displays program synopsis and usage.

##numtheory.c: 
This contains my implementation of the number theory functions.

##numtheory.h: 
This header file specifies the interface for the number theory functions.

##randstate.c: 
This file contains the implementation of my random state interface for the RSA library and number theory functions.

##randstate.h: 
This header file specifies the interface for initializing and clearing the random state.

##rsa.c: 
This contains the implementation of the RSA library.

##rsa.h: 
This header file specifies the interface for the RSA library.

##Makefile:
This file compiles all the other .c files so that they are executable and run together to execute keygen, encrypt and decrypt.

##README.md: 
A file containg the proper markdown syntax that describes how to use my program and all the contents of my file.

##DESIGN.pdf: 
This document has a written explanation for all the written portions of code and how I went about creating them and what their purpose is. It provides enough information to replicate it.
