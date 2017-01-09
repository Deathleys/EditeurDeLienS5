#include "fusion_progbits_ELF.h"

char* get_nom_section(donnees_ELF ELF, int i) {

	return ELF->Table_Chaines_ES + ELF->Entetes_Sections[i]->sh_name ;
		
}

//fusion des sections progbits de même nom de ELF1 et ELF2 dans ELF3
void concatenation_section_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3){

	for(int i = 0; i < ELF1->les; i++) {
		int decalage = 0;
		//cas des sections progbits à fusionner
		if(ELF1->Entetes_Sections[i]->sh_type == SHT_PROGBITS) {
			for(int j = 0; j < ELF2->les; j++) {
			
				//cas où la secton progbits est présente dans les deux fichiers => concaténer
				if(ELF2->Entetes_Sections[j]->sh_type == SHT_PROGBITS && strcmp(get_nom_section(ELF1, i),get_nom_section(ELF2, j))==0) {
					
					ELF3->Sections[i] = (Elf32_Shdr *) realloc(ELF3->Sections[i], ELF3->Entetes_Sections[i]->sh_size + ELF2->Entetes_Sections[j]->sh_size);
					if (ELF2->Sections[j] == NULL){
						fprintf(stderr, "Erreur d'allocation") ;
						exit(1);	
					}else{
						ELF3->Sections[i + ELF2->Entetes_Sections[j]->sh_size] = ELF2->Sections[j];// ajout du contenu de ELF2 après ELF1
						ELF3->Entetes_Sections[i]->sh_size += ELF2->Entetes_Sections[j]->sh_size; // augmentation de la taille donnée pour cette section
						decalage = ELF2->Entetes_Sections[j]->sh_size;
					}
				}
			}
		}
		
		//shoff: début des en-têtes de section 
		if (ELF3->Entetes_Sections[i]->sh_offset < ELF3->Entete_ELF->e_shoff){
			ELF3->Entete_ELF->e_shoff += decalage;
		}
		
		//phoff: début de l'en-tête du programme
		if (ELF3->Entetes_Sections[i]->sh_offset < ELF3->Entete_ELF->e_phoff){
			ELF3->Entete_ELF->e_phoff += decalage;
		}
		
		//décalage des sections suivante
		for (int k = i+1; k < ELF3->les; k++){
			ELF3->Entetes_Sections[k]->sh_offset += decalage;
		}
	}
}

//Si la section progbits de ELF2 n'est pas dans ELF1, on l'ajoute dans ELF3
void ajout_section_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3){
	for(int i = 0; i < ELF2->les; i++) { //fusion des sections progbits de même nom
		int trouve = 0;
		//cas des sections progbits à fusionner
		if(ELF2->Entetes_Sections[i]->sh_type == SHT_PROGBITS) {
			for(int j = 0; j < ELF1->les; j++) {
			
				//cas où la secton progbits est présente dans les deux fichiers => concaténer
				if(ELF1->Entetes_Sections[j]->sh_type == SHT_PROGBITS && strcmp(get_nom_section(ELF1, i),get_nom_section(ELF2, j))==0) {
					trouve = 1;
				}
			}
			if (trouve == 0){
				//En-tête de section
				ELF3->Entetes_Sections = (Elf32_Shdr **) realloc(ELF3->Entetes_Sections, sizeof(ELF3->Entetes_Sections) + sizeof(Elf32_Shdr *));
				ELF3->Entetes_Sections[ELF3->les] = ELF2->Entetes_Sections[i];
				//Contenu de section
				ELF3->Sections = (void **) realloc(ELF3->Sections, sizeof(ELF3->Sections) + ELF2->Entetes_Sections[i]->sh_size);
				ELF3->Sections[ELF3->les] = ELF2->Sections[i];
				
				//shnum + 1 / les + 1 dans l'en-tête de ELF3
				ELF3->les++;
				ELF3->Entete_ELF->e_shnum++;
			}
		}
	}
	
}

void fusion_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3) { //ELF1 et ELF2 déjà remplis
	concatenation_section_progbits(ELF1, ELF2, ELF3);
	ajout_section_progbits(ELF1, ELF2, ELF3);
}


/*

int main (int argc, char **argv) {

	if (argc >= 2) {

		FILE *f, *f2;
	
		f = fopen(argv[1], "r") ;
		
		if (!f) {
			
			fprintf(stderr, "Le fichier %s n'existe pas", argv [1]) ;
			exit (1) ;
			
		}

		donnees_ELF ELF1 = initialiser_donnees_ELF() ;
		lectureFichier(ELF1, f);
		donnees_ELF ELF3 = initialiser_donnees_ELF() ;
		lectureFichier(ELF3, f);
		fclose(f) ;
		
		
		f2 = fopen(argv[2], "r") ;
		
		if (!f2) {
			
			fprintf(stderr, "Le fichier %s n'existe pas", argv [2]) ;
			exit (1) ;
			
		}
		donnees_ELF ELF2 = initialiser_donnees_ELF() ;
		lectureFichier(ELF2, f2);
		fclose(f2) ;
		
		fusion_progbits(ELF1, ELF2, ELF3);

		afficher_entetes_section(ELF1);
		afficher_entetes_section(ELF2);
		afficher_entetes_section(ELF3);
		
		liberer_donnees_ELF (&ELF1) ;
		liberer_donnees_ELF (&ELF2) ;
		liberer_donnees_ELF (&ELF3) ;
		
		
	
	}
	
	else
		
		printf ("usage : %s fichier_ELF (indice/nom section)\n", argv[0]) ;
		
	return EXIT_SUCCESS ;
	
}
*/
