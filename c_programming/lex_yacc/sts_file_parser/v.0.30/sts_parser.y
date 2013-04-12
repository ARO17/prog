%{
  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sts_parser.h"
  
#define INITIALSIZE 10
//# define DEBUG 1
  
/* Une ligne de commande du fichier sous titre  */
Command_line cmd_line;
/* L'ensemble des commandes du fichier sous titre  */
Commands_array cmd_array;
/* Nombre de ligne valide parsée  */
static int lines_number;

extern int yylineno;
extern char *yytext;

extern int yylex();
extern int yyerror(const char *);
extern int yyrestart(FILE *);

  
%}

%error-verbose

%union {
  int integer;
  char *string;
}

%token  <integer> NUMBER
%token  <string> CAPSID
%token  <string> GROUPID
%token  COLON COMMA ASSIGN CAPSULE GROUP TIMESEPARATOR
%token  EOL

%%

config_file: 	lines
		;

lines:		one_line lines
		| one_line
		;

one_line:	Command EOL
                {{ 
		    lines_number+=1;
		    /* TODO: Fill the commands array structure */
		    insertElement(&cmd_array, &cmd_line);
		    initCommandLine(&cmd_line);
#ifdef DEBUG
		    printf("DEBUG: %d valid command line\n", lines_number);
#endif
                }}
                ;
                | Time EOL
		{{
		    fprintf(stderr, "%d: BAD FORMAT: No command given after time.\n", yylineno);
		}}
                ;
                | EOL
		| error        
		{{
#ifdef DEBUG
		    printf("DEBUG: Values RAZ after error.\n");
#endif
		    initCommandLine(&cmd_line);
		}}
		;

Command: Time ASSIGN CAPSID
    {{
	if ((cmd_line.fragrance = atoi($3+1)) > 4) {
	  yyerror("Fragrance value must be >=0 and <=4\n");
	  YYERROR;
	} else {
#ifdef DEBUG
	printf("DEBUG: fragrance format F*: %s\n", cmd_line.fragrance);
#endif
	}
    }}
    ;
    | Time ASSIGN CAPSID COMMA GROUPID
    {{
	if ((cmd_line.fragrance = atoi($3+1)) > 4) {
	  yyerror("Fragrance value must be >=0 and <=4\n");
	  YYERROR;
	} else {
	cmd_line.group = atoi($5+1);
#ifdef DEBUG
	printf("DEBUG: fragrance format F*: %d, group format G*: %d\n", cmd_line.fragrance, cmd_line.group);
#endif
	}
    }}
    ;
    | Time ASSIGN GROUPID COMMA CAPSID
    {{
	if ((cmd_line.fragrance = atoi($5+1)) > 4) {
	  yyerror("Fragrance value must be >=0 and <=4\n");
	  YYERROR;
	} else {
	cmd_line.group = atoi($3+1);
#ifdef DEBUG
	printf("DEBUG: group format F*: %d, fragrance format G*: %d\n", cmd_line.group, cmd_line.fragrance);
#endif
	}
    }}
    ;
    | Time ASSIGN CAPSULE NUMBER
    {{
	if ((cmd_line.fragrance = $4) > 4) {
	  yyerror("Fragrance value must be >=0 and <=4\n");
	  YYERROR;
	} else {
#ifdef DEBUG
	printf("DEBUG: fragrance format F*: %s\n", cmd_line.fragrance);
#endif
	}
    }}
    ;
    | Time ASSIGN CAPSULE NUMBER COMMA GROUP NUMBER
    {{
	if ((cmd_line.fragrance = $4) > 4) {
	  yyerror("Fragrance value must be >=0 and <=4\n");
	  YYERROR;
	} else {
	cmd_line.group = $7;
#ifdef DEBUG
	printf("DEBUG: fragrance format F*: %d, group format G*: %d\n", cmd_line.fragrance, cmd_line.group);
#endif
	}
    }}
    ;
    | Time ASSIGN GROUP NUMBER COMMA CAPSULE NUMBER
    {{
	if ((cmd_line.fragrance = $7) > 4) {
	  yyerror("Fragrance value must be >=0 and <=4\n");
	  YYERROR;
	} else {
	cmd_line.group = $4;
#ifdef DEBUG
	printf("DEBUG: group format F*: %d, fragrance format G*: %d\n", cmd_line.group, cmd_line.fragrance);
#endif
	}
    }}
    ;

Time: StartTime EndTime
    ;

