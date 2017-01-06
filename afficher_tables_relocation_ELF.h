#ifndef AFFICHER_TABLES_RELOCATION_ELF_H
#define AFFICHER_TABLES_RELOCATION_ELF_H
#include "type.h"

//Elf32_Rel lireRelocation(FILE* f, int numSec, int index, donnees_ELF ELF);

//Elf32_Rel* lireRelocationsDeSection(FILE* f, int j, donnees_ELF ELF);

//Elf32_Rel** lire_Table_Relocation(donnees_ELF ELF, FILE* f);

char* getTypeRelocation(Elf32_Word r_info);

void afficher_tables_relocation(FILE* f, donnees_ELF ELF);

/* Ajouter au type .h
Elf32_Rel **Table_Relocation; // stocke les entrees de relocation (par section) de type Elf32_Rel 
	int *indiceRelocations; 	// stocke les indices des sections de relocation
	int lsr; 			// nombre de sections de relocations
	
Ajouter à lecture fichier : les 3 fonctins lire	
	

#endif
