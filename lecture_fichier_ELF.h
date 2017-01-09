#ifndef LECTURE_FICHIER_ELF_H
#define LECTURE_FICHIER_ELF_H

#include "type.h"
#include "affichage_ELF.h"

bool lire_Entete_ELF (donnees_ELF ELF, FILE *f) ;

bool lire_Entete_Programme (donnees_ELF ELF, FILE *f) ;

bool lire_Section (donnees_ELF ELF, int ind_section, FILE *f) ;

bool lire_Table_Symboles (donnees_ELF ELF, FILE *f) ;

bool lire_Table_Chaines_ES (donnees_ELF ELF, FILE *f) ;

bool lire_Table_Chaines (donnees_ELF ELF, FILE *f) ;

bool lire_Entetes_Sections (donnees_ELF ELF, FILE *f) ;

int est_fichier_ELF (unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr *En_Tete) ;
	
#endif
