/*
 * linked_lists.c -- Linked lists training
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sat Feb 22 12:25:50 2014 Harold André
 * Last update Thu Mar  6 20:01:26 2014 Harold André
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct element element;
struct element
{
    int val;
    struct element *nxt;
};

typedef element* llist;

llist ajouterEnTete(llist list, int valeur)
{
    /* On crée un nouvel élement */
    element *nouvelElement = malloc(sizeof(element));

    /* On assigne la valeur au nouvel élément */
    nouvelElement->val = valeur;

    /* On assigne l'adresse de l'élément suivant au nouvel élément */
    nouvelElement->nxt = list;

    /* On retourne la nouvelle liste, i.e. le pointeur sur le premier élément */
    return nouvelElement;
}

llist ajouterEnFin(llist list, int valeur)
{
    /* On crée un nouvel élement */
    element *nouvelElement = malloc(sizeof(element));

    /* On assigne la valeur au nouvel élément */
    nouvelElement->val = valeur;

    /* On ajoute en fin, donc aucun élément ne va suivre */
    nouvelElement->nxt = NULL;

    if (liste == NULL){
	/* Si la liste est vide, il suffit de renvoyer l'élément créé */
	return nouvelElement;
    } else {
	/* Sinon, on parcourt la liste à l'aide d'un pointeur temporaire et
	   on indique que le dernier élément de la liste est relié
	   au nouvel élément */
	element *temp = list;
	while (temp->nxt != NULL) {
	    temp = temp->nxt;
	}
	temp->nxt = nouvelElement;
	return liste;
    }
}

void afficherLste(llist liste)
{
    element *tmp = liste;
    /* Tant que l'on est pas au bout de la liste */
    while (tmp != NULL) {
	printf("%d", tmp->val);
	tmp = tmp->nxt;
    }
}

int estVide(llist liste)
{
    return (liste == NULL)? 1 : 0;
}

llist supprimerElementEnTete(llist liste)
{
    if (liste != NULL) {
	/* Si la liste est non vide, on se prépare  à renvoyer l'adresse
	   de l'élément en 2ème position */
	element *aRenvoyer = liste->nxt;
	/* On libère le premier élément */
	free(liste);
	/* On retourne le nouveau début de la liste */
	return aRenvoyer;
    }
    else {
	return NULL;
    }
}

llist supprimerElementEnFin(llist liste)
{
    /* Si la liste est vide, on retourne NULL */
    if(liste == NULL)
        return NULL;
 
    /* Si la liste contient un seul élément */
    if(liste->nxt == NULL)
	{
	    /* On le libère et on retourne NULL (la liste est maintenant vide) */
	    free(liste);
	    return NULL;
	}
 
    /* Si la liste contient au moins deux éléments */
    element* tmp = liste;
    element* ptmp = liste;
    /* Tant qu'on n'est pas au dernier élément */
    while(tmp->nxt != NULL)
	{
	    /* ptmp stock l'adresse de tmp */
	    ptmp = tmp;
	    /* On déplace tmp (mais ptmp garde l'ancienne valeur de tmp */
	    tmp = tmp->nxt;
	}
    /* A la sortie de la boucle, tmp pointe sur le dernier élément, et ptmp sur
       l'avant-dernier. On indique que l'avant-dernier devient la fin de la liste
       et on supprime le dernier élément */
    ptmp->nxt = NULL;
    free(tmp);
    return liste;
}

llist rechercherElement(llist liste, int valeur)
{
    element *tmp=liste;
    /* Tant que l'on n'est pas au bout de la liste */
    while(tmp != NULL)
	{
	    if(tmp->val == valeur)
		{
		    /* Si l'élément a la valeur recherchée, on renvoie son adresse */
		    return tmp;
		}
	    tmp = tmp->nxt;
	}
    return NULL;
}

int nombreOccurences(llist liste, int valeur)
{
    int i = 0;
 
    /* Si la liste est vide, on renvoie 0 */
    if(liste == NULL)
        return 0;
 
    /* Sinon, tant qu'il y a encore un élément ayant la val = valeur */
    while((liste = rechercherElement(liste, valeur)) != NULL)
	{
	    /* On incrémente */
	    liste = liste->nxt;
	    i++;
	}
    /* Et on retourne le nombre d'occurrences */
    return i;
}

