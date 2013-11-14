/*
 * getopt.c -- example of command-line parsing via getopt
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Sat Jul 13 15:15:02 2013 Harold André
 * Last update Mon Jul 15 18:07:57 2013 Harold André
 *
 * gcc -Wall -o getopt getopt.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <limits.h>

#define AUTHOR "Harold André"
#define VERSION "1.0"

/* For long options that have no equivalent short option, use a
   non-character as a pseudo short option, starting with CHAR_MAX + 1.  */
enum
{
  HELP_OPTION = CHAR_MAX + 1,
  VERSION_OPTION
};

/* global variable debug for the example */
int debug = 0;

/* print how display help on failure status, usage and help otherwise */
void usage(int status, char *program_name)
{
    if (status != EXIT_SUCCESS)
	fprintf (stderr, "Try \"%s --help\" for more information.\n",
		 program_name);
    else {
	printf("Usage: %s [-dmp] -f fname [-s sname] name [name]...\n",
	       program_name);
	fputs ("\
Short program description, ex: copy file fname to name.\n\
blah blah blah blah blah.\n\
\n\
", stdout);
	fputs ("\
Mandatory arguments to long options are mandatory for short options too.\n\
", stdout);
	fputs ("\
  -d, --debug                   enable debug mode\n\
  -f, --file NAME               file to work on\n\
  -m, --modification-time       indicate modification time to blah blah blah\n\
                                blah blah\n\
  -p, --preserve-permissions    preserve permissions for file\n\
  -s, --second-name NAME        copy with the name NAME\n\
", stdout);
	fputs ("\
      --help     display this help and exit\n\
      --version  output version information and exit\n\
", stdout);
    }

    /* always quit the program after print usage */
    exit(status);
}

int main(int argc, char *argv[])
{
    /* when an option take a parameter optarg point on the parameter */
    extern char *optarg;
    /* if there are other arguments on the command-line there are not options
       optind is an index on this remaining non-option ARGV-elements */
    extern int optind;
    int c, option_index=0;
    int mflag=0, pflag=0, fflag=0;
    char *sname = "default_sname", *fname = NULL;
    char *program_name = argv[0];

    /* informations on longs options:
       name,
       is argument required or not for the option,
       flag, (see man 3 getopt),
       value to return when long option is encountered, here return the short
       option's character, if exist, corresponding to the long option */
    static struct option long_options[] = {
	{"debug",                no_argument,       NULL, 'd'},
	{"file",                 required_argument, NULL, 'f'},
	{"modification-time",    no_argument,       NULL, 'm'},
	{"preserve-permissions", no_argument,       NULL, 'p'},
	{"second-name",          required_argument, NULL, 's'},
	{"help",                 no_argument,       NULL, HELP_OPTION},
	{"version",              no_argument,       NULL, VERSION_OPTION},
	{NULL,                   0,                 NULL,  0 }
    };

    /* when all options are parsed, getopt* return -1
       if an option letter is followed by a colon, this option requires
       an argument */
    while ((c = getopt_long(argc, argv, "df:mps:",
			      long_options, &option_index)) != -1) {
	switch (c) {
	case 'd':
	    debug = 1;
	    break;
	case 'm':
	    mflag = 1;
	    break;
	case 'p':
	    pflag = 1;
	    break;
	case 'f':
	    fflag = 1;
	    fname = optarg;
	    break;
	case 's':
	    sname = optarg;
	    break;
	case HELP_OPTION:
	    usage(EXIT_SUCCESS, program_name);
	    break;
	case VERSION_OPTION:
	    printf("%s %s\n", program_name, VERSION);
	    printf("Written by %s\n", AUTHOR);
	    exit(EXIT_SUCCESS);
	    break;
	case '?':
	default:
	    usage(EXIT_FAILURE, program_name);
	}
    }

    if (fflag == 0) {  /* -f was mandatory */
	fprintf(stderr, "%s: missing -f option\n", program_name);
	usage(EXIT_FAILURE, program_name);
    } else if ((optind+1) > argc) {
	/* need at least one argument (change +1 to +2 for two, etc. as needeed) */
	printf("optind = %d, argc = %d\n", optind, argc);
	fprintf(stderr, "%s: missing name\n", program_name);
	usage(EXIT_FAILURE, program_name);
    }

    /* see what we have */
    printf("debug = %d\n", debug);
    printf("pflag = %d\n", pflag);
    printf("mflag = %d\n", mflag);
    printf("fname = \"%s\"\n", fname);
    printf("sname = \"%s\"\n", sname);

    /* these are the arguments after the command-line options */
    if (optind < argc) {
	printf("non-option ARGV-elements: ");
	while (optind < argc)
	    printf("%s ", argv[optind++]);
	printf("\n");
    }

    if (optind < argc)  
	for (;optind < argc; optind++)
	    printf("argument: \"%s\"\n", argv[optind]);
    else {
	printf("no arguments left to process\n");
    }

    return 0;
}
