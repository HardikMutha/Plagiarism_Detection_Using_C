/*
	This Script is used to create a lexical analyser using the flex tool
	It assumes that flex tool is installed and accessible via the CLI

	All the Commands are run using the system() method in <stdlib.h>
	The Output of the script is a file "lexer" which is the lexical analyser
*/

/*
	Steps to use the script:
	First Compile the code using the gcc compiler
	an executable is generated
	
	This executable expects two arguments filename1 and filename2
	filename1 -> This is the filename with the extension .l and contains the rules of the grammar
		  	  -> This file is used by flex_tool to generate a file named "lexer" which is the final lexer tool

	filename2 -> This is the filename on which the lexer should act upon i.e our source file
				 The command which the script automatically runs is
				 ./lexer filename2
				 The expected output is then achieved
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Invalid Number of Arguments\n");
		return -1;
	}
	char *filename1 = argv[1];
	char *filename2 = argv[2];
	char a[128];
	int i;
	strcpy(a, "flex ");
	for (i = 0; i < strlen(filename1); i++)
	{
		a[i + 5] = filename1[i];
	}
	a[i + 5] = '\0';
	int result = system(a);									// command: flex filename1
	int result2 = system("gcc lex.yy.c -o lexer -w"); 		// command: gcc lex.yy.c -o lexer -w
	strcpy(a, "./lexer ");
	int len = strlen(a);
	for (i = 0; i < strlen(filename2); i++)
	{
		a[i + len] = filename2[i];
	}
	a[i + len] = '\0';
	int result3 = system(a);								// command: ./lexer filename2
	if (result == -1 || result2 == -1 || result3 == -1)
	{
		perror("Error Running the Script");
		return errno;
	}
	return 0;
}
