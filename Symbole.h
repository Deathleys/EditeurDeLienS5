#ifndef AFFICHER_TABLE_SYMBOLE_H
#define AFFICHER_TABLE_SYMBOLE_H

#include "type.h"

void afficher_nom(Elf32_Sym *symbole);

void afficher_type (Elf32_Sym *symbole);

void afficher_portee_symbole (Elf32_Sym *symbole);

void afficher_valeur (Elf32_Sym *symbole) ;

void afficher_taille (Elf32_Sym *symbole) ;

void afficher_visibilite(Elf32_Sym *symbole) ;

void afficher_table_symbole (donnee_ELF ELF);

#endif
