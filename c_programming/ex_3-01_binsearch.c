/*
 *
 * KnR
 * Exercice 3-1
 * (binary search = recherche dichotomique)
 * Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside).
 * Write a version with only one test inside the loop and measure the difference in run-time. 
 *
 */

#include <stdio.h>

#define TAB_SIZE 1000000

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);

int main()
{
  int tab[TAB_SIZE];
  int i;

  for (i = 0; i < TAB_SIZE; i++)
    tab[i] = i;

  //printf("Result: %d\n", binsearch(345xc6, tab, TAB_SIZE));
  printf("Result: %d\n", binsearch2(3456, tab, TAB_SIZE));

  return 0;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    //    printf("low: %d, mid: %d, high: %d\n", low, mid, high);
    mid = (low+high)/2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else  /* found match */
      return mid;
    
  }
  return -1;  /* no match */
}

int binsearch2(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low+high) /2;
    if (x < v[mid])
      high = mid - 1;
    else
      low = mid + 1;
    //    printf("low: %d, mid: %d, high: %d\n", low, mid, high);
  }

  if (x == mid)
    return mid;
  else
    return -1;  /* no match */
}
