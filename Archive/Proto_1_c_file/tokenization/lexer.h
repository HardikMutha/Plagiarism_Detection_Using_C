/*
 * Graph of functions:
 *      -> each node of graph will be a tree of code blocks
 *          -> each code block will have head as condition or declaration (etc)
 *          -> followed by next node as the block of code inside
 *      -> links will be of which function is calling which function
 *
 *
 * So my doubt is should I simply return one long string as the source code from 
 * read_file and pass it to the beautifier
 *
 * 
 * I guess i should cuz like read_file technically should only be reading file and
 * storing it into the string or something of that sorts
 *
 *
 */


/*
 * functions
 *      - tokenize    
 *      - get_next_token
 *
 */


#define MAX_TOKEN_SIZE      64
#define MAX_TOKEN_LENGTH    128

typedef enum {
    TOKEN_END = 0,          // end of file '\0'
    TOKEN_KEYWORD,          // { int, float, char, ... }
    TOKEN_IDENTIFIER,       // { variables }
    TOKEN_LITERAL,          // { numbers, values }
    TOKEN_ASSIGN,           // { = }
    TOKEN_OPERATOR,         // { +, -, /, *, |, &, >, <, ||, && }
    TOKEN_PUNCTUATION,      // { ',', ';', '':', ... }
    TOKEN_HEADER,           // starting with # (whole line should be ignored)
    TOKEN_SEPERATOR,       // { '(', ')', '{', '}', '[', ']' }
    TOKEN_UNKNOWN           //NULL
} Token_type;

typedef struct {
    Token_type type;
    char val[MAX_TOKEN_SIZE];
} Token;

Token get_next(const char **input);
