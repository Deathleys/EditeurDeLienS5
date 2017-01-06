#include "afficher_symbole_ELF.h"

void afficher_nom_symbole(char* str, Elf32_Sym *symbole) { 
	
	int i = symbole->st_name;
	if(i!=0){
       	while (str[i] != '\0') { 
           	printf("%c", str[i]);
           	i++;
	       }	
	}
	
}


void afficher_ndx_symbole(Elf32_Sym *symbole) {

	//printf("Relation section : ") ;

	switch (symbole->st_shndx) {
		case 0: printf("UND "); break;
		case 65521: printf("ABS "); break;
		case 65522: printf("COM "); break;
		default : printf("%i";symbole->st_shndx) ;	
	}
}

void afficher_type_symbole(Elf32_Sym *symbole) {
	
	//Vérifier ELF32_ST_TYPE(), besoin pour récolter info.

	//printf("Type de symbole et de liaison : ") ;

	switch ( ELF32_ST_TYPE(symbole->st_info) {
	
		case STT_NOTYPE : printf("Indéfini") ; break ;
		case STT_OBJECT  : printf("Donnée objet") ; break ;
		case STT_FUNC : printf("Fonc. ou code exéc.") ; break ;
		case STT_SECTION  : printf("Section") ; break ;
		case STT_FILE  : printf("Fichier") ; break ; // A vérifier, donne le nom de fichier normalement.
		case STT_LOPROC : printf("Spéc. au Proc.") ; break ;
		case STT_HIPROC : printf("Spéc. au Proc.") ; break ;
		default : printf("Erreur") ;
		
	}
	
}

void afficher_portee_symbole (Elf32_Sym *symbole) {
	
	// Vérifier ELF32_ST_BIND()

	//printf("Type de portée : ") ;
	
	switch (ELF32_ST_BIND(symbole->st_info)) {
	
		case STB_LOCAL : printf("Locale") ; break ;
		case STB_GLOBAL  : printf("Global") ; break ;
		case STB_WEAK : printf("Faible") ; break ;
		case STB_LOPROC : printf("Spécifique au Processeur") ; break ;
		case STB_HIPROC : printf("Spécifique au Processeur") ; break ;
		default : printf("Erreur") ;
		
	}
	
}

void afficher_valeur_symbole (Elf32_Sym *symbole) {

	//printf("Valeur : ") ;
	
	printf("%u",symbole->st_value)
	
}

void afficher_taille_symbole (Elf32_Sym *symbole) {

	//printf("Taille : ") ;
	
	printf("%06u",symbole->st_size)
	
}

void afficher_visibilite_symbole(Elf32_Sym *symbole) {
	
	//Vérifier ELF32_ST_TYPE()

	//printf("Type de visibilité : ") ;
	
	switch (symbole->other) {
	
		case STV_DEFAULT : printf("Indéfini") ; break ;
		case STV_HIDDEN : printf("Non valable dans d'autres modules") ; break ;
		case STV_PROTECTED  : printf("Préemptible ou non exporté") ; break ;
		default : printf("Erreur") ;
		
	}
	
}

void afficher_table_symbole (donnee_ELF ELF) {
	int i ;
	printf("Num\tValeur\tTail\tType\tLien\tVis\tNdx\tNom\n");	
    		
    for (i = 0 ; i < ELF->lts ; i++) {

		printf("[%i]:\t", i);
		afficher_valeur_symbole (ELF->Tables_Symbole) ;printf("\t");
		afficher_taille_symbole (ELF->Tables_Symbole) ;printf("\t");
		afficher_type_symbole (ELF->Tables_Symbole);printf("\t");
		afficher_portee_symbole_symbole (ELF->Tables_Symbole);printf("\t");
		afficher_visibilite_symbole(ELF->Tables_Symbole) ;printf("\t");
		afficher_ndx_symbole(ELF->Tables_Symbole);printf("\t");
		afficher_nom_symbole(ELF->Table_Chaines,ELF->Tables_Symbole); // Changer tables_chaines pour prendre la table des symboles.
		printf("\n");
		
	}
	
}