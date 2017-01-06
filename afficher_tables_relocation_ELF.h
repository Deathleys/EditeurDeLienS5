#ifndef AFFICHER_TABLES_RELOCATION_ELF_H
#define AFFICHER_TABLES_RELOCATION_ELF_H
#include "type.h"



char* getTypeRelocation(Elf32_Word r_info);

void afficher_tables_relocation(FILE* f, donnees_ELF ELF);

char *typeRelocation[];

Elf32_Sym *getSymbole(donnees_ELF ELF, Elf32_Word r_info);

void REafficher_nom_symbole(unsigned char* table, Elf32_Sym *symbole);

/* 
1) Ajouter à la structure ELF dans type .h :
	Elf32_Rel **Table_Relocation; // stocke les entrees de relocation (par section) de type Elf32_Rel 
	int *indiceRelocations; 	// stocke les indices des sections de relocation
	int lsr; 			// nombre de sections de relocations
	
2) Ajouter aux fonctions dans lecture_fichier.c : les 3 fonctions lire	
	Elf32_Rel lireRelocation(FILE* f, int numSec, int index, donnees_ELF ELF);
	Elf32_Rel* lireRelocationsDeSection(FILE* f, int j, donnees_ELF ELF);
	Elf32_Rel** lire_Table_Relocation(donnees_ELF ELF, FILE* f);

3) Ajouter au main de lecture_fichier : 
	afficher_tables_relocation(f,ELF);
	
*/
#endif
