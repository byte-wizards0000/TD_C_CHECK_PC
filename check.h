#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LINE_CHAR_MAX 255

typedef struct person person;
typedef enum presence presence;

enum presence
{
	OUI = 1,
	NON = 2,
	PERSO = 3,
	ABSENT = 4
};

struct person
{
	char numero[3];
	char nom[30];
	char prenom[40];
	char check[15];
	char temp[15];
};

void fontionPrincipale();													
//appel de tous les fontions

int nombreEleve(FILE* fichier, char* tab);									
//obtenir nombre eleve

void obtenirInfo(FILE *fichier, char *tab, person *l1);						
//obtenir nom eleve

void recherche(char *tab, int nbreleve, person *l1, int *num, int *number);	
//recherche de l'eleve a checker

void check(person *l1, int i);												
//checker les pc

void checker(person *l1, int nbreleve, char *tab, int *number, int num);	
//menu du check

void printInfo(person *l1, int nbreleve);									
//ecrire dans le fichier temporaire

void affiche(char *tab);													
//affichage de tous les eleves

void searcheAffiche(person *l1, char *tab, int num);						
//affichage de l'eleve a checker

char *toLowerCase(char *i_str);												
//conversion en minuscule

void search();																
//recherche

void sortie(char *tab);														
//sauvegarde du check