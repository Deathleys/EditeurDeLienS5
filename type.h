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
	Elf32_Shdr **Entetes_Sections ; // stocke les entêtes de section
	Elf32_Sym  **Table_Symboles ; // stocke les symboles de type Elf32_Sym 
	unsigned char **Sections ;    // stocke le contenu des sections
	
	int ind_etstrtabes ; // indice de la table des chaines des noms des entêtes de section (.shstrtab)
	int ind_etsymtab ;  // indice  de la table des symboles (.symtab) 
	int ind_etstrtab ;  // indice  de la table des chaines de symboles (.strtab)
	int les ;           // nombre d'entêtes de section (ou nombre de sections) 
	int lts ;			// nombre de symboles
	unsigned char *Table_Chaines_ES ; // table des chaines des noms des entêtes de section (.shstrtab)
	unsigned char *Table_Chaines ;  // table des chaines des noms de symbole (.strtab)
	
} *donnees_ELF ;

#endif