StartTime:
    NUMBER
    {{
	cmd_line.start_time.seconde = $1;
#ifdef DEBUG
	printf("DEBUG: seconde: %d\n", cmd_line.start_time.seconde); 
#endif
    }}
    ;
    | NUMBER COLON NUMBER 
    {{ 
	cmd_line.start_time.minute = $1;
	cmd_line.start_time.seconde = $3;
#ifdef DEBUG
	printf("DEBUG: minute: %d, seconde: %d\n", cmd_line.start_time.minute, cmd_line.start_time.seconde); 
#endif
    }}
    ;
    | NUMBER COLON NUMBER COLON NUMBER
    {{ 
	cmd_line.start_time.hour = $1;
	cmd_line.start_time.minute = $3;
	cmd_line.start_time.seconde = $5;
#ifdef DEBUG
	printf("DEBUG: hour: %d, minute: %d, seconde: %d\n", cmd_line.start_time.hour, cmd_line.start_time.minute, cmd_line.start_time.seconde); 
#endif
    }}
    ;

EndTime:
    TIMESEPARATOR NUMBER
    {{
	cmd_line.end_time.seconde = $2;
#ifdef DEBUG
	printf("DEBUG: seconde: %d\n", cmd_line.end_time.seconde); 
#endif
    }}
    ;
    | TIMESEPARATOR NUMBER COLON NUMBER 
    {{ 
	cmd_line.end_time.minute = $2;
	cmd_line.end_time.seconde = $4;
#ifdef DEBUG
	printf("DEBUG: minute: %d, seconde: %d\n", cmd_line.end_time.minute, cmd_line.end_time.seconde); 
#endif
    }}
    ;
    | TIMESEPARATOR NUMBER COLON NUMBER COLON NUMBER
    {{ 
	cmd_line.end_time.hour = $2;
	cmd_line.end_time.minute = $4;
	cmd_line.end_time.seconde = $6;
#ifdef DEBUG
	printf("DEBUG: hour: %d, minute: %d, seconde: %d\n", cmd_line.end_time.hour, cmd_line.end_time.minute, cmd_line.end_time.seconde); 
#endif
    }}
    ;

%%


int yyerror (const char *s)
{
  fprintf(stderr, "%d: %s at '%s'\n", yylineno, s, yytext);

  return 0;
}


int initArray(Commands_array *cmd_array, size_t initialSize) {
  cmd_array->cmd_line = malloc(initialSize * sizeof(Command_line));
  if (cmd_array->cmd_line == NULL) {
    fprintf(stderr, "Memory allocation error.");
    return -1;
  }

  cmd_array->used = 0;
  cmd_array->size = initialSize;

  return initialSize;
}

int insertElement(Commands_array *cmd_array, Command_line *element) {
  if (cmd_array->used == cmd_array->size) {
    cmd_array->size *= 2;
    cmd_array->cmd_line = realloc(cmd_array->cmd_line, cmd_array->size * sizeof(Command_line));
    if (cmd_array->cmd_line == NULL) {
      fprintf(stderr, "Memory allocation error.");
      return -1;
    }
  }
  cmd_array->cmd_line[cmd_array->used++] = *element;

  return cmd_array->used;
}

void freeArray(Commands_array *cmd_array) {
  free(cmd_array->cmd_line);
  cmd_array->cmd_line = NULL;
  cmd_array->used = cmd_array->size = 0;
}

void initCommandLine(Command_line *cmd_line) {
  cmd_line->start_time.hour = 0;
  cmd_line->start_time.minute = 0;
  cmd_line->start_time.seconde = 0;

  cmd_line->end_time.hour = 0;
  cmd_line->end_time.minute = 0;
  cmd_line->end_time.seconde = 0;

  cmd_line->fragrance = 0;
  cmd_line->group = 0;
}

Commands_array *loadSubtitleFile (char *subtitle_file_name)
{
  FILE *rcfile;

  lines_number = 0;
  initCommandLine(&cmd_line);

  rcfile = fopen (subtitle_file_name, "r");
  if (rcfile)
    {
      initArray(&cmd_array, INITIALSIZE);

      /* Reading subtitles file */
      printf("Start reading subtitle file.\n");
      yyrestart (rcfile);
      yyparse ();
      fclose (rcfile);
      printf("End reading subtitle file.\n");
      printf("Number of valid lines: %d\n", lines_number);

    }
  else
    {
      fprintf (stderr, "Error, can't open subtitles file.\n");
    }

  return &cmd_array;
}
