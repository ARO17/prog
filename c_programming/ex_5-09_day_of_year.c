/*
 * ex_5-09_day_of_year.c -- Ex KnR book
 * 
 * Rewrite the routines day_of_year and month_day with pointers instead of
 * indexing.
 *
 *
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sat Nov 16 14:55:54 2013 Harold André
 * Last update Wed Nov 20 20:19:20 2013 Harold André
 *
 * gcc -Wall -o ex_5-09_day_of_year ex_5-09_day_of_year.c
 *
 * 
 */

#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap, day1 = day;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i < month; i++) {
	/*    day += daytab[leap][i]; */
	//	printf("daytab: %d\n", *((*daytab)+i)+leap);
	day1 += *((*daytab + i) + leap);
	day +=  *(*(daytab + leap) + i);
	printf("day1: %d\n day: %d\n daytab: %p\n *daytab: %p\n **daytab: %d\n i: %d, leap: %d\n", day1, day, daytab, *daytab, **daytab, i, leap);
    }
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    p = daytab[leap];
    while (yearday > *++p)
	yearday -= *p;
    *pmonth = p - *(daytab + leap);
    *pday = yearday;
}

int main()
{
    int alloc[2];
    /*    
	  int *month = alloc;
	  int *day = alloc+1;
    */

    printf("Day of year from 29/11/1979 is: %d\n", day_of_year(1979, 11, 29));
    printf("Day of year from 19/11/2013 is: %d\n", day_of_year(2013, 11, 19));

    printf("alloc[0]: %d, alloc[1]: %d\n", alloc[0], alloc[1]);
    month_day(1979, 333, alloc, alloc+1);
    printf("333th day of 1979 is: month %d, day %d\n", *alloc, *(alloc+1));
    printf("alloc[0]: %d, alloc[1]: %d\n", alloc[0], alloc[1]);

    return 0;
}
