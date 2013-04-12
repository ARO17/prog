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

{number}     { yylval.integer = atoi(yytext); return(NUMBER); }
[Ff]{number} { yylval.string = yytext; return(FRAG); }
[Gg]{number} { yylval.string = yytext; return(GROUP); }
":"          { return(COLON); }
"-"          { return(DASH); }
","          { return(COMMA); }
"="          { return(ASSIGN); }
"->"         { return(ASSIGN); }
"\n"         { return(EOL); }
"\r"         { return(EOL); }
"\r\n"       { return(EOL); }
<<EOF>>      { return 0 ; }
.            ;


%%
