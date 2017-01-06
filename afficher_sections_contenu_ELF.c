#include "afficher_sections_contenu_ELF.h"

int cmpstr (unsigned char * ch1, unsigned char * ch2) {
	
	int i = 0 ;
	
	for (; ch1[i] && ch2[i] && ch1[i] == ch2[i] ; i++) ;
		
		return ch1[i] == ch2[i] ;
		
}

int indice_nom_entete (donnees_ELF ELF, char *nom) {
	
	int i = 0 ;
	
	while (i < ELF->les && cmpstr((ELF->Table_Chaines_ES + ELF->Entetes_Sections[i]->sh_name), (unsigned char *) nom)) i++ ;
	
	return i ;
		
}


void afficherContenuSection(donnees_ELF ELF, int section){

	//if (section != ELF->ind_etsymtab) {
	
		for (int i = 0 ; i < ELF->Entetes_Sections[section]->sh_size ; i++) {
	
			printf("%.2x ", *((unsigned char *)ELF->Sections[section] + i));
    
    	}
    	
    //else {
    
    	
}

void afficher_contenu_sections (donnees_ELF ELF, char * index_char) {
	
	int section , i = 0 ;
	
	while (index_char[i] && isdigit( (int)index_char[i]) ) i++ ;
	
	if (index_char[i]) {
		
		section = indice_nom_entete (ELF, index_char) ;
		
	}
		
	else {
		
		section = atoi(index_char) ;
		
	}

	if (section < ELF->les) {
	
		printf("Vidange héxadécimale de la section \"%s\"", index_char);
		printf("\n") ;
		afficherContenuSection(ELF, section) ;
		
	}
    		
    else {
		
    	printf("La section n'a pas de données à être vidangé.") ;
    }
    		    		
}
