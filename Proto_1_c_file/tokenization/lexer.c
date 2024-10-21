#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"


/*
 * keywords input reading from csv
 * checking for keyword
 *
 */

const char *keywords[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "register",
    "restrict",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while",
    NULL  // Sentinel value to mark the end of the array
};

int is_keyword(char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(keywords[i], word) == 0) {
            return 1; // It is a keyword
        }
    }
    return 0; // Not a keyword
}

int is_space(char ch) {
    if(ch == ' ' || ch == '\t' || ch == '\v' || ch == '\n')
        return 1;
    return 0;
}

int is_digit(char ch) {
    if(ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

int is_alpha(char ch) {
    if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return 1;
    return 0;
}

int is_operator(char ch) {
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '|' || ch == '&' || ch == '>' || ch == '<' || ch == '=' || ch == '!' || ch == '~' || ch == '.')
        return 1;
    return 0;
}

int is_seperator(char ch) {
    if(ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']')
        return 1;
    return 0;
}

int is_punctuation(char ch) {
   if(ch == ';' || ch == ':' || ch == ',' || ch == '?' || ch == '"') 
       return 1;
   return 0;
}


// tokenization
Token get_next(const char **input) {
    Token t;
    // ignoring white space
    while(**input != '\0' && is_space(**input))
        (*input)++;
    
    // for end of file
    if(**input == '\0') {
        t.type = TOKEN_END;
        strcpy(t.val, "EOF");
        return t;
    }
    
    int len = 0;
    if(is_alpha(**input)) {
        while(is_alpha(**input) && len < MAX_TOKEN_LENGTH) {
            t.val[len++] = **input;
            (*input)++;
        }
        t.val[len] = '\0';
        t.type = (is_keyword(t.val) ? ( TOKEN_KEYWORD ) : ( TOKEN_IDENTIFIER ));
        return t;
    }
    
    if(is_digit(**input)) {            
        while(is_digit(**input) && len < MAX_TOKEN_LENGTH) {
            t.val[len++] = **input;
            (*input)++;
        }
        t.val[len] = '\0';
        t.type = TOKEN_LITERAL;
        return t;
    }
    
    if(**input == '=' && *(*input + 1) != '=') {
        t.type = TOKEN_ASSIGN;
        strcpy(t.val, "=");
        (*input)++;
        return t;
    }

    if(is_operator(**input)) {
       t.val[len++] = **input; 
       (*input)++;
       if(is_operator(*(*input + 1))) {
           t.val[len++] = **input;
           (*input)++;
       }
       t.val[len] = '\0';
       t.type = TOKEN_OPERATOR;
       return t;
    }

    if(is_seperator(**input)) {
        t.val[0] = **input;
        (*input)++;
        t.type = TOKEN_SEPERATOR;
        t.val[1] = '\0';
        return t;
    }

    if(is_punctuation(**input)) {
        t.val[len++] = **input;
        t.type = TOKEN_PUNCTUATION;
        (*input)++;
        return t;
    }
    
    if(**input == '#') {
        while(**input != '\n' && **input != '\0') {
            t.val[len++] = **input;
            (*input)++;
        }
        t.type = TOKEN_HEADER;
        return t;
    }

    t.type = TOKEN_UNKNOWN;
    t.val[len++] = **input;
    t.val[len] = '\0';
    return t;
}

int main() {
    const char *input = "int main() { printf(); return 0; }";
    const char *p = input;
    Token token;
    
    while((token = get_next(&p)).type != TOKEN_END) {
        printf("Token: Type = %d, Value = '%s'\n", token.type, token.val);
    }
    return 0;
}

