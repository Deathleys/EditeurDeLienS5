#include "type.h"

void afficher_entete_ELF (Elf32_Ehdr *Entete) ;

void afficher_entetes_section (donnees_ELF Entetes_Sections) ;

void afficher_contenus_section (donnees_ELF ELF, char *section) ;

void afficher_table_symboles (donnees_ELF ELF) ;

void afficher_sections_reimplantation (donnees_ELF ELF) ;


