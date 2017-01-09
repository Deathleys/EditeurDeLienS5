#ifndef AFFICHER_SECTIONS_CONTENU_ELF_H
#define AFFICHER_SECTIONS_CONTENU_ELF_H

#include <ctype.h>
#include "tableau.h"
#include "type.h"

#define NB_COL_SC 5
#define LONGUEUR_SC (NB_COL_SC * COL + 2)
#define COULEUR_POLICE_SC 33
#define COULEUR_CARRE_SC 44

#define DESSINER_COL_SC(L) CARRE(COULEUR_CARRE_SC) ;\
						for (int i = 0 ; i < L - 2 ; i++) printf (" " )
						
#define DESSINER_3COL_SC() DESSINER_COL_SC(COL) ; DESSINER_COL_SC(COL * 2) ;\
						   DESSINER_COL_SC(COL * 2) ; CARRE(COULEUR_CARRE_SC) ; printf("\n")

int indice_nom_entete (donnees_ELF ELF, char *nom) ;

void afficher_contenu_section (donnees_ELF ELF, int ind_section) ;

void afficher_contenus_section (donnees_ELF ELF, char * index_char) ;

#endif
