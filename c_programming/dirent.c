/*
 * count_lines.c -- Count lines of all text file in current directory
 * 
 * Written by Harold André
 * E-mail     <harold.andre@scentys.com>
 * 
 * Started on  Thu Jun 27 17:22:34 2013 Harold André
 * Last update Fri Jun 28 16:34:44 2013 Harold André
 * 
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
    puts("test");
    /* for each file of current directory
       |test if regular file
       ||open file in read mode
       ||while != EOF
       |||get each line and count++
       ||close file
       return number of line and number of file
    */
    return 0;
}
