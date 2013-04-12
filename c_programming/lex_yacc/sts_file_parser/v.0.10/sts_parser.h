typedef struct
{
  int hour;
  int minute;
  int seconde;
  int fragrance;
  int group;
}
Command_line;

typedef struct
{
  Command_line *cmd_line;
  size_t used; /* items number */
  size_t size; /* total size allocated  */
}
Commands_array;

int initArray(Commands_array *cmd_array, size_t initialSize);

int insertElement(Commands_array *cmd_array, Command_line *element);

void freeArray(Commands_array *cmd_array);

void initCommandLine(Command_line *cmd_line);

Commands_array *loadSubtitleFile(char *subtitle_file_name);
