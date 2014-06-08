/*
 * doubly_linked_lists.c -- Doubly linked lists training
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Thu May  8 13:50:58 2014 Harold André
 * Last update Thu May 29 12:48:25 2014 Harold André
 *
 * gcc -Wall doubly_linked_lists.c -o doubly_linked_lists
 * 
 */

#include <stdio.h>
#include <stdlib.h>


#define dlist_remove_first(list) dlist_remove_position(list, 1)
#define dlist_remove_last(list) dlist_remove_position(list, dlist_length(list))

struct node
{
    int data;
    struct node *p_next;
    struct node *p_prev;
};

typedef struct dlist
{
    size_t length;
    struct node *p_tail;
    struct node *p_head;
} Dlist;

Dlist *dlist_new(void)
{
    Dlist *p_new = malloc(sizeof *p_new);
    if (p_new != NULL)
    {
        p_new->length = 0;
        p_new->p_head = NULL;
        p_new->p_tail = NULL;
    }
    return p_new;
}

Dlist *dlist_add_to_end(Dlist *p_list, int data)
{
    if (p_list != NULL) /* On vérifie si notre liste a été allouée */
    {
        struct node *p_new = malloc(sizeof *p_new); /* Création d'un nouveau node */
        if (p_new != NULL) /* On vérifie si le malloc n'a pas échoué */
        {
            p_new->data = data; /* On 'enregistre' notre donnée */
            p_new->p_next = NULL; /* On fait pointer p_next vers NULL */
            if (p_list->p_tail == NULL) /* Cas où notre liste est vide (pointeur vers fin de liste à  NULL) */
            {
                p_new->p_prev = NULL; /* On fait pointer p_prev vers NULL */
                p_list->p_head = p_new; /* On fait pointer la tête de liste vers le nouvel élément */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers le nouvel élément */
            }
            else /* Cas où des éléments sont déjà présents dans notre liste */
            {
                p_list->p_tail->p_next = p_new; /* On relie le dernier élément de la liste vers notre nouvel élément (début du chaînage) */
                p_new->p_prev = p_list->p_tail; /* On fait pointer p_prev vers le dernier élément de la liste */
                p_list->p_tail = p_new; /* On fait pointer la fin de liste vers notre nouvel élément (fin du chaînage: 3 étapes) */
            }
            p_list->length++; /* Incrémentation de la taille de la liste */
        }
    }
    return p_list; /* on retourne notre nouvelle liste */
}

Dlist *dlist_add_to_begin(Dlist *p_list, int data)
{
    if (p_list != NULL)
    {
        struct node *p_new = malloc(sizeof *p_new);
        if (p_new != NULL)
        {
            p_new->data = data;
            p_new->p_prev = NULL;
            if (p_list->p_tail == NULL)
            {
                p_new->p_next = NULL;
                p_list->p_head = p_new;
                p_list->p_tail = p_new;
            }
            else
            {
                p_list->p_head->p_prev = p_new;
                p_new->p_next = p_list->p_head;
                p_list->p_head = p_new;
            }
            p_list->length++;
       }
    }
    return p_list;
}

Dlist *dlist_insert(Dlist *p_list, int data, int position)
{
    if (p_list != NULL)
    {
        struct node *p_temp = p_list->p_head;
        int i = 1;
        while (p_temp != NULL && i <= position)
        {
            if (position == i)
            {
                if (p_temp->p_next == NULL)
                {
                    p_list = dlist_add_to_end(p_list, data);
                }
                else if (p_temp->p_prev == NULL)
                {
                    p_list = dlist_add_to_begin(p_list, data);
                }
                else
                {
                    struct node *p_new = malloc(sizeof *p_new);;
                    if (p_new != NULL)
                    {
                        p_new->data = data;
                        //p_temp->p_next->p_prev = p_new;
			p_temp->p_prev->p_next = p_new;
			p_new->p_prev = p_temp->p_prev;
			p_temp->p_prev = p_new;
                        p_new->p_next = p_temp;
                        p_list->length++;
                    }
                }
            }
            else
            {
                p_temp = p_temp->p_next;
            }
            i++;
        }
    }
    return p_list;
}

/* Supprimer un élément selon sa valeur */
Dlist *dlist_remove_value(Dlist *p_list, int data)
{
    if (p_list != NULL)
    {
        struct node *p_temp = p_list->p_head;
        int found = 0;
        while (p_temp != NULL && !found)
        {
            if (p_temp->data == data)
            {
                if (p_temp->p_next == NULL)
                {
                    p_list->p_tail = p_temp->p_prev;
                    p_list->p_tail->p_next = NULL;
                }
                else if (p_temp->p_prev == NULL)
                {
                    p_list->p_head = p_temp->p_next;
                    p_list->p_head->p_prev = NULL;
                }
                else
                {
                    p_temp->p_next->p_prev = p_temp->p_prev;
                    p_temp->p_prev->p_next = p_temp->p_next;
                }
                free(p_temp);
                p_list->length--;
                found = 1;
            }
            else
            {
                p_temp = p_temp->p_next;
            }
        }
    }
    return p_list;
}

