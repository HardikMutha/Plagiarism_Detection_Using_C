/*
 * Basic structure of reading the files and processing:
 *  - read_file function:
 *      -> arguments: fd(int), filename(char *), words(*char[]), max_words_size(int)
 *      -> return type: int(words size)
 *      -> file is opened, and will be closed at the end of the function
 *      -> internally calls the read_line function to read each line of the line rather than having to store the complete file
 *      -> each line is fed to preprocessor function called tokenize
 *      -> tokenize function returns a string containing all words in the line seperated by a comma
 *      -> the comma seperated words are stored in an array of strings
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
 *      -> all punctuation marks(',', ';', ':', '.', '-') and sigle spaces are converted to commas seperating each word on the given line
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



int main(int argc, char *argv[]) {
    int fd = 0;
    char *filename, words[MAX_SIZE][MAX_SIZE];
    filename = (char *)malloc(sizeof(char) * 32);
    
    if(argc != 3) {
        printf("files not provided\n");
        return 0;
    }
    // tokenization of first file:
    strcpy(filename, argv[1]);
    int words1 = read_file(fd, filename, words, MAX_SIZE); 
    
    for(int i = 0; i < words1; i++) {
        printf("%s\n", words[i]);
    } 

    free(filename);
    return 0;
}


int read_file(int fd, char *filename, char words[MAX_SIZE][MAX_SIZE], int max_words_size) {
    int i = 0;
    fd = open(filename, O_RDONLY);
    if(fd == -1) {
        perror("open failed");
        return errno;
    }
    char *line = (char *)malloc(sizeof(char) * MAX_SIZE);
    
    while(read_line(fd, line, MAX_SIZE)) {
        // calling the tokenization function  
        // line is read into the line
        // line will be passed to the tokenize function
        tokenize(line, words[i], MAX_SIZE);
        // we will get tokenized words string with comma seperated words
        i++;
    }

    return i; // i is the length of array of strings words
}


int read_line(int fd, char *line, int max_line_size) {
    int length = 0; 
    char ch;
    while(length < max_line_size && read(fd, &ch, 1)) {
        if(ch != '\n') {
            line[length++] = ch;
        } else {
            break;
        }
    }

    line[length] = '\0';
    return length;
}

int is_punctuation(char ch) {
    if(ch == ',' || ch == '.' || ch == ':' || ch == ';')
        return 1;
    return 0;
}

int is_space(char ch) {
    if(ch == ' ' || ch == '\t' || ch == '\v')
        return 1;
    return 0;
}

char toLower(char ch) {
    if(ch >= 'a' && ch <= 'z')
        return ch;
    if(ch >= 'A' && ch <= 'Z')
        ch += ('a' - 'A');
    return ch;
}


int tokenize(char *line, char *words, int max_words_size) {
    int i = 0; // for line traversal
    int j = 0; // for words (string) traversal
    while(line[i] != '\0') {
        if(is_space(line[i]) || is_punctuation(line[i])) {
            // to ignore more than one white space
            // while(line[i] == ' ' || line[i] == '\t' || line[i] == '\v')
            //   i++;
            if(j != 0 && words[j - 1] != ',') {
                words[j++] = ',';
            }
            i++;
        }
        else {
            words[j++] = toLower(line[i++]);
        }
    }
    words[j] = '\0'; // words string contains the words in line(string) seperated by comma
    return j;
}
