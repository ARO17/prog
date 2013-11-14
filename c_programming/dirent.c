/*
 * dirent.c -- Count lines and files number
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Thu Jun 27 17:22:34 2013 Harold André
 * Last update Wed Jul 10 19:57:01 2013 Harold André
 *
 * gcc -Wall -o dirent dirent.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#ifndef WIN32
#include <sys/types.h>
#endif

/*
  whithout arg, scan current dir and return number of file and total line number
  with dir path, return number of file and total line number
  with one or multiple file(s) name, return the number of file and
  the total line number of files passed as args.
  
 */
int main(int argc, char *argv[])
{
    DIR *dirp = NULL;
    struct dirent *entry = NULL;
    char *dirpath = "/home/aro17/";
    int entry_number = 0;
    FILE *fp = NULL;
    char *filepath = NULL;
    int c;
    int line_number, global_line_number;

    /* open a directory */
    dirp = opendir(dirpath);
    if (dirp == NULL) {
	perror("opendir");
	exit(-1);
    }

    /* read the all entries of the directory dir */
    while ((entry = readdir(dirp)) != NULL) {
	/* regular files */
	if (entry->d_type == DT_REG) {
	    entry_number+=1;
	    printf("REG - %s's entry : %s\n", dirpath, entry->d_name);
#ifdef NOTDEF
	    /* add / if there is not at the end of the directory path */
	    if (strrchr(dirpath, '/') != dirpath[strlen(dirpath)-1])
		strcat(dirpath, "/");
	    printf("%s\n", dirpath);
#endif
	    /* create filepath */
	    filepath = malloc(sizeof(char)*(strlen(dirpath)+strlen(entry->d_name)+1));
	    if (filepath == NULL) {
		perror("malloc");
		exit(-3);
	    }
	    strcpy(filepath, dirpath);
	    strcat(filepath, entry->d_name);

	    line_number = 0;
	    /* open file in read mode */
	    fp = fopen(filepath, "r");
	    if (fp != NULL) {
		/* count line number */
		while ((c = fgetc(fp)) != EOF)
		    if (c == '\n')
			line_number++;
		printf("Number of line: %d\n", line_number);
		fclose(fp);
	    } else {
		printf("Unable to open file: %s\n", filepath);
	    }
	    free(filepath);
	    /* add line number of the last file */
	    global_line_number += line_number;
	
	} else if (entry->d_type == DT_DIR) {
	    printf("DIR - This is a directory: %s\n", entry->d_name);
	}else {
	    printf("OTH - This is an other type of file: %s\n", entry->d_name);
	}
    }
    printf("number of file in %s directory: %d\n", dirpath, entry_number);
    printf("number of line: %d\n", global_line_number);

    /* close the directory */
    if (closedir(dirp) == -1) {
	perror("closedir");
	exit(-2);
    }

#ifdef _DIRENT_HAVE_D_TYPE
    printf("dirent have d_type\n");
#endif

    return 0;
}
