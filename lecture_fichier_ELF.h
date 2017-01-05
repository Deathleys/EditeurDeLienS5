#ifndef LECTURE_FICHIER_ELF_H
#define LECTURE_FICHIER_ELF_H

#include "type.h"
#include "afficher_entete_ELF.h"
#include "afficher_sections_ELF.h"

void afficher_type_fichier (Elf32_Ehdr *En_Tete) ;

Elf32_Ehdr * lire_Entete_ELF (FILE *f) ;

Elf32_Phdr * lire_Entete_Programme (Elf32_Ehdr *En_Tete, FILE *f) ;

void lire_Entetes_Sections (donnees_ELF Entetes_Sections, FILE *f) ;

int est_fichier_ELF (char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr *En_Tete) ;
	
#endif
