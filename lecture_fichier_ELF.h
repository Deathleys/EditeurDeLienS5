#ifndef LECTURE_FICHIER_ELF_H
#define LECTURE_FICHIER_ELF_H

#include "type.h"
#include "afficher_entete_ELF.h"
#include "afficher_sections_ELF.h"
#include "afficher_sections_contenu_ELF.h"

void lire_Entete_ELF (donnees_ELF ELF, FILE *f) ;

void lire_Entete_Programme (donnees_ELF ELF, FILE *f) ;

void lire_Entetes_Sections (donnees_ELF ELF, FILE *f) ;

int est_fichier_ELF (unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr *En_Tete) ;
	
#endif
