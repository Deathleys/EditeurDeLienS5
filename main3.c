#include <getopt.h>
#include "main.h"

void usage(char *name) {
	fprintf(stderr, "Usage:\n"
		"%s [ --help ] [ --fichier1 nom_de_fichier ] [ --fichier2 nom_de_fichier ] \n\n"
		"Simule le comportement de la commande ReadElf et implémente une sous partie d'éditeur de liens.\n",name );
		
}

donnees_ELF initialiser_donnees_ELF () {
	
	donnees_ELF ELF = malloc (sizeof *ELF) ;
	
	if (ELF) {
		
		// initialisation des champs :
		
		ELF->Entetes_Sections = NULL ;       // stocke les en-têtes de section
		ELF->Table_Symboles = NULL ;         // stocke les symboles de type Elf32_Sym 
		ELF->Table_Rel = NULL ;              // stocke les entrées de section de type Elf32_Rel
		ELF->Table_Progbits = NULL ;              // stocke les entrées de section de type Elf32_Rel
	
		ELF->Table_Chaines_ES = NULL ;       // table des chaines des noms des entêtes de section (.shstrtab)
		ELF->Table_Chaines = NULL ;          // table des chaines des noms de symbole (.strtab)
		ELF->Sections = NULL ;               // stocke le contenu des sections
	
		ELF->les = 0 ;                       // nombre d'en-têtes de section (ou nombre de sections) 
		ELF->lts = 0 ;			             // nombre de symboles
		
	}
	
	return ELF ;

}


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
}


int main (int argc, char **argv) {

	int opt;
	char *nom_fichier1 = NULL , *nom_fichier2 = NULL , *nom_section = NULL;
	FILE *f1 = NULL, *f2 = NULL, *f3 = NULL;
	char *Donnees_ELF_fich1 = NULL, *Donnees_ELF_fich2 = NULL, *Donnees_ELF_fich3 = NULL ;
	donnees_ELF ELF1 = NULL, ELF2 = NULL, ELF3 = NULL ;

	struct option longopts[] = {
		{ "help", no_argument, NULL, 'H' },
		//{ "debug", required_argument, NULL, 'd' },
		{ "fichier1", required_argument, NULL, '1' },
		{ "fichier2", required_argument, NULL, '2' },
		{ "entete", no_argument, NULL, 'h' },
		{ "sections", no_argument, NULL, 'S' },		
		{ "sections_contenu", required_argument, NULL, 'x' },
		{ "toutes_contenus_sections", no_argument, NULL, 'X' },
		{ "symbole", no_argument, NULL, 's' },	
		{ "tables_reimplantation", no_argument, NULL, 'r' },	
		{ "fusion", no_argument, NULL, 'f' },	
		{ NULL, 0, NULL, 0 }
	};

	while ((opt = getopt_long(argc, argv, "Hd:1:2:hSx:sr", longopts, NULL)) != -1) {
		switch(opt) {
			case 'd':
				add_debug_to(optarg);
				break;
			case '1':
				nom_fichier1 = optarg;
				initialiser_descripteur(&f1,nom_fichier1, "r");
				lecture_fichier_ELF(&ELF1, &Donnees_ELF_fich1, f1, argv[1]) ;	
				break;
			case '2':
				nom_fichier2 = optarg;
				initialiser_descripteur(&f2,nom_fichier2, "r");
				lecture_fichier_ELF(&ELF2, &Donnees_ELF_fich2, f2, argv[2]) ;
				break;

			case 'h':
				if(ELF1!=NULL){
					printf("Affichage de l'en-tête (Similaire à readelf -h):\n");
					afficher_entete_ELF (ELF1->Entete_ELF) ;
					printf("\n\n") ;
				}
				//libération
				exit(0);
			case 'S':
				if(ELF1!=NULL){
					printf("Affichage de la table des sections (Similaire à readelf -S):\n");
					afficher_entetes_section (ELF1) ;
					printf("\n\n") ;
				}
				//libération
				exit(0);
			case 'x':
				if(ELF1!=NULL){
					nom_section = optarg;
					printf("Affichage du contenu de la section %s (Similaire à readelf -x nom_num_Section):\n",nom_section);
					afficher_contenus_section(ELF1, nom_section);
					printf("\n\n") ;
				}
				//libération
				exit(0);
			case 'X':
				if(ELF1!=NULL){
					printf("Affichage des contenus de toutes les sections de %s (Similaire à readelf -x nom_num_Section):\n",nom_fichier1);			
					char indice_test[ELF1->les];
					for(int i=0;i<ELF1->les;i++){
						sprintf(indice_test,"%d",i);
						afficher_contenus_section (ELF1, indice_test) ;
					}
					printf("\n\n") ;
				}
				//libération
				exit(0);
			case 's':
				if(ELF1!=NULL){
					printf("Affichage de la table des symboles (Similaire à readelf -s):\n");
					afficher_table_symboles (ELF1) ;
					printf("\n\n") ;
				}
				//libération
				exit(0);
			case 'r':
				if(ELF1!=NULL){
					printf("Affichage de la table de réimplantation (Similaire à readelf -r):\n");
					afficher_sections_reimplantation (ELF1) ;
					printf("\n\n") ;
				}
				//libération
				exit(0);
			case 'f':
				if(ELF1!=NULL && ELF2!=NULL){		
					initialiser_descripteur(&f3,argv[1], "r");
					lecture_fichier_ELF(&ELF3, &Donnees_ELF_fich3, f3, argv[1]);
					printf("Fusion des fichiers\n");
					fusion_progbits(ELF1, ELF2, ELF3);
					printf("\n\n") ;
				}
				//libération
				exit(0);

			case 'H':
				usage(argv[0]);
				exit(0);

			default:
				fprintf(stderr, "Option %c non reconnue.\n", opt);
				usage(argv[0]);
				exit(1);
			}
	}

	liberer_donnees_ELF(&ELF1, &Donnees_ELF_fich1) ;
	liberer_donnees_ELF(&ELF2, &Donnees_ELF_fich2) ;
	liberer_donnees_ELF(&ELF3, &Donnees_ELF_fich3) ;
	
	fclose(f1) ;
	fclose(f2) ;
	fclose(f3) ;	
		
	return EXIT_SUCCESS ;
	
}
