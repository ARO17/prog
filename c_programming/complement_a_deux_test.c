/*
 * complement_a_deux_test.c
 *
 * Test du comportement des valeurs limites négatives et positives
 *
 * gcc -Wall -o complement_a_deux_test complement_a_deux_test.c
 *
 */

#include <stdio.h>


int main()
{
    char c_min = -128;
    char c_max = 127;

    int i_min = -2147483648;
    int i_max = 2147483647;

    printf("sizeof(char) = %zu\n", sizeof(char));
    printf("c_min = %d, c_max = %d\n", c_min, c_max);
    printf("-c_min = %d, -c_max = %d\n", -c_min, -c_max);
    printf("c_min-1 = %d, c_max+1 = %d\n", c_min-1, c_max+1);
    printf("sizeof(c_max+1) = %zu\n", sizeof(c_max+1));

    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("i_min = %d, i_max = %d\n", i_min, i_max);
    printf("-i_min = %d, -i_max = %d\n", -i_min, -i_max);
    printf("i_min-1 = %d, i_max+1 = %d\n", i_min-1, i_max+1);
    printf("sizeof(i_max+1) = %zu\n", sizeof(i_max+1));

    fprintf(stderr, "Erreur fichier %s, ligne %u, ", __FILE__, __LINE__);
    perror("la fonction fopen a rencontré un problème ");

    return 0;
}
