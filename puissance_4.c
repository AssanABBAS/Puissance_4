// ABBAS Assan    28606493  email: assan.gilles.abbas@gmail.com
// DEANGELI Mateo 28603357  email: matdeabra@gmail.com


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int NB_LIGNES = 6;
const int NB_COLONNES = 7;


// fonction optionnelle qui remplace les conditions while lorsqu'on demande à l'utilisateur de rentrer une lettre 
int entrer_booleen(char e, char t, char T, char f, char F)
{
	if (e == t || e == T || e == F || e == f)
		return 1;
	else
		return 0;
}

struct Puiss4 {
	int grille1[6][7]; //contenant respectivement les pions des joueurs 1 et 2 
						//(un 0 correspond à une case vide et un 1 à une case contenant un pion);
	int grille2[6][7];
	int dernier_pion[7];// la ième case donne le numéro de la plus haute ligne contenant un pion dans la ième colonne de la grille 
						//(on prendra par convention la valeur -1 pour une colonne vide).
};

struct Puiss4 initialisation(int* joueur_1_IA, int* joueur_2_IA)
{
	struct Puiss4 jeu;
	// initialisation de la grille
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			jeu.grille1[i][j] = 0;
			jeu.grille2[i][j] = 0;         //Les 3 grilles sont vides
			jeu.dernier_pion[j] = -1;
		}
	}

	// Types de joueurs : IA ou utilisateur
	char entree;
	do
	{
		printf("joueur 1 est-il une IA : oui ou non\n");
		scanf_s(" %c", &entree);
	} while (entrer_booleen(entree, 'o', 'O', 'n', 'N') == 0);
	if (entree == 'O' || entree == 'o')
		*joueur_1_IA = 1;   //joueur 1 est une IA
	else
		*joueur_1_IA = 0;	//joueur 1 est un utilisateur
	do
	{
		printf("joueur 2 est-il une IA : oui ou non\n");
		scanf_s(" %c", &entree);
	} while (entrer_booleen(entree, 'o', 'O', 'n', 'N') == 0);
	if (entree == 'O' || entree == 'o')
		*joueur_2_IA = 1;	//joueur 2 est une IA
	else
		*joueur_2_IA = 0;	//joueur 2 est un utilisateur
	return jeu;
}


void affiche_jeu(struct Puiss4 jeu)  //affichage de la grille
{
	for (int i = 5; i >= 0; i = i - 1)
	{
		printf("%d - | ", i + 1);        // affichage des nombres sur la gauche
		for (int j = 0; j < 7; j++)
		{
			if ((jeu.grille1[i][j] == 1) && (jeu.grille2[i][j] == 1))   //Test afin de vérifier qu'on ne peut pas jouer dans cette case
				printf("ERREUR! Deux pièces sont à la même case");

			if (jeu.grille1[i][j] == 1)
			{
				printf("x | ");             //remplissage de la grille 1 par le joueur 1
			}
			else if (jeu.grille2[i][j] == 1)
			{
				printf("o | ");				// remplissage de la grille 2 par le joueur 2
			}
			else
			{
				printf("  | ");
			}

		}
		printf("\n");
	}
	printf("     ---------------------------");
	printf("\n     ");
	for (int j = 1; j < 8; j++) {
		printf(" %d  ", j);
	}
	printf("\n");
}

struct Puiss4 ajoute_pion(struct Puiss4 jeu, int joueur, int num_col)   //debut de partie
{
	int ligne = 0;
	while (jeu.grille1[ligne][num_col] == 1 || jeu.grille2[ligne][num_col] == 1)  //boucle while pour que le jeton soit dans la bonne ligne
	{
		ligne++;
	}
	if (joueur == 1)
	{
		jeu.grille1[ligne][num_col] = 1;  //remplissage de la grille du joueur 1
		jeu.dernier_pion[num_col] = 1;
	}
	else
	{
		jeu.grille2[ligne][num_col] = 1;  //remplissage de la grille du joueur 2
		jeu.dernier_pion[num_col] = 1;
	}
	return jeu;
}

