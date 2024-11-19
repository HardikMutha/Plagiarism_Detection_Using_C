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
 */

#define MAX_SIZE 1024

int read_file(char *filename, list *l);
int read_line(int fd, char *line, int max_line_size);
int tokenize(char *line, list *l);

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
        // line is read into the line
        // line will be passed to the tokenize function
        token_count += tokenize(line, l);
        // we will get tokenized words string with comma separated words
    }

    return token_count; // i is the length of array of strings words
}

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

int tokenize(char *line, list *l)
{
    int i = 0; // for line traversal
    int j = 0; // for word traversal
    int tokens = 0;

    char *word = (char *)malloc(sizeof(char) * 64);
    while (line[i] != '\0')
    {
        if (is_space(line[i]) || is_punctuation(line[i]))
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
    if (j != 0)
    {
        word[j] = '\0';
        append(l, word);
        tokens++;
    }
    return tokens;
}
