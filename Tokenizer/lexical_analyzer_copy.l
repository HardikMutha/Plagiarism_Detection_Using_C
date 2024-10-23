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

[''|,|;(|)|{|}|.|_] {total++; fprintf(yyout,"Delimiter %s\n",yytext);}

[[]] {total++; fprintf(yyout,"Delimiter %s\n",yytext);}

"#"|"@"|"$"|"^"|"%"|"^"|"&" {total++; fprintf(yyout,"SpecialCharacters %s\n",yytext);}

"["|"]" {total++; fprintf(yyout,"Delimiter %s\n",yytext);}


"="  {total++; fprintf(yyout,"Assign %s\n",yytext);}


"+"|"-"|"*"|"/"  {total++; fprintf(yyout,"Arithmatic %s\n",yytext);}

"and"|"or"|"not"|"nand"|"xor"|"nor"|"xnor"  {total++; fprintf(yyout,"Logical %s\n",yytext);}

"<="|">="|"++"|"!="|"=="|"<"|">"  {total++; fprintf(yyout,"Relational %s\n",yytext);}

("int")|("if")|("else")|("while")|("do")|("break")|("continue")|("double")|("float")|("return")|("EOF") {total++; fprintf(yyout,"Keyword %s\n",yytext);}

("return")|("char")|("case")|("sizeof")|("long")|("short")|("typedef")|("switch")|("unsigned")|("void")|("static")|("struct")|("goto") {total++; fprintf(yyout,"Keyword %s\n",yytext);}

[a-zA-Z_][a-zA-Z0-9_]*\( {total++; fprintf(yyout,"Function %s\n",yytext);}

[a-zA-Z_][a-zA-Z0-9_]* {total++; fprintf(yyout,"Identifier %s\n",yytext);}

[0-9]*"."[0-9]+ {total++; fprintf(yyout,"Fraction %s\n", yytext);} 

[-][0-9]*"."[0-9]+ {total++; fprintf(yyout,"NegativeFraction %s\n", yytext);} 

[0-9]+ {total++; fprintf(yyout,"Integer %s\n",yytext);}

"-"[0-9]+ {total++; fprintf(yyout,"NegativeInteger %s\n",yytext);}

["]([^"\\\n]|\\.|\\\n)*["] {total++; fprintf(yyout,"String %s\n",yytext);}

"//".*" "*    {total++; fprintf(yyout,"Commment %s\n",yytext);}

\/\*(.*\n)*.*\*\/    {total++; fprintf(yyout,"Comment %s\n",yytext);}


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
