1. encode.c: This file contains my implementation of the Huffman encoder. In order to use the file the following commands can be executed by the user:    
    -h: Prints a help message explaining the program's purpose and the options it accepts, then exits the program.
 -i infile: Specifies the input file to encode using Huffman coding. The default input should be set as stdin.
 -o outfile: Specifies the output file to write the compressed input to. The default output should be set as stdout.
-v: Prints compression statistics to stderr. These statistics include the uncompressed file size, the compressed file size, and space-saving.

2. decode.c: This file contains my implementation of the Huffman decoder.In order to use the file the following commands can be executed by the user:
     -h: Prints out a help message describing the purpose of the program and the command-line options it accepts, exiting the program afterwards.
-i infile: Specifies the input file to decode using Huffman coding. The default input should be set as stdin.
-o outfile: Specifies the output file to write the decompressed input to. The default output
should be set as stdout.
-v: Prints decompression statistics to stderr. These statistics include the compressed file size, the decompressed file size, and space-saving.

3. defines.h: This file contains the macro definitions used throughout the assignment. This file is given to us and should not undergo any modifications.

4. header.h: This contains the struct definition for a file header. This file is given to us and should not undergo any modifications.

5. node.h: This file contains the node ADT interface. This file will be provided. This file is given to us and should not undergo any modifications.

6. node.c: This file contains my implementation of the node ADT.

7. pq.h: This file contains the priority queue ADT interface. This file will be provided. This file is given to us and should not undergo any modifications.

8. pq.c: This file contains my implementation of the priority queue ADT. I have defined my 
priority queue struct in this file.

9. code.h: This file contains the code ADT interface. This file will be provided. This file is given to us and should not undergo any modifications.

10. code.c: This file contains my implementation of the code ADT.

11. io.h: This file contains the I/O module interface. This file will be provided. This file is given to us and should not undergo any modifications.
this file.

12. io.c: This file contains my implementation of the I/O module.

13. stack.h: This file contains the stack ADT interface. This file will be provided. This file is given to us and should not undergo any modifications.

14. stack.c: This file contains my implementation of the stack ADT. I have defined my stack
struct in this file.

15. huffman.h: This file contains the Huffman coding module interface. This file is given to us and should not undergo any modifications.

16. huffman.c: This file contains my implementation of the Huffman coding module interface.

17. Makefile: This file contains the implementation of my makefile which compiles my executables and then cleans them up afterwards.

18. README.md: This must be in Markdown. This describes my program's usage and any possible false positives that are reported. Such as my priority queue which I believe is reporting back incorrect nodes.

19. DESIGN.pdf: This must be a PDF. The design document contains my written explanation of the process I underwent for my code and contains pseudo-code that makes it easy to comprehend.
