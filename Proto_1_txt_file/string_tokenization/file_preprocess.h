/*
 * Basic structure of reading the files and processing:
 *  - read_file function:
 *      -> arguments: fd(int), filename(char *), words(*char[]), max_words_size(int)
 *      -> return type: int(words size)
 *      -> file is opened, and will be closed at the end of the function
 *      -> internally calls the read_line function to read each line of the line rather than having to store the complete file
 *      -> each line is fed to preprocessor function called tokenize
 *      -> tokenize function returns a string containing all words in the line separated by a comma
 *      -> the comma separated words are stored in an array of strings
 * 
 * - read_line function:
 *      -> arguments: fd(int), line(char *), max_line_size(int)
 *      -> return type: int(line size)
 *      -> reading the line from provided file
 *       
 * - tokenize:
 *      -> arguments: line(char *), words(char *), max_words_size(int)
 *      -> return type: int(words size)
 *      -> leading and trailing white spaces are ignored
 *      -> all punctuation marks(',', ';', ':', '.', '-') and sigle spaces are converted to commas separating each word on the given line
 *
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


#define MAX_SIZE 1024

int read_file   (int fd, char *filename, char words[MAX_SIZE][MAX_SIZE], int max_words_size);
int read_line   (int fd, char *line, int max_line_size);
int tokenize    (char *line, char *words, int max_words_size);