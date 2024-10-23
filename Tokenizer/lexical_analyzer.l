%{

int total =0 ;

%}

%option noyywrap




%%




#.* {total++; fprintf(yyout, "Pre-processor directive %s\n",yytext);}

[''|,|;(|)|{|}|.|_] {total++; fprintf(yyout,"Delimiter %s\n",yytext);}

[[]] {total++; fprintf(yyout,"Delimiter %s\n",yytext);}

"#"|"@"|"$"|"^"|"%"|"^"|"&" {total++; fprintf(yyout,"Special Characters %s\n",yytext);}

"["|"]" {total++; fprintf(yyout,"Delimiter %s\n",yytext);}


"="  {total++; fprintf(yyout,"Assignment Operator %s\n",yytext);}


"+"|"-"|"*"|"/"  {total++; fprintf(yyout,"Arithmatic Operator %s\n",yytext);}

"and"|"or"|"not"|"nand"|"xor"|"nor"|"xnor"  {total++; fprintf(yyout,"Logical Operators %s\n",yytext);}

"<="|">="|"++"|"!="|"=="|"<"|">"  {total++; fprintf(yyout,"Relational Operator %s\n",yytext);}

("int")|("if")|("else")|("while")|("do")|("break")|("continue")|("double")|("float")|("return")|("EOF") {total++; fprintf(yyout,"Keyword %s\n",yytext);}

("return")|("char")|("case")|("sizeof")|("long")|("short")|("typedef")|("switch")|("unsigned")|("void")|("static")|("struct")|("goto") {total++; fprintf(yyout,"Keyword %s\n",yytext);}

[a-zA-Z_][a-zA-Z0-9_]*\( {total++; fprintf(yyout,"Function %s\n",yytext);}

[a-zA-Z_][a-zA-Z0-9_]* {total++; fprintf(yyout,"Identifier %s\n",yytext);}

[0-9]*"."[0-9]+ {total++; fprintf(yyout,"Fraction %s\n", yytext);} 

[-][0-9]*"."[0-9]+ {total++; fprintf(yyout,"Negative Fraction %s\n", yytext);} 

[0-9]+ {total++; fprintf(yyout,"Integer %s\n",yytext);}

"-"[0-9]+ {total++; fprintf(yyout,"Negative Integer %s\n",yytext);}

["]([^"\\\n]|\\.|\\\n)*["] {total++; fprintf(yyout,"String %s\n",yytext);}

"//"." "    {total++; fprintf(yyout,"single line Commments: %s\n",yytext);}

\/\(.\n).\*\/    {total++; fprintf(yyout,"multi line Comments: %s\n",yytext);}


. {fprintf(yyout,"",yytext);}




[\t\n]+



%%

main()
{
extern FILE *yyin, *yyout; 
  
    
    yyin = fopen("input.txt", "r"); 
  
   
    yyout = fopen("Output.txt", "w"); 
  
    yylex();

	fprintf(yyout,"%d",total);
	 

    return 0; 
}
