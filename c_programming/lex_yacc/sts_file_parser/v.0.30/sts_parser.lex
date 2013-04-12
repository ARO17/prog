%option nounput
%option noinput

%{

#include "sts_parser.y.h"

%}


blank   [ \t]+
digit   [0-9]
number  {digit}+


%%

{blank}      ; /* Do nothing */
[A-Z]        ;
[a-z]        ;
#.*$         ;

{number}                      { yylval.integer = atoi(yytext); return(NUMBER); }
[cC]{number}                  { yylval.string = yytext; return(CAPSID); }
[gG]{number}                  { yylval.string = yytext; return(GROUPID); }
[cC][aA][pP][sS][uU][lL][eE]  { return(CAPSULE); } 
[gG][rR][oO][uU][pP]          { return(GROUP); }
":"                           { return(COLON); }
","                           { return(COMMA); }
"="                           { return(ASSIGN); }
"->"                          { return(TIMESEPARATOR); }
"\n"                          { return(EOL); }
"\r"                          { return(EOL); }
"\r\n"                        { return(EOL); }
<<EOF>>                       { return 0 ; }
.                             ;


%%