// fonction random pour que l'IA joue
struct Puiss4 coup_ia(struct Puiss4 jeu, int joueur)
{
	int num_col;
	do
	{
		num_col = rand() % 7;  //%7 pour que le nombre choisi aléatoirement reste entre 0 et 1
	} while (jeu.grille1[5][num_col] == 1 || jeu.grille2[5][num_col] == 1);
	return ajoute_pion(jeu, joueur, num_col);
}

struct Puiss4 coup_joueur(struct Puiss4 jeu, int joueur)
{
	int num_col;
	do           //boucle while afin que le joueur puisse rentrer un numéro de colone valide
	{
		printf("--------------- Entrez le numero de la colonne : --------------\n");
		scanf_s("%d", &num_col);									 //demande de la colonne où on veut mettre le pion
		printf("\n");
		num_col--;													//afin qu'il mette le pion dans la colonne qu'on a demandé
	} while (num_col < 0 || num_col>7 || jeu.grille1[5][num_col] == 1 || jeu.grille2[5][num_col] == 1);
	return ajoute_pion(jeu, joueur, num_col);
}


int grille_remplie(struct Puiss4 jeu)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (jeu.grille1[i][j] == 0 && jeu.grille2[i][j] == 0)  //test pour vérifier si les cases sont remplies ou non
			{
				return 0;
			}
		}
	}
	puts("\nLa grille est remplie\n");
	return 1;
}

