#ifndef AFFICHER_SYMBOLE_ELF_H
#define AFFICHER_SYMBOLE_ELF_H

#include "type.h"
#include "tableau.h"

#define TITRE_TS "TABLE DES SYMBOLES :"
#define NB_COL_TS 7
#define COL_SYMTAB 40
#define LONGUEUR_TS (NB_COL_TS * COL + 2)
#define COULEUR_POLICE_TS 34
#define COULEUR_CARRE_TS 41

#define DESSINER_COL_NOM_TS() DESSINER_COL(COULEUR_CARRE_TS, COL_SYMTAB, 1)

#define DESSINER_COL_TS() CARRE(COULEUR_CARRE_TS) ; DESSINER_COL_NOM_TS ()  ;\
						   DESSINER_COL(COULEUR_CARRE_TS, LONGUEUR_TS / NB_COL_TS, NB_COL_TS) ; printf("\n")

void afficher_nom_symbole(donnees_ELF ELF, int i);

void afficher_type_symbole (Elf32_Sym *symbole);

void afficher_portee_symbole (Elf32_Sym *symbole);

void afficher_valeur_symbole (Elf32_Sym *symbole) ;

void afficher_taille_symbole (Elf32_Sym *symbole) ;

void afficher_visibilite_symbole(Elf32_Sym *symbole) ;

void afficher_table_symboles (donnees_ELF ELF);

#endif
