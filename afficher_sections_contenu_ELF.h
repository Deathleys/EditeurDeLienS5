#ifndef AFFICHER_SECTIONS_CONTENU_ELF_H
#define AFFICHER_SECTIONS_CONTENU_ELF_H

#include <string.h>
#include "type.h"

void get_nom_section(char* str, Elf32_Shdr* En_Tete_Section, char* nom);

int getIndexByName(Elf32_Ehdr* En_Tete_ELF, Elf32_Shdr** Entetes_Section, char *tableNoms, char* nomSection);

unsigned char* getContenuSection(Elf32_Shdr* Entete_Section, FILE* f);

int getIndex(donnees_ELF ELF, FILE *f , char* index_char) ;

void afficher_contenu_sections (donnees_ELF ELF, FILE *f ,char *index_char ) ;

#endif
