#include "main.h"


int main (int argc, char **argv) {

	if (argc >= 2) {

		FILE *f ;
	
		f = fopen(argv[1], "r") ;
		
		if (!f) {
			
			fprintf(stderr, "Le fichier %s n'existe pas", argv [1]) ;
			exit (1) ;
			
		}
		
		char *Donnees_ELF = NULL ;
		donnees_ELF ELF = NULL ;
		
		lecture_fichier_ELF(&ELF, &Donnees_ELF, f, argv[1]) ;
		
		afficher_entete_ELF (ELF->Entete_ELF) ;

		printf("\n\n") ;

		afficher_entetes_section (ELF) ;

		printf("\n\n") ;

		if (argc == 3) {

				afficher_contenus_section (ELF, argv[2]) ;

				printf("\n\n") ;

		}

		afficher_table_symboles (ELF) ;
			
		printf("\n\n") ;
			
		afficher_sections_reimplantation (ELF) ;
		
		if (Donnees_ELF) {
		
			free(Donnees_ELF) ;
			Donnees_ELF = NULL ;
		
		}
	
		if (ELF) {
	
			while (ELF->Table_Rel) {
	
				Section_Rel *tmp = ELF->Table_Rel ;
				ELF->Table_Rel = ELF->Table_Rel->succ ;
				free(tmp) ;
			
			}
	
			if (ELF->Entetes_Sections) free(ELF->Entetes_Sections) ;
			if (ELF->Sections) free(ELF->Sections) ;
			if (ELF->Table_Symboles)  free(ELF->Table_Symboles) ;
	
			free(ELF) ; ELF = NULL ;
	
		}
	
		fclose(f) ;
		
	}
		
	else
		
		printf ("usage : %s fichier_ELF (indice/nom section)\n", argv[0]) ;
		
	return EXIT_SUCCESS ;
	
}
