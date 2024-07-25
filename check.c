#include "check.h"

void fontionPrincipale()
{

    int nbreleve = 0;
	int num = 0;
	int *number = NULL;
    int choixOption = 0;
    char *tab = NULL;
    person *l1 = NULL;
    FILE* fichier = NULL;
    
    tab = malloc(255*sizeof(char));
    fichier = fopen("listeL1.csv", "r");
    if(fichier == NULL)
    {
        printf("Erreur d'ouverture du fichier");
        exit(1);
    }
    nbreleve = nombreEleve(fichier, tab);
    l1 = malloc(nbreleve*sizeof(person));
    number = malloc(nbreleve*sizeof(int));

    obtenirInfo(fichier, tab, l1);

	while(1)
	{
		choose :
		printf(
		"\t\t ____________________________________________________________\n"
		"\t\t|                         Option:                            |\n"
		"\t\t|                                                            |\n"
		"\t\t|      1-  Checker les pc                                    |\n"
		"\t\t|      2-  Recherche des informations                        |\n"
		"\t\t|      3-  Affichage de tous les élèves                      |\n"
		"\t\t|      4-  Enregistrer le check d'aujourd'hui                |\n"
		"\t\t|      5-  Quitter                                           |\n"
		"\t\t|____________________________________________________________|\n"
		"\nEntrez votre choix : "
		);
		scanf("%d", &choixOption);
		switch(choixOption)
		{
			case 1:
				checker(l1, nbreleve, tab, number, num);
				printInfo(l1, nbreleve);
				break;
			case 2:
				search();
				break;
			case 3:
				affiche(tab);
				break;
			case 4:
				sortie(tab);
				break;
			case 5:
				goto quit;
				break;
			default:
				goto choose;
		}
	}

	quit :
    free(number);
    free(tab);
    free(l1);
    fclose(fichier);

}

int nombreEleve(FILE* fichier, char* tab)
{

    int nombre = 0;
    rewind(fichier);
    while(fgets(tab, 255, fichier) != NULL)
    {
        nombre++;
    }
    return nombre;

}

void obtenirInfo(FILE *fichier, char *tab, person *l1)
{

	int i = 0;
	int a = 0;
	int b = 0;
	rewind(fichier);
	while (fgets(tab, 255, fichier) != NULL)
	{
		for (i = 0; i < strlen(tab); i++)
		{
			b = 0;
			while (tab[i] != ';')
			{
				l1[a].numero[b] = tab[i];
				b++;
				i++;
			}
			b = 0;
			i++;
			while (tab[i] != ' ')
			{
				l1[a].nom[b] = tab[i];
				b++;
				i++;
			}
			i++;
			b = 0;
			while (tab[i] != ';')
			{
				l1[a].prenom[b] = tab[i];
				b++;
				i++;
			}
			break;
		}
		a++;
	}
}

void check(person *l1, int i)
{

	int choix;
	label :
		printf("1- OUI\n");
		printf("2- NON\n");
		printf("3- PERSO\n");
		printf("4- ABSENT\n");
		printf("%s : %s : %s : ", l1[i].numero, l1[i].nom, l1[i].prenom);
		scanf("%d", &choix);
		strcpy(l1[i].temp, __TIME__);
		switch(choix)
		{
			case OUI:
				strcpy(l1[i].check, "OUI");
				break;
			case NON:
				strcpy(l1[i].check, "NON");
				break;
			case PERSO:
				strcpy(l1[i].check, "PERSO");
				break;
			case ABSENT:
				strcpy(l1[i].check, "ABSENT");
				break;
			default:
				goto label;
		}

}

void recherche(char *tab, int nbreleve, person *l1, int* num, int *number)
{

	int i = 0;
	int verif = 0;
	int a = 0;
	retour :
		printf("Donner un indice du personne à rechercher : ");
		getchar();
		scanf("%[^\n]", tab);
		for(i = 0; i < nbreleve; i++)
		{
			if (strcmp(l1[i].nom, tab) == 0 || strcmp(l1[i].numero, tab) == 0 || strcmp(l1[i].prenom, tab) == 0 || strcmp(l1[i].check, tab) == 0)
			{
				number[a] = i;
				a++;
				verif = 1;
			}
		}
		if(verif == 0)
		{
			printf("Cette indice ne correspond à aucun profil\n");
			goto retour;
		}
	*num = a;

}

void checker(person *l1, int nbreleve, char *tab, int *number, int num)
{

	int i;
	int ckoixCheck;

	printf(
		"\t\t ____________________________________________________________\n"
		"\t\t|                                                            |\n"
		"\t\t|                         Option:                            |\n"
		"\t\t|      1-  Checker tous les pc                               |\n"
		"\t\t|      2-  Checker un à un                                   |\n"
		"\t\t|____________________________________________________________|\n"
		"\nEntrez votre choix : "
	);
	scanf("%d", &ckoixCheck);

	switch(ckoixCheck)
	{	
		case 1:
			for(i = 0; i < nbreleve; i++)
			{
				check(l1, i);
			}
			break;
		case 2:
			recherche(tab, nbreleve, l1, &num, number);
			check(l1, number[0]);
			break;
	}
	
}

