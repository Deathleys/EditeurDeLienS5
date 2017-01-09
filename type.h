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

typedef struct Cellule_Rel {

	Elf32_Rel   *Section_Rel ;
	struct Cellule_Rel *succ ;
	
} Cellule_Rel ;

typedef struct donnees_ELF {
	
	Elf32_Ehdr *Entete_ELF ;         // stocke l'en-tête du fichier ELF
	Elf32_Phdr *Entete_Programme ;   // stocke l'en-tête du programme (optionnel)
	Elf32_Shdr **Entetes_Sections ;  // stocke les en-têtes de section
	Elf32_Sym  **Table_Symboles ;    // stocke les symboles de type Elf32_Sym 
	Cellule_Rel *Table_Rel ;         // stocke les entrées de relocation (par section) de type Elf32_Rel
	//int *indiceRelocations; 	     // indices des sections de relocation
	
	char *Table_Chaines_ES ;         // table des chaines des noms des entêtes de section (.shstrtab)
	char *Table_Chaines ;            // table des chaines des noms de symbole (.strtab)
	void **Sections ;                // stocke le contenu des sections
	
	int ind_etstrtabes ;             // indice  de la table des chaines des noms des entêtes de section (.shstrtab)
	int ind_etsymtab ;               // indice  de la table des symboles (.symtab) 
	int ind_etstrtab ;               // indice  de la table des chaines de symboles (.strtab)
	
	int les ;                        // nombre d'en-têtes de section (ou nombre de sections) 
	int lts ;			             // nombre de symboles
	int lsr; 			             // nombre de sections de relocation
	
} *donnees_ELF ;

#endif
