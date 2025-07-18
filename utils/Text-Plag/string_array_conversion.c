/*
 * Basic structure of reading the files and processing:
 *  - read_file function:
 *      -> arguments:  filename(char *), linked list(list *)
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
 */

#define MAX_SIZE 1024

int read_file(char *filename, list *l);
int read_line(int fd, char *line, int max_line_size);
int tokenize(char *line, list *l);

/*
    read_file function:
        Expects a filename and linked list as arguments
        the File is read line by line using the read_line function
        Once a line is read, it is tokenized using the tokenize function
        The tokenize function returns the number of words in the line
        The tokenize function also appends the words to the linked list
        The total number of words in the file is returned
*/

int read_file(char *filename, list *l)
{
    int token_count = 0;
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open failed");
        return errno;
    }
    char *line = (char *)malloc(sizeof(char) * MAX_SIZE);

    while (read_line(fd, line, MAX_SIZE))
    {
        // calling the tokenization function
        // line is read into the char *line varilable
        // line will be passed to the tokenize function
        token_count += tokenize(line, l);
    }
    free(line);
    close(fd);
    return token_count; // i is the length of array of strings words
}

/*
    read_line function:
        Expects a file descriptor, a line buffer and the max line size as arguments
        Reads the line from the file descriptor and stores it in the line buffer
        It also skips any random spaces or new lines
        Returns the length of the line read
*/

int read_line(int fd, char *line, int max_line_size)
{
    int length = 0;
    char ch;
    while (length < max_line_size && read(fd, &ch, 1))
    {
        if (ch != '\n')
        {
            line[length++] = ch;
        }
        else
        {
            break;
        }
    }
    line[length] = '\0';
    if (length == 0 && ch == '\n') // ignoring the empty lines but to keep continue reading the file
        return 1;
    return length;
}

// Checks if a character is punctuation
int is_punctuation(char ch)
{
    if (ch == ',' || ch == '.' || ch == ':' || ch == ';')
        return 1;
    return 0;
}

int is_space(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\v')
        return 1;
    return 0;
}

char toLower(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return ch;
    if (ch >= 'A' && ch <= 'Z')
        ch += ('a' - 'A');
    return ch;
}

/*
    tokenize function:
        Expects a line and a list as arguments
        Tokenizes the line and stores the words in the list
        Tokenization is done by separating the words by spaces and punctuation marks and newline characters
        Append Function from Linked List ADT is used to append the words to the list
        Returns the number of words tokenized
*/

int tokenize(char *line, list *l)
{
    int i = 0; // for word traversal
    int j = 0;
    int tokens = 0;

    char *word = (char *)malloc(sizeof(char) * 64);
    while (line[i] != '\0')
    {
        if (is_space(line[i]) || is_punctuation(line[i])) // check if the character is space or punctuation
        {
            if (!is_space(line[i - 1]) && !is_punctuation(line[i - 1]))
            {
                word[j] = '\0';
                append(l, word);
                j = 0;
                tokens++;
            }
            i++;
            continue;
        }
        else
        {
            word[j++] = line[i++];
        }
    }
    if (j != 0) // Append the last word which is not followed by a space or punctuation
    {
        word[j] = '\0';
        append(l, word);
        tokens++;
    }
    return tokens;
}
