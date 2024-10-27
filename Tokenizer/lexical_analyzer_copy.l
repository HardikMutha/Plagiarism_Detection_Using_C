%{

int total =0 ;

/* typedef enum { */
/*     TOKEN_PREPROCESS, */
/*     TOKEN_DELIMITE */
/*     TOKEN_ASSIGN, */
/*     TOKEN_OPERATOR, */
/*     TOKEN_KEYWORD, */
/*     TOKEN_FUNCTION */
/* } TokenType; */

/* typedef struct Token { */
/*     char token_val[32]; */
/*     TokenType token_type; */
/*     struct Token *next; */
/* } Token; */
%}

%option noyywrap




%%




#.* {total++; fprintf(yyout, "Preprocessor %s\n",yytext);}

[''|,|(|)|.|_] {total++; fprintf(yyout,"Delimiter %s\n",yytext);}

[;|{|}] {total++; fprintf(yyout, "SpDelim %s\n",yytext);}

[[]] {total++; fprintf(yyout,"Delimiter %s\n",yytext);}

"#"|"@"|"$"|"^"|"%"|"^"|"&" {total++; fprintf(yyout,"SpecialCharacters %s\n",yytext);}

"["|"]" {total++; fprintf(yyout,"Delimiter %s\n",yytext);}


"="  {total++; fprintf(yyout,"Assign %s\n",yytext);}


"+"|"-"|"*"|"/"  {total++; fprintf(yyout,"Arithmatic %s\n",yytext);}

"&&"|"||"|"!"|"^"  {total++; fprintf(yyout,"Logical %s\n",yytext);}

"<="|">="|"++"|"!="|"=="|"<"|">"  {total++; fprintf(yyout,"Relational %s\n",yytext);}

("int")|("if")|("else")|("while")|("do")|("break")|("continue")|("double")|("float")|("return")|("EOF") {total++; fprintf(yyout,"Keyword %s\n",yytext);}

("return")|("char")|("case")|("sizeof")|("long")|("short")|("typedef")|("switch")|("unsigned")|("void")|("static")|("struct")|("goto") {total++; fprintf(yyout,"Keyword %s\n",yytext);}

