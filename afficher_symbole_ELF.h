#ifndef AFFICHER_SYMBOLE_ELF_H
#define AFFICHER_SYMBOLE_ELF_H

#include "type.h"

#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

void afficher_nom_symbole(char* str,Elf32_Sym *symbole);

void afficher_type_symbole (Elf32_Sym *symbole);

void afficher_portee_symbole (Elf32_Sym *symbole);

void afficher_valeur_symbole (Elf32_Sym *symbole) ;

void afficher_taille_symbole (Elf32_Sym *symbole) ;

void afficher_visibilite_symbole(Elf32_Sym *symbole) ;

void afficher_table_symbole (donnee_ELF ELF);

#endif