void printInfo(person *l1, int nbreleve)
{

	int i = 0;
	FILE *fichier1 = NULL;
	fichier1 = fopen("index.html", "w");
	if (fichier1 == NULL)
	{
		exit(1);
	}

	fprintf(fichier1, 	"<HTML>\n"
						"\t<HEAD>\n"
					 	"\t\t<TITLE>\n"
					 	"\t\t\tPRESENCE L1\n"
					 	"\t\t</TITLE>\n"
					 	"\t</HEAD>\n"
					 	"\t<BODY>\n");

	fprintf(fichier1, "\t\t<CENTER><IMG src=\"logo_mit.png\"/></CENTER><BR>\n");

	fprintf(fichier1, "<center><FONT color=\"red\" size=\"20\">LISTE DE PRESENCE MIT</FONT></center>");

	fprintf(fichier1, "\t\t<CENTER><TABLE border=\"5\" bgcolor=\"#EE00FF\">\n");

	fprintf(fichier1, 	"\t\t\t<TR>\n"
						"\t\t\t\t<TD>NUMERO</TD>\n"
						"\t\t\t\t<TD>NOM</TD>\n"
						"\t\t\t\t<TD>PRENOM</TD>\n"
						"\t\t\t\t<TD>PRESENCE</TD>\n"
						"\t\t\t</TR>\n");
	for(i = 0; i < nbreleve; i++)
	{
		fprintf(fichier1, 	"\t\t\t<TR>\n");
		fprintf(fichier1, 	"\t\t\t\t<TD> %s </TD>\n", l1[i].numero);
		fprintf(fichier1,	"\t\t\t\t<TD> %s </TD>\n", l1[i].nom);
		fprintf(fichier1,	"\t\t\t\t<TD> %s </TD>\n", l1[i].prenom);
		if(strcmp(l1[i].check, "OUI") == 0)
		{
			fprintf(fichier1,	"\t\t\t\t<TD bgcolor=\"green\"> %s </TD>\n", l1[i].check);
		}
		else if(strcmp(l1[i].check, "NON") == 0)
		{
			fprintf(fichier1,	"\t\t\t\t<TD bgcolor=\"red\"> %s </TD>\n", l1[i].check);
		}
		else if(strcmp(l1[i].check, "PERSO") == 0)
		{
			fprintf(fichier1,	"\t\t\t\t<TD bgcolor=\"blue\"> %s </TD>\n", l1[i].check);
		}
		else if(strcmp(l1[i].check, "ABSENT") == 0)
		{
			fprintf(fichier1,	"\t\t\t\t<TD bgcolor=\"yellow\"> %s </TD>\n", l1[i].check);
		}
		else
		{
			fprintf(fichier1,	"\t\t\t\t<TD bgcolor=\"#EE00FF\"> %s </TD>\n", l1[i].check);
		}
		fprintf(fichier1, 	"\t\t\t</TR>\n");
	}

	fprintf(fichier1, "\t\t</TABLE></CENTER>\n");

	fprintf(fichier1, "\t</BODY>\n");
	fprintf(fichier1, "</HTML>\n");

	fclose(fichier1);
}

void affiche(char *tab)
{

	FILE *fichier1 = NULL;
	fichier1 = fopen("fichier_temp.csv", "r");
	if (fichier1 == NULL)
	{
		exit(1);
	}

	while (fgets(tab, 255, fichier1) != NULL)
	{
		printf("%s", tab);
	}

	fclose(fichier1);
}

void searcheAffiche(person *l1, char *tab, int num)
{
	
	int i = 0;
	int ligne = 0;
	int compteur;
	FILE* stream = NULL;
	stream = fopen("fichier_temp.csv", "r");

	while (fgets(tab, 255, stream) != NULL)
	{
		for (i = 0; i < strlen(tab); i++) // 1
		{
			if(tab[i] == '=')
			{
				printf("%s", tab);
				ligne = compteur;
				break;
			}
			if (compteur == (ligne + num) + 1)
			{
				printf("\n%s\n", tab);
				break;
			}
		}
		compteur++;
	}

	fclose(stream);
	return;
}

char *toLowerCase(char *i_str)
{
    int i;//loop 1
    char *f_str;
    f_str = malloc(sizeof(char)*strlen(i_str));

    for(i = 0; i < strlen(i_str); i++)
	{
        f_str[i] = tolower(i_str[i]);
	}

    return f_str;
}


void search()
{
	FILE *stream = NULL;
	stream = fopen("fichier_sortie.csv", "r");

    char *buff;
    buff = malloc(sizeof(char)*LINE_CHAR_MAX);
    
	char *toSearch;
	toSearch = malloc(sizeof(char)*LINE_CHAR_MAX);
	
	do
	{
		printf("recherche -> ");getchar();
		scanf("%[^\n]", toSearch); getchar();
	} while (strcmp(toSearch, " ") == 0 || strcmp(toSearch, "\t") == 0 || toSearch[0] == '\t');
		
    while ((fgets(buff, LINE_CHAR_MAX, stream)) != NULL)
    {
        if (strstr(toLowerCase(buff), toLowerCase(toSearch)) != NULL)
        {
            printf("%s", buff);
        }
    }

	free(toSearch);
	free(buff);
	fclose(stream);
    return;
}

void sortie(char *tab)
{
	FILE *fichier1 = NULL;
	FILE *fichier2 = NULL;
	fichier1 = fopen("fichier_temp.csv", "r");
	fichier2 = fopen("fichier_sortie.csv", "a");
	if (fichier1 == NULL || fichier2 == NULL)
	{
		exit(1);
	}

	while (fgets(tab, 255, fichier1) != NULL)
	{
		fprintf(fichier2, "%s", tab);
	}

	fclose(fichier1);
	fclose(fichier2);
}