/* Supprimer un élément selon sa position */
Dlist *dlist_remove_position(Dlist *p_list, int position)
{
    if (p_list != NULL)
    {
        struct node *p_temp = p_list->p_head;
        int i = 1;
        while (p_temp != NULL && i <= position)
        {
            if (i == position)
            {
                if (p_temp->p_next == NULL)
                {
                    p_list->p_tail = p_temp->p_prev;
                    p_list->p_tail->p_next = NULL;
                }
                else if (p_temp->p_prev == NULL)
                {
                    p_list->p_head = p_temp->p_next;
                    p_list->p_head->p_prev = NULL;
                }
                else
                {
                    p_temp->p_next->p_prev = p_temp->p_prev;
                    p_temp->p_prev->p_next = p_temp->p_next;
                }
                free(p_temp);
                p_list->length--;
            }
            else
            {
                p_temp = p_temp->p_next;
            }
	    i++;
        }
    }
    return p_list;
}

/* Renvoi la taille de la liste ou 0 si elle n'existe pas */
size_t dlist_length(Dlist *p_list)
{
    size_t ret = 0;
    if (p_list != NULL)
    {
        ret = p_list->length;
    }
    return ret;
}

/* Recherche un élément selon sa valeur
   et renvoie une liste contentant cet unique élément  */
Dlist *dlist_find(Dlist *p_list, int data)
{
    Dlist *ret = NULL;
    if (p_list != NULL)
    {
        struct node *p_temp = p_list->p_head;
        int found = 0;
        while (p_temp != NULL && !found)
        {
            if (p_temp->data == data)
            {
                ret = dlist_new(); /* On alloue une nouvelle liste  */
                ret = dlist_add_to_end(ret, data); /* Ajoute data à la liste */
                found = 1;
            }
            else
            {
                p_temp = p_temp->p_next;
            }
        }
    }
    return ret;
}

/* Renvoie une liste contenant tous les éléments de valeur "data" */
Dlist *dlist_find_all(Dlist *p_list, int data)
{
    Dlist *ret = NULL;
    if (p_list != NULL)
    {
        struct node *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            if (p_temp->data == data)
            {
                if (ret == NULL)
                {
                    ret = dlist_new();
                }
                ret = dlist_add_to_end(ret, data);
            }
            p_temp = p_temp->p_next;
        }
    }
    return ret;
}

/* Retourne la liste inverse de la liste passée en paramètre */
Dlist *dlist_reverse(Dlist *p_list)
{
    Dlist *ret = NULL;
    if (p_list != NULL)
    {
        struct node *p_temp = p_list->p_tail;
        ret = dlist_new();
        while (p_temp != NULL)
        {
            ret = dlist_add_to_end(ret, p_temp->data);
            p_temp = p_temp->p_prev;
        }
    }
    return ret;
}

void dlist_print(Dlist *p_list)
{
    if (p_list != NULL) {
	struct node *p_temp = p_list->p_head;
	while (p_temp != NULL) {
	    printf("\t%d", p_temp->data);
	    p_temp = p_temp->p_next;
	}
	printf("\n");
    }
}

void dlist_print_reverse(Dlist *p_list)
{
    if (p_list != NULL) {
	struct node *p_temp = p_list->p_tail;
	while (p_temp != NULL) {
	    printf("\t%d", p_temp->data);
	    p_temp = p_temp->p_prev;
	}
	printf("\n");
    }
}

void dlist_delete(Dlist **p_list)
{
    if (*p_list != NULL)
    {
        struct node *p_temp = (*p_list)->p_head;
        while (p_temp != NULL)
        {
            struct node *p_del = p_temp;
            p_temp = p_temp->p_next;
            free(p_del);
        }
        free(*p_list), *p_list = NULL;
    }
}

/* Erreur : Pour pouvoir modifier le pointeur passer en argument
 et le faire pointer sur NULL, il faut passer un pointeur sur le pointeur */
void dlist_delete_bug(Dlist *p_list)
{
    if (p_list != NULL)
    {
        struct node *p_temp = p_list->p_head;
        while (p_temp != NULL)
        {
            struct node *p_del = p_temp;
            p_temp = p_temp->p_next;
            free(p_del);
        }
        free(p_list), p_list = NULL;
    }
}

int main(int argc, char **argv)
{
    int i;
    Dlist *p_my_liste = dlist_new();

    for (i = 1; i < 5; i++)
	dlist_add_to_end(p_my_liste, i);

    printf("Ma nouvelle liste.\n");
    dlist_print(p_my_liste);
    dlist_print_reverse(p_my_liste);

    dlist_insert(p_my_liste, 88, 3);

    printf("On insert l'élément avec la valeur 88 en position 3.\n");
    dlist_print(p_my_liste);
    dlist_print_reverse(p_my_liste);

    dlist_remove_value(p_my_liste, 2);

    printf("On supprime l'élément avec la valeur 2.\n");
    dlist_print(p_my_liste);
    dlist_print_reverse(p_my_liste);

    dlist_remove_position(p_my_liste, 3);

    printf("On supprime l'élément se trouvant en 3ème position.\n");
    dlist_print(p_my_liste);
    dlist_print_reverse(p_my_liste);

    printf("La mémoire n'est pas encore libérée.\n");
    getchar();

    dlist_delete_bug(p_my_liste);

    if (p_my_liste == NULL)
	printf("p_my_liste vaut NULL\n");
    else
	printf("p_my_liste n'est pas NULL\n");

    printf("La mémoire a été libérée de mauvaise manière.\n");

    dlist_print(p_my_liste);
    dlist_print_reverse(p_my_liste);

    getchar();

    dlist_delete(&p_my_liste);

    printf("La mémoire a été correctement libérée.\n");

    dlist_print(p_my_liste);
    dlist_print_reverse(p_my_liste);

    getchar();

    return 0;
}
