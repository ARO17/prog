/*
 * debug.h -- Debug and error macros
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Wed Jun  4 16:36:17 2014 Harold André
 * Last update Wed Jun  4 17:43:08 2014 Harold André
 *
 * Find here: http://c.learncodethehardway.org/book/ex20.html
 *
 */

/*

  !!! Interesting, but beware "goto return" who exit the program !!!
  And I maybe the logic is not intuitive, for example:

  classic error handling:

      int rc = dosomething();

      if(rc != 0) {
        fprintf(stderr, "There was an error: %s\n", strerror());
        goto error;
      }
  
  The same with error's macro:

      int rc = dosomething();
      check(rc == 0, "There was an error.");

  In my mind, this expression means if rc == 0 then I get the error message...
  But this means if rc == 0 then I do not get the error message !

 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <errno.h>
#include <string.h>

/* 
   The alternative #define debug that translates any use of
   debug("format", arg1, arg2) into an fprintf call to stderr.
   Many C programmers don't know, but you can create macros that actually work
   like printf and take variable arguments. Some C compilers (actually cpp)
   don't support this, but the ones that matter do.
   The magic here is the use of ##__VA_ARGS__ which says "put whatever they had
   for extra arguments (...) here".
*/
#ifdef DEBUG
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define debug(M, ...)
#endif

/* The clean_errno macro that's used in the others to get a safe readable version
   of errno. */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

/* The log_err, log_warn, and log_info, macros for logging messages meant for
   the end user. Works like debug but can't be compiled out. */
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

/* 
   Check will make sure the condition A is true, and if not logs the error M
   (with variable arguments for log_err),
   then jumps to the function's error: for cleanup.
*/
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

/*
  sentinel is placed in any part of a function that shouldn't run, and if it
  does prints an error message then jumps to the error: label. You put this in
  if-statements and switch-statements to catch conditions that shouldn't happen,
  like the default:.
*/
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

/* A short-hand macro check_mem that makes sure a pointer is valid,
   and if it isn't reports it as an error with "Out of memory." */
#define check_mem(A) check((A), "Out of memory.")

/*
  An alternative macro check_debug that still checks and handles an error,
  but if the error is common then you don't want to bother reporting it.
  In this one it will use debug instead of log_err to report the message,
  so when you don't define DEBUG the check still happens,
  the error jump goes off, but the message isn't printed.
 */
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
