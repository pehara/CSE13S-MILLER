//Contains the implementation of the parsing module.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "parser.h"

#define MAX_PARSER_LINE_LENGTH 1000

struct Parser {
    FILE *f;
    char current_line[MAX_PARSER_LINE_LENGTH + 1];
    uint32_t line_offset;
};

//constructor for parser
Parser *parser_create(FILE *f) {

    Parser *p = (Parser *) malloc(sizeof(Parser));
    if (p) {
        p->f = f;
        memset(p->current_line, 0, MAX_PARSER_LINE_LENGTH);
        p->line_offset = 0;
    }

    return p;
}

// destructor for parser
void parser_delete(Parser **p) {
    free(p);
    p = NULL;
}

//take a pointer blah
bool next_word(Parser *p, char *word) {
    uint32_t i = 0;
    char current_line[MAX_PARSER_LINE_LENGTH + 1];
    memset(current_line, 0, MAX_PARSER_LINE_LENGTH);

    // Read a line
    fgets(p->current_line, MAX_PARSER_LINE_LENGTH, p->f);
    //printf("%s", p->current_line);

    // Increment offset
    p->line_offset++;

    // Convert all to lower case
    while(p->current_line[i] ) {
      current_line[i] = (tolower(p->current_line[i]));
      i++;
    }

    // Check for word found
    if (i) {
        // Copy parser word into word
        memcpy(word, current_line, i);
        printf("\nNext word 1");
        return 1;//true
    } else {
    	printf("\nNext word 0");
        return 0;//false
    }

}
