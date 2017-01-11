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

void initialiser_descripteur(FILE **f, char * nom_fichier, char *mode){
	
	*f = fopen(nom_fichier, mode) ;
		
	if (!f) {
		fprintf(stderr, "Le fichier %s n'a pas pu être ouvert en lecture", nom_fichier) ;
		exit (1) ;		
	}
	else
		fprintf(stderr, "Le fichier %s a pu être ouvert en lecture\n", nom_fichier) ;
}


int main (int argc, char **argv) {

	if (argc >= 3) {

		FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
		char *Donnees_ELF_fich1 = NULL, *Donnees_ELF_fich2 = NULL, *Donnees_ELF_fich3 = NULL ;
		donnees_ELF ELF1 = NULL, ELF2 = NULL, ELF3 = NULL ;
	
		initialiser_descripteur(&f1,argv[1], "r");
		initialiser_descripteur(&f2,argv[2], "r");
		initialiser_descripteur(&f3,argv[1], "r");//on devrait réutiliser f1

		lecture_fichier_ELF(&ELF1, &Donnees_ELF_fich1, f1, argv[1]) ;	
		lecture_fichier_ELF(&ELF2, &Donnees_ELF_fich2, f2, argv[2]) ;
		lecture_fichier_ELF(&ELF3, &Donnees_ELF_fich3, f3, argv[1]) ;

		//afficher_entete_ELF (ELF1->Entete_ELF) ;

		//printf("\n\n") ;
		
		//afficher_entete_ELF (ELF2->Entete_ELF) ;
		
		//printf("\n\n") ;

		//afficher_entetes_section (ELF1) ;
		
		//printf("\n\n") ;
	
		fusion_progbits(ELF1, ELF2, ELF3);

		//tests pour affichage après fusion
		afficher_entetes_section(ELF1);
		afficher_entetes_section(ELF2);
		afficher_entetes_section(ELF3);
		
		char indice_test[10];

		for(int i=0;i<ELF3->les;i++){
			sprintf(indice_test,"%d",i);
			afficher_contenus_section (ELF3, indice_test) ;
		}
		
		
			
		//afficher_table_symboles (ELF1) ;			
		//printf("\n\n") ;
		//fusion_table_symboles (ELF1, ELF2, ELF3) ;	
		//afficher_sections_reimplantation (ELF) ;
		
		liberer_donnees_ELF(&ELF1, &Donnees_ELF_fich1) ;
		liberer_donnees_ELF(&ELF2, &Donnees_ELF_fich2) ;
		liberer_donnees_ELF(&ELF3, &Donnees_ELF_fich3) ;
		
		fclose(f1) ;
		fclose(f2) ;
		fclose(f3) ;
	}
		
	else
		
		printf ("usage : %s fichier_ELF (indice/nom section)\n", argv[0]) ;
		
	return EXIT_SUCCESS ;
	
}
