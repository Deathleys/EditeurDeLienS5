#ifndef AFFICHER_SECTIONS_ELF_H
#define AFFICHER_SECTIONS_ELF_H

#include "type.h"

Elf32_Shdr* lire_Entete_Section(FILE* f, int index, Elf32_Ehdr* Entete_ELF) ;

void afficher_type_section (Elf32_Shdr* Entete_Section) ;

void afficher_addr_section(Elf32_Shdr* Entete_Section) ;

void afficher_decalage_section(Elf32_Shdr* Entete_Section) ;

void afficher_size_section(Elf32_Shdr* Entete_Section) ;

void afficher_info_section(Elf32_Shdr* Entete_Section) ;

void afficher_flags_section(Elf32_Shdr* Entete_Section) ;

void afficher_legende_flags() ;

void afficher_nom_section(char* str, Elf32_Shdr* Entete_Section) ;

char* getTableNoms(donnees_ELF ELF, FILE *f) ;

void afficher_entetes_sections (donnees_ELF Entetes_Sections) ;

#endif
