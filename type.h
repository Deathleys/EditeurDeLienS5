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

// Déclaration d'un type Section_Progbits pour chaîner les sections de relocation

typedef struct Liste_Sym {
	
	Elf32_Sym * sym ;
	struct Liste_Sym * succ ;
	
} Liste_Sym ;


// Déclaration d'un type Section_Progbits pour chaîner les sections de relocation

typedef struct Section_Progbits {

	struct Section_Progbits *succ ;
	int ind ;
	int taille ;
	
} Section_Progbits ;

// Déclaration d'un type Cellule_Rel pour chaîner les sections de relocation

typedef struct Section_Rel {

	Elf32_Rel   *Entrees_Rel ;
	struct Section_Rel *succ ;
	                 int ind ;
	                 int nbr ;
	
} Section_Rel ;

typedef struct donnees_ELF {
	
	Elf32_Ehdr *Entete_ELF ;              // pointe sur l'en-tête du fichier ELF
	Elf32_Phdr *Entete_Programme ;        // pointe sur l'en-tête du programme (optionnel) 
	Elf32_Shdr **Entetes_Sections ;       // pointe sur la Table des en-têtes de section
	Elf32_Sym  **Table_Symboles ;         // pointe sur la Table des symboles de type Elf32_Sym 
	Section_Rel *Table_Rel ;              // pointe sur la Table de réimplantation des objets statiques
	Section_Progbits *Table_Progbits ;    // pointe sur la Table des sections Progbits
	
	char *Table_Chaines_ES ;              // pointe sur la Table des chaines des noms des entêtes de section (.shstrtab)
	char *Table_Chaines ;                 // pointe sur la Table des chaines des noms de symbole (.strtab)
	char **Sections ;                     // pointe sur la Table des contenus de sections
	
	        int les ;                     // nombre d'en-têtes de section (ou nombre de sections) 
		    int lts ;			          // nombre de symboles
	long int taille ;                     // taille du fichier ELF
	
} *donnees_ELF ;

donnees_ELF initialiser_donnees_ELF () ;

#endif
