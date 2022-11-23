1. banhammer.c: This file contains the main program which is executable and can be tested by using the .banhammer command after compiling. Using the helper function which can be accessed by using ./banhammer -h allows the user to print out the program's usage, the size of the program, and the size specified for the bloom filter, enabling the move to front rule and print the overall stats of the function.

2. messages.h: This file defines the different misspeak, bad speak and good speak messages used within the main banhammer code, the code is not supposed to be modified.


3. cityhash.h: This code was given to us and contains the implementation of the hash functions header files, we can not modify this file. 


4. cityhash.c:  This code was given to us and contains the implementation of the hash function, we can not modify this file. 


5. ht.h:   This file was given to us and defines the interface for the hash table ADT, we are not permitted to modify this file.

6. ht.c: This file contains the implementation of the hash table ADT, written by us to be used in our other programs.

7. ll.h: This program defines the interface for the linked list ADT, which we are not permitted to change.

8. ll.c: This program contains the implementation of our linked list ADT.

9. node.h: This program defines the interface for the node ADT, Which we are not permitted to adjust.

10. node.c: This file contains the implementation of our node ADT which helps us with several other functions.

11. bf.h: this program definesthe interface for the Bloom filter ADT, which we are not permitted to adjust.

12. bf.c: This file contains the implementation of my Bloom filter ADT.

13. bv.h: this file defines the interface for the bit vector ADT, which we are not permitted to change.

14. bv.c: this program contains the implementation of my bit vector ADT.

15. parser.h: This file defines the interface for the parsing module which we are not permitted to change.

16. parser.c: this program contains the implementation of my parsing module.

17. Makefile: This is a file that will allow the grader to type make to compile your program. I was tasked with creating my own make file for this assignment which can be used as normal with make and make clean. It completes the following: 
• CC=clang must be specified.
• CFLAGS=-Wall -Wextra -Werror -Wpedantic must be included.
• make should build the banhammer executable, as should make all.
• make clean must remove all files that are compiler generated except the executable.
• make spotless must remove all files that are compiler generated as well as the executable.
• make format should format all your source code, including the header files.


18. README.md: This file contains the proper markdown syntax for all my files. It includes a short description of each program alonside with any of the command line options for the main program. It should also contain any false positives recorded. 

19. DESIGN.pdf: This is a file that contains the design process of the code showcase, it is in pdf form and goes into depth about what each line of my code achieves. It helps support my knowledge of the assignment.  

20. WRITEUP.pdf: This file contains an answer to my prelab question and any supporting statistics for my submission. 