llist element_i(llist liste, int indice)
{
    int i;
    /* On se déplace de i cases, tant que c'est possible */
    for(i=0; i<indice && liste != NULL; i++)
	{
	    liste = liste->nxt;
	}
 
    /* Si l'élément est NULL, c'est que la liste contient moins de i éléments */
    if(liste == NULL)
	{
	    return NULL;
	}
    else
	{
	    /* Sinon on renvoie l'adresse de l'élément i */
	    return liste;
	}
}

#define ERREUR -1
int valeur(llist liste)
{
    return ((liste == NULL)?ERREUR:(liste->val));
}

/* version récursive */
int nombreElements(llist liste)
{
    /* Si la liste est vide, il y a 0 élément */
    if(liste == NULL)
        return 0;
    
    /* Sinon, il y a un élément (celui que l'on est en train de traiter)
       plus le nombre d'éléments contenus dans le reste de la liste */
    return nombreElements(liste->nxt)+1;
}

/* version itérative */
int nombreElementsIter(llist liste)
{
    int nb = 0;
    element* tmp = liste;
 
    /* On parcours la liste */
    while(tmp != NULL)
	{
	    /* On incrémente */
	    nb++;
	    tmp = tmp->nxt;
	}
    /* On retourne le nombre d'éléments parcourus */
    return nb;
}

/* effacer toute la liste de façon itérative */
llist effacerListe(llist liste)
{
    element* tmp = liste;
    element* tmpnxt;
 
    /* Tant que l'on n'est pas au bout de la liste */
    while(tmp != NULL)
	{
	    /* On stocke l'élément suivant pour pouvoir ensuite avancer */
	    tmpnxt = tmp->nxt;
	    /* On efface l'élément courant */
	    free(tmp);
	    /* On avance d'une case */
	    tmp = tmpnxt;
	}
    /* La liste est vide : on retourne NULL */
    return NULL;
}

/* effacer toute la liste de façon récursive */
llist effacerListeRecur(llist liste)
{
    if(liste == NULL)
	{
	    /* Si la liste est vide, il n'y a rien à effacer, on retourne 
	       une liste vide i.e. NULL */
	    return NULL;
	}
    else
	{
	    /* Sinon, on efface le premier élément et on retourne le reste de la 
	       liste effacée */
	    element *tmp;
	    tmp = liste->nxt;
	    free(liste);
	    return effacerListe(tmp);
	}
}

llist supprimerElement(llist liste, int valeur)
{
    /* Liste vide, il n'y a plus rien à supprimer */
    if(liste == NULL)
	return NULL;
 
    /* Si l'élément en cours de traitement doit être supprimé */
    if(liste->val == valeur)
	{
	    /* On le supprime en prenant soin de mémoriser 
	       l'adresse de l'élément suivant */
	    element* tmp = liste->nxt;
	    free(liste);
	    /* L'élément ayant été supprimé, la liste commencera à l'élément suivant
	       pointant sur une liste qui ne contient plus aucun élément ayant la valeur recherchée */
	    tmp = supprimerElement(tmp, valeur);
	    return tmp;
	}
    else
	{
	    /* Si l'élement en cours de traitement ne doit pas être supprimé,
	       alors la liste finale commencera par cet élément et suivra une liste ne contenant
	       plus d'élément ayant la valeur recherchée */
	    liste->nxt = supprimerElement(liste->nxt, valeur);
	    return liste;
	}
}



int main(int argc, char **argv)
{
    /* Déclarons 3 listes chaînées de façons différentes mais équivalentes */
    llist ma_liste1 = NULL;
    element *ma_liste2 = NULL;
    struct element *ma_liste3 = NULL;
    {
	llist ma_liste = NULL;
	int i;
 
	for(i=1;i<=10;i++)
	    {
		ma_liste = ajouterEnTete(ma_liste, i);
		ma_liste = ajouterEnFin(ma_liste, i);
	    }
	afficherListe(ma_liste);
 
	supprimerListe(ma_liste); // Libère les ressources, nous verrons cette fonction plus tard.
 
	return 0;
    }
