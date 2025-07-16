/*
    This mainheader.h file contains all the header files which will be required throught the project.
    This file is directly included and all the header files in the file get included.
    It is used in txt_comparison.c file.
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
#include <limits.h>
#include "../assets/TXT_ADT's/BST_ADT/bst.c"
#include "../assets/TXT_ADT's/List_ADT/linkedlist.c"
#include "./Helpers/string_array_conversion.c"
#include "./Helpers/JaccardSim.c"
#include "./Helpers/ngram.c"
#include "./Helpers/ProcessFiles.c"
#include "../lib/PDF_Parser/pdf_parser.h"
