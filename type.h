#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <elf.h>
#include <byteswap.h>
#include <string.h>
#include "util.h"

#define TAILLE_MAGIC_NUMBER 4
#define MODE_BIG_ENDIAN 2
#define CLASSE_32BITS 1


// Déclaration d'un type Cellule_Rel pour chaîner les sections de relocation

typedef struct Section_Rel {

	Elf32_Rel   *Entrees_Rel ;
	struct Section_Rel *succ ;
	                 int ind ;
	                 int nbr ;
	
} Section_Rel ;

typedef struct donnees_ELF {
	
	Elf32_Ehdr *Entete_ELF ;         // stocke l'en-tête du fichier ELF
	Elf32_Phdr *Entete_Programme ;   // stocke l'en-tête du programme (optionnel)
	Elf32_Shdr **Entetes_Sections ;  // stocke les en-têtes de section
	Elf32_Sym  **Table_Symboles ;    // stocke les symboles de type Elf32_Sym 
	Section_Rel *Table_Rel ;         // stocke les entrées de relocation (par section) de type Elf32_Rel
	
	char *Table_Chaines_ES ;         // table des chaines des noms des entêtes de section (.shstrtab)
	char *Table_Chaines ;            // table des chaines des noms de symbole (.strtab)
	void **Sections ;                // stocke le contenu des sections
	
	int les ;                        // nombre d'en-têtes de section (ou nombre de sections) 
	int lts ;			             // nombre de symboles
	
} *donnees_ELF ;

#endif
