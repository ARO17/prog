#include <stdio.h>
#include <stdlib.h>
#include "sts_parser.h"

int
main(int argc, char *argv[])
{
  Commands_array *cmd_array = NULL;
  int i;

  if (argc != 2) {
    fprintf(stderr, "usage: %s filename\n", argv[0]);
    exit(1);
  }
  else
    cmd_array = loadSubtitleFile(argv[1]);

  if (cmd_array)
    {
      for (i = 0; i < cmd_array->used; i++) {
	printf ("Command %d: Play fragrance %d of group %d at %d hour, %d minute(s) and %d seconde(s)\n",
		i,
		cmd_array->cmd_line[i].fragrance,
		cmd_array->cmd_line[i].group,
		cmd_array->cmd_line[i].hour,
		cmd_array->cmd_line[i].minute,
		cmd_array->cmd_line[i].seconde);
      }
    }

  exit(0);
}