[a-zA-Z_][a-zA-Z0-9_]*\( {total++; fprintf(yyout,"Function %s\n",yytext);}

[0-9]*"."[0-9]+ {total++; fprintf(yyout,"Fraction %s\n", yytext);} 

[-][0-9]*"."[0-9]+ {total++; fprintf(yyout,"NegativeFraction %s\n", yytext);} 

[0-9]+ {total++; fprintf(yyout,"Integer %s\n",yytext);}

"-"[0-9]+ {total++; fprintf(yyout,"NegativeInteger %s\n",yytext);}

["]([^"\\\n]|\\.|\\\n)*["] {total++; fprintf(yyout,"String %s\n",yytext);}

"//".*" "*    {total++; fprintf(yyout,"Commment %s\n",yytext);}

\/\*(.*\n)*.*\*\/    {total++; fprintf(yyout,"Comment %s\n",yytext);}

("CHAR_BIT")|("SCHAR_MIN")|("SCHAR_MAX")|("UCHAR_MAX")|("CHAR_MIN")|("CHAR_MAX")|("MB_LEN_MAX")|("SHRT_MIN")|("SHRT_MAX")|("USHRT_MAX")|("INT_MIN")|("INT_MAX")|("UINT_MAX")|("LONG_MIN")|("LONG_MAX")|("ULONG_MAX")|("LLONG_MIN")|("LLONG_MAX")|("ULLONG_MAX")|("WORD_BIT")|("LONG_BIT")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("EOF")|("FOPEN_MAX")|("FILENAME_MAX")|("L_tmpnam")|("TMP_MAX")|("BUFSIZ")|("SEEK_SET")|("SEEK_CUR")|("SEEK_END")|("_IOFBF")|("_IOLBF")|("_IONBF")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("EXIT_SUCCESS")|("EXIT_FAILURE")|("RAND_MAX")|("MB_CUR_MAX")|("NULL")|("SIZE_MAX")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("M_PI")|("M_E")|("M_LOG2E")|("M_LOG10E")|("M_LN2")|("M_LN10")|("M_PI_2")|("M_PI_4")|("M_1_PI")|("M_2_PI")|("M_2_SQRTPI")|("M_SQRT2")|("M_SQRT1_2")|("HUGE_VAL")|("INFINITY")|("NAN")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("EPERM")|("ENOENT")|("ESRCH")|("EINTR")|("EIO")|("ENXIO")|("E2BIG")|("ENOEXEC")|("EBADF")|("ECHILD")|("EAGAIN")|("ENOMEM")|("EACCES")|("EFAULT")|("EBUSY")|("EEXIST")|("EXDEV")|("ENODEV")|("ENOTDIR")|("EISDIR")|("EINVAL")|("ENFILE")|("EMFILE")|("ENOTTY")|("ETXTBSY")|("EFBIG")|("ENOSPC")|("ESPIPE")|("EROFS")|("EMLINK")|("EPIPE")|("EDOM")|("ERANGE")|("EDEADLK")|("ENAMETOOLONG")|("ENOLCK")|("ENOSYS")|("ENOTEMPTY")|("EILSEQ")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("O_RDONLY")|("O_WRONLY")|("O_RDWR")|("O_CREAT")|("O_EXCL")|("O_NOCTTY")|("O_TRUNC")|("O_APPEND")|("O_NONBLOCK")|("O_DSYNC")|("O_SYNC")|("O_RSYNC")|("F_DUPFD")|("F_GETFD")|("F_SETFD")|("F_GETFL")|("F_SETFL")|("F_GETLK")|("F_SETLK")|("F_SETLKW")|("FD_CLOEXEC")|("F_RDLCK")|("F_WRLCK")|("F_UNLCK")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("FREAD")|("FWRITE")|("FAPPEND")|("FSYNC")|("FNONBLOCK")|("FNDELAY")|("FASYNC")|("FMARK")|("FDEFER")|("FSHLOCK")|("FEXLOCK")|("FNBIO")|("FNOSPC")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("S_IFMT")|("S_IFDIR")|("S_IFCHR")|("S_IFBLK")|("S_IFREG")|("S_IFIFO")|("S_IFLNK")|("S_IFSOCK")|("S_ISUID")|("S_ISGID")|("S_ISVTX")|("S_IRWXU")|("S_IRUSR")|("S_IWUSR")|("S_IXUSR")|("S_IRWXG")|("S_IRGRP")|("S_IWGRP")|("S_IXGRP")|("S_IRWXO")|("S_IROTH")|("S_IWOTH")|("S_IXOTH")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("STDIN_FILENO")|("STDOUT_FILENO")|("STDERR_FILENO")|("_POSIX_VERSION")|("_POSIX_RE_DUP_MAX")|("_POSIX_LINK_MAX")|("_POSIX_PATH_MAX")|("_POSIX_FOPEN_MAX")|("NGROUPS_MAX")|("SSIZE_MAX")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("CLOCKS_PER_SEC")|("CLOCK_REALTIME")|("CLOCK_MONOTONIC")|("CLOCK_PROCESS_CPUTIME_ID")|("CLOCK_THREAD_CPUTIME_ID")|("TIME_MAX")|("TIME_MIN")|("NULL")|("TM_YEAR_BASE")|("TIMEZONE_MAX")|("HOUR")|("MINUTE")|("SECOND")|("NANOSECONDS")|("MICROSECONDS")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("EOF")|("CHAR_MAX")|("CHAR_MIN")|("UCHAR_MAX")|("va_start")|("va_arg")|("va_end")|("va_copy")|("offsetof")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("FLT_MIN")|("FLT_MAX")|("FLT_EPSILON")|("DBL_MIN")|("DBL_MAX")|("DBL_EPSILON")|("LDBL_MIN")|("LDBL_MAX")|("LDBL_EPSILON")|("FLT_DIG")|("DBL_DIG")|("LDBL_DIG")|("FLT_MANT_DIG")|("DBL_MANT_DIG")|("LDBL_MANT_DIG")|("FLT_MIN_EXP")|("DBL_MIN_EXP")|("LDBL_MIN_EXP")|("FLT_MAX_EXP")|("DBL_MAX_EXP")|("LDBL_MAX_EXP")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

("INT8_MIN")|("INT8_MAX")|("UINT8_MAX")|("INT16_MIN")|("INT16_MAX")|("UINT16_MAX")|("INT32_MIN")|("INT32_MAX")|("UINT32_MAX")|("INT64_MIN")|("INT64_MAX")|("UINT64_MAX")|("INT_LEAST8_MIN")|("INT_LEAST8_MAX")|("UINT_LEAST8_MAX")|("INT_LEAST16_MIN")|("INT_LEAST16_MAX")|("UINT_LEAST16_MAX")|("INT_LEAST32_MIN")|("INT_LEAST32_MAX")|("UINT_LEAST32_MAX")|("INT_LEAST64_MIN")|("INT_LEAST64_MAX")|("UINT_LEAST64_MAX")|("INT_FAST8_MIN")|("INT_FAST8_MAX")|("UINT_FAST8_MAX")|("INT_FAST16_MIN")|("INT_FAST16_MAX")|("UINT_FAST16_MAX")|("INT_FAST32_MIN")|("INT_FAST32_MAX")|("UINT_FAST32_MAX")|("INT_FAST64_MIN")|("INT_FAST64_MAX")|("UINT_FAST64_MAX")|("INTPTR_MIN")|("INTPTR_MAX")|("UINTPTR_MAX")|("SIZE_MAX")|("PTRDIFF_MIN")|("PTRDIFF_MAX")  {total++;fprintf(yyout,"Constant %s\n",yytext);}

[a-zA-Z_][a-zA-Z0-9_]* {total++; fprintf(yyout,"Identifier %s\n",yytext);}



. { fprintf(yyout,"",yytext); }




[\t\n]+



%%

main()
{
extern FILE *yyin, *yyout; 
  
    
    yyin = fopen("input.txt", "r"); 
  
   
    yyout = fopen("Output.txt", "w"); 
  
    yylex();

	fprintf(yyout,"\n\n\n\n\n Total Tokens = %d",total);
	 

    return 0; 
}


