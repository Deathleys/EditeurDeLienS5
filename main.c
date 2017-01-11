#include "main.h"

void liberer_donnees_ELF (donnees_ELF *ELF, char **Donnees_ELF) {
	
	if (*Donnees_ELF) {
		
		free(*Donnees_ELF) ;
		*Donnees_ELF = NULL ;
		
	}
	
	if (*ELF) {
	
		while ((*ELF)->Table_Rel) {

			Section_Rel *tmp = (*ELF)->Table_Rel ;
			(*ELF)->Table_Rel = (*ELF)->Table_Rel->succ ;
			free(tmp) ;
		
		}
		
		while ((*ELF)->Table_Progbits) {

			Section_Progbits *tmp = (*ELF)->Table_Progbits ;
			(*ELF)->Table_Progbits = (*ELF)->Table_Progbits->succ ;
			free(tmp) ;
		
		}

		if ((*ELF)->Entetes_Sections) free((*ELF)->Entetes_Sections) ;
		if ((*ELF)->Sections) free((*ELF)->Sections) ;
		if ((*ELF)->Table_Symboles)  free((*ELF)->Table_Symboles) ;

		free(*ELF) ;
		*ELF = NULL ;

	}
	
}


int main (int argc, char **argv) {

	if (argc >= 3) {

		FILE *f1, *f2 ;
	
		f1 = fopen(argv[1], "r") ;
		
		if (!f1) {
			
			fprintf(stderr, "Le fichier %s n'a pas pu être ouvert en lecture", argv [1]) ;
			exit (1) ;
			
		}
		
		f2 = fopen(argv[2], "r") ;
		
		if (!f2) {
			
			fprintf(stderr, "Le fichier %s n'a pas pu être ouvert en lecture", argv [2]) ;
			exit (2) ;
			
		}
		
		char *Donnees_ELF_fich1 = NULL, *Donnees_ELF_fich2 = NULL ;
		donnees_ELF ELF1 = NULL, ELF2 = NULL ;
		
		lecture_fichier_ELF(&ELF1, &Donnees_ELF_fich1, f1, argv[1]) ;
		
		lecture_fichier_ELF(&ELF2, &Donnees_ELF_fich2, f2, argv[2]) ;
		
		afficher_entete_ELF (ELF1->Entete_ELF) ;

		printf("\n\n") ;
		
		//afficher_entete_ELF (ELF2->Entete_ELF) ;
		
		//printf("\n\n") ;

		afficher_entetes_section (ELF1) ;
		
		printf("\n\n") ;
		
		Section_Progbits * AC = ELF1->Table_Progbits ;
		
		while(AC) {
			
			printf("ind = %d, taille = %d\n", AC->ind, AC->taille) ;
			AC = AC->succ ;
			
		}
		
		if (argc ==4) {

				afficher_contenus_section (ELF1, argv[3]) ;

				printf("\n\n") ;

		}
		
		afficher_entetes_section (ELF2) ;

		printf("\n\n") ;
		
		donnees_ELF ELF3 = initialiser_donnees_ELF() ;
		char * Donnees_ELF_fich3 = NULL ;
		
		/*if (fusionner_progbits(ELF1, ELF2, ELF3)) {
		
			printf("chaine = %s\n", ELF3->Table_Chaines_ES) ;
			
			char indice[10] ;
			
			for (int i = 0 ; i < ELF3->les ; i++) {
			
				sprintf(indice, "%d", i) ;
				afficher_contenus_section (ELF3, indice) ;
				printf("\n\n") ;
				
			}
			
		*/
			
		afficher_table_symboles (ELF1) ;
			
		printf("\n\n") ;
		
		fusion_table_symboles (ELF1, ELF2, ELF3) ;

		
			
		//afficher_sections_reimplantation (ELF) ;
		
		liberer_donnees_ELF(&ELF1, &Donnees_ELF_fich1) ;
		liberer_donnees_ELF(&ELF2, &Donnees_ELF_fich2) ;
		liberer_donnees_ELF(&ELF3, &Donnees_ELF_fich3) ;
		
		fclose(f1) ;
		fclose(f2) ;
		
	}
		
	else
		
		printf ("usage : %s fichier_ELF (indice/nom section)\n", argv[0]) ;
		
	return EXIT_SUCCESS ;
	
}