int gagne(struct Puiss4 jeu, int joueur, int* point_J1, int* point_J2)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (joueur == 1)
			{
				int pion_aligne = 0;
				int k = i;
				while (jeu.grille1[k][j] == 1 && k < 6)  //on regarde verticalement entre 1 et 6 pour ne pas sortir de la grille 
				{
					k++;
					pion_aligne++;
				}
				if (pion_aligne > 3)
				{
					printf("--------- PUISSANCE %d : LE JOUEUR 1 A GAGNE !!! ---------------\n\n", pion_aligne);
					*point_J1 += 10;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
				pion_aligne = 0;
				k = j;
				while (jeu.grille1[i][k] == 1 && k < 7)//on regarde horizontalement entre 1 et 7 pour ne pas sortir de la grille 
				{
					k++;
					pion_aligne++;
				}
				if (pion_aligne > 3)
				{
					printf("--------- PUISSANCE %d : LE JOUEUR 1 A GAGNE !!! ---------------\n\n", pion_aligne);
					*point_J1 += 10;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
				pion_aligne = 0;
				int l = i;
				k = j;
				while (jeu.grille1[l][k] == 1 && l < 6 && k < 7) //on regarde la diagonale ascendante entre 1 et 6 pour la verticale
				{												// et 1 et 7 pour l'horizontale pour ne pas sortir de la grille 
					k++;
					l++;
					pion_aligne++;
				}
				if (pion_aligne > 3)
				{
					printf("--------- PUISSANCE %d : LE JOUEUR 1 A GAGNE !!! ---------------\n\n", pion_aligne);
					*point_J1 += 10;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
				pion_aligne = 0;
				l = i;
				k = j;
				while (jeu.grille1[l][k] == 1 && l >= 0 && k < 7) //on regarde la diagonale descendante entre 1 et 6 pour la verticale avec un pas négatif 
				{												 // et 1 et 7 pour l'horizontale pour ne pas sortir de la grille 
					k++;
					l--;
					pion_aligne++;
				}
				if (pion_aligne > 3)
				{
					printf("--------- PUISSANCE %d : LE JOUEUR 1 A GAGNE !!! ---------------\n\n", pion_aligne);
					*point_J1 += 10;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
				else
				{
					printf("------------------------ MATCH NUL ----------------------------\n\n");
					*point_J1 += 5;
					*point_J2 += 5;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
			}
			if (joueur == 2)
			{
				int pion_aligne = 0;
				int k = i;
				while (jeu.grille2[k][j] == 1 && k < 6)
				{
					k++;
					pion_aligne++;
				}
				if (pion_aligne > 3)
				{
					printf("--------- PUISSANCE %d : LE JOUEUR 2 A GAGNE !!! ---------------\n\n", pion_aligne);
					*point_J2 += 10;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
				pion_aligne = 0;
				k = j;
				while (jeu.grille2[i][k] == 1 && k < 7)
				{
					k++;
					pion_aligne++;
				}
				if (pion_aligne > 3)
				{
					printf("--------- PUISSANCE %d : LE JOUEUR 2 A GAGNE !!! ---------------\n\n", pion_aligne);
					*point_J2 += 10;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
				pion_aligne = 0;
				int l = i;
				k = j;
				while (jeu.grille2[l][k] == 1 && l < 6 && k < 7)
				{
					k++;
					l++;
					pion_aligne++;
				}
				if (pion_aligne > 3)
				{
					printf("--------- PUISSANCE %d : LE JOUEUR 2 A GAGNE !!! ---------------\n\n", pion_aligne);
					*point_J2 += 10;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
				pion_aligne = 0;
				l = i;
				k = j;
				while (jeu.grille2[l][k] == 1 && l >= 0 && k < 7)
				{
					k++;
					l--;
					pion_aligne++;
				}
				if (pion_aligne > 3)
				{
					printf("-------PUISSANCE %d : le joueur 2 A GAGNE !!! ---------------\n\n", pion_aligne);
					*point_J2 += 10;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
				else
				{
					printf("------------------------ MATCH NUL ----------------------------\n\n");
					*point_J1 += 5;
					*point_J2 += 5;
					printf("\nLe joueur 1 a %d points\nLe joueur 2 a %d points\n\n", *point_J1, *point_J2);
					return 1;
				}
			}

		}
	}
	return 0;
}

void sauvegarde(struct Puiss4 jeu, int joueur, int nb_tour, int joueur_1_IA, int joueur_2_IA, int point_J1, int point_J2)
{
	FILE* writesave;
	fopen_s(&writesave, "sauvegarde.txt", "w+");
	if (writesave == NULL)
	{
		puts("Il n'y a pas de sauvegarde\nFin du programme.");
		return 0;
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				fprintf(writesave, " %d", jeu.grille1[i][j]);
				fprintf(writesave, " %d", jeu.grille2[i][j]);
			}
		}
		fprintf(writesave, " %d", nb_tour);
		fprintf(writesave, " %d", joueur_1_IA);
		fprintf(writesave, " %d", joueur_2_IA);
		fprintf(writesave, " %d", point_J1);
		fprintf(writesave, " %d", point_J2);
	}
	fclose(writesave);
}

struct Puiss4 charge(int* nb_tour, int* joueur_1_IA, int* joueur_2_IA, int* point_J1, int* point_J2) //pointeur car lorsqu'on chargera les valeurs on veut modifier les vraies valeurs et non la copie 
{
	struct Puiss4 jeu;
	FILE* readsave;
	fopen_s(&readsave, "sauvegarde.txt", "r");
	if (readsave == NULL)
	{
		puts("Probleme a l'ouverture de 'save.txt'\nFin du programme.");
		jeu = initialisation(joueur_1_IA, joueur_2_IA);
	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				fscanf_s(readsave, " %d", &jeu.grille1[i][j]);
				fscanf_s(readsave, " %d", &jeu.grille2[i][j]);
			}
		}
		fscanf_s(readsave, " %d", nb_tour);
		fscanf_s(readsave, " %d", joueur_1_IA);
		fscanf_s(readsave, " %d", joueur_2_IA);
		fscanf_s(readsave, " %d", point_J1);
		fscanf_s(readsave, " %d", point_J2);
		fclose(readsave);
	}

	return jeu;
}


int main()          // début de partie
{
	// Propriétés de la partie
	char new_game, save;
	int tour = 1, point_J1 = 0, point_J2 = 0, num_joueur;
	int partie_terminee = 0;
	char nouvelle_partie = 'n';
	int joueur_1_IA = 0;
	int joueur_2_IA = 0;

	struct Puiss4 p;
	do
	{
		printf("Voulez-vous commencer une nouvelle partie ?\nEcrivez o ou O pour oui et n ou N pour charger une ancienne\n");  // demande nouvelle ou chargement partie
		printf("\n");
		scanf_s(" %c", &new_game);
		printf("\n");
		if (new_game == 'o' || new_game == 'O')
		{
			p = initialisation(&joueur_1_IA, &joueur_2_IA);  //nouvelle partie
		}
		else if (new_game == 'n' || new_game == 'N')
		{
			p = charge(&tour, &joueur_1_IA, &joueur_2_IA, &point_J1, &point_J2); // chargement ancienne partie
		}
	} while (new_game != 'o' && new_game != 'n' && new_game != 'O' && new_game != 'N');

	affiche_jeu(p);
	do  // afin de recommencencer une partie après la fin de la première
	{
		if (nouvelle_partie == 'o' || nouvelle_partie == 'O')
		{
			p = initialisation(&joueur_1_IA, &joueur_2_IA);
			partie_terminee = 0;
			tour = 1;
		}

		while (partie_terminee == 0)
		{
			printf("\n");
			printf("---------------------------------------------------------------\n");
			printf("------------------------- Tour %d -----------------------------\n", tour);
			printf("---------------------------------------------------------------\n");
			printf("\n");

			if (tour % 2 == 1)
			{
				printf("--------------------A joueur 1 de jouer !----------------------\n");
				if (joueur_1_IA == 1)  // si le joueur est une IA
				{
					p = coup_ia(p, 1);
				}
				else  //si le joueur est un utilisateur
				{
					p = coup_joueur(p, 1);
				}
				tour++;
				partie_terminee += gagne(p, 1, &point_J1, &point_J2); //verifie si le joueur 1 a gagne
				affiche_jeu(p);
				printf_s("---------\n");
				printf_s("Voulez-vous sauvegarder ?\n");
				do
				{
					printf("Ecrivez o ou O pour oui et n ou N pour non.\n");
					scanf_s(" %c", &save);
					printf("\n");
					if (save == 'o' || save == 'O')
					{
						sauvegarde(p, 1, tour, joueur_1_IA, joueur_2_IA, point_J1, point_J2);
						printf("Partie sauvegardee.\n\n");
					}
				} while (save != 'o' && save != 'n' && save != 'O' && save != 'N');

			}
			else
			{
				printf("------------------- A joueur 2 de jouer ! --------------------- \n");
				if (joueur_2_IA == 1)
				{
					p = coup_ia(p, 2);
				}
				else
				{
					p = coup_joueur(p, 2);
				}
				tour++;
				partie_terminee += gagne(p, 2, &point_J1, &point_J2);
				affiche_jeu(p);
				printf_s("---------\n");
				printf_s("Voulez-vous sauvegarder ?\n");
				do
				{
					printf("Ecrivez o ou O pour oui et n ou N pour non.\n");
					scanf_s(" %c", &save);
					printf("\n");
					if (save == 'o' || save == 'O')
					{
						sauvegarde(p, 2, tour, joueur_1_IA, joueur_2_IA, point_J1, point_J2);
						printf("Partie sauvegardee.\n\n");
					}
				} while (save != 'o' && save != 'n' && save != 'O' && save != 'N');
			}
			partie_terminee += grille_remplie(p);
		}
		// Demander à faire une nouvelle partie
		do {
			printf("Voulez-vous faire une nouvelle partie ?\nEcrivez o ou O pour oui et n ou N pour non\n");
			printf("\n");
			scanf_s(" %c", &nouvelle_partie);
			printf("\n");
		} while (nouvelle_partie != 'o' && nouvelle_partie != 'n' && nouvelle_partie != 'O' && nouvelle_partie != 'N');

	} while (nouvelle_partie == 'o' || nouvelle_partie == 'O'); //si le joueur demande une nouvelle partie on recommence en sauvegardant les points
	affiche_jeu(p);
	return 0;
}