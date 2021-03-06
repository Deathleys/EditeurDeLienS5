#ifndef LECTURE_FICHIER_ELF_H
#define LECTURE_FICHIER_ELF_H

#include "type.h"

char * lire_Donnees_ELF (Elf32_Ehdr Entete, FILE *f, long int *l) ;

bool lire_Entete_ELF (donnees_ELF *ELF, char ** Donnees_ELF, FILE *f, unsigned char * Magic_Number_ELF) ;

bool lire_Entete_Programme (donnees_ELF ELF, char * Donnees_ELF) ;

bool lire_Section (donnees_ELF ELF, int ind_section, char * Donnees_ELF) ;

bool lire_Table_Symboles (donnees_ELF ELF, int ind_table_symboles, char * Donnees_ELF) ;

bool lire_Table_Chaines (donnees_ELF ELF, int ind_table, char ** Table, char * Donnees_ELF) ;

bool lire_Section_Rel (donnees_ELF ELF, int ind_section_rel, Section_Rel **Table_Rel, char * Donnees_ELF) ;

bool lire_Section_Progbits (donnees_ELF ELF, int ind_section_progbits, Section_Progbits **Table_Progbits, char * Donnees_ELF) ;

bool lire_Entetes_Sections (donnees_ELF ELF, char * Donnees_ELF) ;

bool est_fichier_ELF (unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr Entete) ;

void lecture_fichier_ELF (donnees_ELF *ELF, char ** Donnees_ELF, FILE *f, char *nom_fich_ELF) ;
	
#endif
