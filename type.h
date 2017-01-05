#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <byteswap.h>
#include "util.h"

#define TAILLE_MAGIC_NUMBER 4
#define MODE_BIG_ENDIAN 2
#define CLASSE_32BITS 1

typedef struct donnees_ELF {
	
	Elf32_Ehdr *Entete_ELF ;
	Elf32_Phdr *Entete_Programme ;
	Elf32_Shdr **Entetes_Sections ;
	Elf32_Sym  *Table_Symboles ;
	int ind_etstrtab ;
	int ind_etsymtab ;
	int les ;
	int lTexte ;
	char *Table_Chaines ;
	char *Texte ;
	
} *donnees_ELF ;

#endif
