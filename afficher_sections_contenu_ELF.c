#include "afficher_sections_contenu_ELF.h"

int indice_nom_entete (donnees_ELF ELF, char *nom) {
	
	int i = 0 ;
	
	while (i < ELF->les && strcmp((ELF->Table_Chaines_ES + ELF->Entetes_Sections[i]->sh_name), nom)) i++ ;
	
	return i ;
		
}


void afficher_contenu_section (donnees_ELF ELF, int ind_section){

	char * nom_section = ELF->Table_Chaines_ES + ELF->Entetes_Sections[ind_section]->sh_name ;

	if (ELF->Entetes_Sections[ind_section]->sh_size) {
	
		printf("Vidange héxadécimale de la section %d / %s :\n\n", ind_section, (nom_section[0] ? nom_section : "(pas de nom)")) ;
		
		char titre [100] ;
		
		sprintf(titre , "CONTENU DE LA SECTION [%.6d] : %s", ind_section, nom_section) ;
		
		DESSINER_LIGNE(COULEUR_CARRE_SC, LONGUEUR_SC) ;
		DESSINER_2BORDURES(COULEUR_CARRE_SC, LONGUEUR_SC) ;
		ECRIRE_TITRE(COULEUR_CARRE_SC, titre, COULEUR_POLICE_SC, LONGUEUR_SC) ;
		DESSINER_2BORDURES(COULEUR_CARRE_SC, LONGUEUR_SC) ;
		DESSINER_LIGNE(COULEUR_CARRE_SC, LONGUEUR_SC) ;
		DESSINER_3COL_SC () ;
		
		for (int i = 0 ; i < ELF->Entetes_Sections[ind_section]->sh_size ;) {
			
			CARRE(COULEUR_CARRE_SC) ; printf("    0x%.8x    ", i) ; CARRE(COULEUR_CARRE_SC) ; printf ("    ") ;
			
			int j = 0 ;
			
			for (; i < ELF->Entetes_Sections[ind_section]->sh_size && j < 8 ; j++, i++)
	
				printf("%.2x  ", *((unsigned char *)ELF->Sections[ind_section] + i));
				
			for (int k = j ; k < 8 ; k++ ) printf("    ") ; 
			
			printf("  ") ; CARRE(COULEUR_CARRE_SC) ; printf("  ") ;
				
			for (; i < ELF->Entetes_Sections[ind_section]->sh_size && j < 16 ; j++, i++)
	
				printf("  %.2x", *((unsigned char *)ELF->Sections[ind_section] + i)) ;
		
			for (int k = (j < 8 ? 8 : j) ; k < 16 ; k++ ) printf("    ") ;
			
			printf ("    ") ; CARRE(COULEUR_CARRE_SC) ; printf("\n") ;
		}
		
		DESSINER_3COL_SC () ;
		DESSINER_LIGNE(COULEUR_CARRE_SC, LONGUEUR_SC) ;
		
	}
    	
    else
    
    	printf("La section %d / %s est vide.\n", ind_section, (nom_section[0] ? nom_section : "(pas de nom)")) ;
    
    	
}

void afficher_contenus_section (donnees_ELF ELF, char *section) {
	
	int ind_section , i = 0 ;
	
	while (section[i] && isdigit( (int)section[i]) ) i++ ;
	
	if (section[i]) ind_section = indice_nom_entete (ELF, section) ;
		
	else ind_section = atoi(section) ;

	if (ind_section < ELF->les) afficher_contenu_section (ELF, ind_section) ;
    
    else printf("La section \"%s\" n'existe pas.\n", section) ;
    		    		
}
