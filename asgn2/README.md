#mathlib.h:
    A given file that prototypes for the given math functions within the assignment. Goes over the several functions utilized within the main program of the assignment.

#mathlib.c:
    A file which contains my math functions that when compiled create usable math executables. This program contains sin, cos, arcsin, arccos, arctan and log math functions created by me that are meant to mimic the original counterparts. Use make inorder to compile the file.

#mathlib-test.c:
    A file that contains the main() program and executes the functions written out within mathlib.c and compares them to the math.h functions. Compiling this allows you to run the mathlib.c program so you can test its code. Use make to compile the file, and by using “-a, -s, -c, -C, -T, -l” the user can run the above operations and by typing “-h” can get help on which commands signify what. To run the program just type ./mathlib-test.c -(whichever command).

#Makefile:
    This is a file that helps compile my program. It allows the user to clean and make files so that they are able to run. This file was given in the assignment and I have not modified it.

#README.md:
    This is the current file you are on and contains a short description about each file and how to run them.

#DESIGN.pdf:
    This is a file that contains pseudo code of the assignment as well as describing the goal of the assignment and explaining how it can be done. The design document will range through the files where code was written and how the program was executed.

#WRITEUP.pdf:
    In this pdf its contents will contain the results of my program and its tests as well as discussing my results and possible reasons for any differences. It contains segments of my executed code with explanations backing them.
