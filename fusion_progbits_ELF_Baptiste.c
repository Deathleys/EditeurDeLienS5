#include "fusion_progbits_ELF.h"

char* get_nom_section(donnees_ELF ELF, int i) {

	return ELF->Table_Chaines_ES + ELF->Entetes_Sections[i]->sh_name ;
		
}

void ajouter_nom_section(donnees_ELF ELF, char* nom_section){
	char* nom = malloc(sizeof(nom_section));
	strcpy(nom, nom_section);
	int taille = ELF->Entetes_Sections[ELF->Entete_ELF->e_shstrndx]->sh_size;
	int longueur_nom = sizeof(nom) + 1;
	int nouvelle_taille = taille + longueur_nom;
	ELF->Table_Chaines_ES = (char *) realloc(ELF->Table_Chaines_ES, nouvelle_taille);
	for (int i = taille; i < nouvelle_taille-1; i++){
		ELF->Table_Chaines_ES[i] = nom[i-taille];
	}
	ELF->Table_Chaines_ES[nouvelle_taille-1] = '\0';
	decalage_sections_suivantes(ELF, longueur_nom, ELF->Entete_ELF->e_shstrndx);
	
	//changement sh_name de la section
	ELF->Entetes_Sections[ELF->les-1]->sh_name = taille;
}

void decalage_sections_suivantes(donnees_ELF ELF, int decalage, int i){
	//shoff: début des en-têtes de section 
	if (ELF->Entetes_Sections[i]->sh_offset < ELF->Entete_ELF->e_shoff){
		ELF->Entete_ELF->e_shoff += decalage;
	}

	//phoff: début de l'en-tête du programme
	if (ELF->Entetes_Sections[i]->sh_offset < ELF->Entete_ELF->e_phoff){
		ELF->Entete_ELF->e_phoff += decalage;
	}

	//décalage des sections suivante
	for (int k = i+1; k < ELF->les; k++){
		ELF->Entetes_Sections[k]->sh_offset += decalage;
	}
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
					if (ELF2->Entetes_Sections[j]->sh_size != 0){
						ELF3->Sections[i] = realloc(ELF3->Sections[i], ELF3->Entetes_Sections[i]->sh_size + ELF2->Entetes_Sections[j]->sh_size);
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
		}
		if (decalage != 0){
			decalage_sections_suivantes(ELF3, decalage, i);
			
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
				if(ELF1->Entetes_Sections[j]->sh_type == SHT_PROGBITS && strcmp(get_nom_section(ELF1, j),get_nom_section(ELF2, i))==0) {
					trouve = 1;
				}
			}
			
			if (trouve == 0){
				
				//En-tête de section
				ELF3->Entetes_Sections = (Elf32_Shdr **) realloc(ELF3->Entetes_Sections, sizeof (Elf32_Shdr) * (ELF3->les + 1));
				Elf32_Shdr *nouvelle_section = malloc(sizeof(Elf32_Shdr));
				
				*nouvelle_section = *(ELF2->Entetes_Sections[i]);
				
				ELF3->Entetes_Sections[ELF3->les] = nouvelle_section;
				
				ELF3->Entetes_Sections[ELF3->les]->sh_offset = ELF3->Entetes_Sections[ELF3->les-1]->sh_offset + ELF3->Entetes_Sections[ELF3->les-1]->sh_size;
				
				//Contenu de section
				/*ELF3->Sections = (void **) realloc(ELF3->Sections, sizeof(ELF3->Sections) + ELF2->Entetes_Sections[i]->sh_size);
				char *nouveau_contenu_section = (char *) malloc(ELF2->Entetes_Sections[i]->sh_size);
				memcpy(nouveau_contenu_section, (ELF2->Sections[i]), ELF2->Entetes_Sections[i]->sh_size);
				ELF3->Sections[ELF3->les-1] = nouveau_contenu_section;*/
				
				
				
				//shnum + 1 / les + 1 dans l'en-tête de ELF3
				ELF3->les = ELF3->les + 1;
				ELF3->Entete_ELF->e_shnum = ELF3->Entete_ELF->e_shnum + 1;
				
				//Contenu de section
				ELF3->Sections = realloc(ELF3->Sections, sizeof *(ELF3->Sections) * (ELF3->les + 1)) ;
				char * nouveau_contenu_section = malloc(ELF2->Entetes_Sections[i]->sh_size);
				memcpy(nouveau_contenu_section, ELF2->Sections[i], ELF2->Entetes_Sections[i]->sh_size);
				ELF3->Sections[ELF3->les-1] = (void *) nouveau_contenu_section;
				
				
				ajouter_nom_section(ELF3, get_nom_section(ELF2, i));
				
				
			}
		}
	}
	
}

/*Section_Progbits * copier_liste_progbits (Section_Progbits *LP) {
	
	alloc = true ;
	Section_Progbits *CLP = LP, *Q = NULL ;
	
	while (CLP && alloc) {
		
		Q->succ = malloc (sizeof *Q) ;
		
		if (Q->succ) {
			
			Q->succ->ind = CLP->ind ;
			Q->succ->taille = CLP->taille ;
			Q->succ->succ = NULL ;
			Q->succ = Q ;
			
		}
		
		else {
			
			while (Q) {
				
				Section_Progbits *tmp = Q ;
				Q = Q->succ ;
				free (tmp) ;
				
			}
			
			alloc = false ;
			
		}
		
		CLP = CLP->succ ;
		
	}
	
	return Q ;
	
}*/
	
bool fusionner_progbits (donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3) {
	
	
	Section_Progbits *C1, *C2, *tmp, *F1, *F2 ; int i = 1 ;
	bool alloc = true ;
	long int taille_shstrtab = 0 ;
	
	ELF3->les++ ;
	ELF3->Entetes_Sections = realloc (ELF3->Entetes_Sections, ELF3->les *  sizeof *(ELF3->Entetes_Sections)) ;
	ELF3->Entetes_Sections[0] = malloc (sizeof **(ELF3->Entetes_Sections)) ;
	ELF3->Entetes_Sections[0]->sh_name = taille_shstrtab ;
	
	ELF3->Table_Chaines_ES = realloc (ELF3->Table_Chaines_ES, taille_shstrtab + strlen(get_nom_section(ELF1, ELF1->Entete_ELF->e_shstrndx)) + 1) ;			
	strcpy (ELF3->Table_Chaines_ES + taille_shstrtab, get_nom_section(ELF1, ELF1->Entete_ELF->e_shstrndx)) ;
	
	printf("chaine = %s\n", ELF3->Table_Chaines_ES) ;
					
	taille_shstrtab += strlen(get_nom_section(ELF1, ELF1->Entete_ELF->e_shstrndx)) + 1 ;
	ELF3->Entetes_Sections[0]->sh_size = taille_shstrtab ;
	
	ELF3->Sections = realloc (ELF3->Sections, ELF3->les * sizeof *(ELF3->Sections)) ;
	ELF3->Sections[0] = (void *) malloc (taille_shstrtab) ;
	
	memcpy (ELF3->Sections[0] , (char *) get_nom_section(ELF1, ELF1->Entete_ELF->e_shstrndx), taille_shstrtab) ;
	
	char indice[10] ;
			
	sprintf(indice, "%d", 0) ;
	afficher_contenus_section (ELF3, indice) ;
	printf("\n\n") ;
	
	F1 = malloc (sizeof *F1) ;
	F2 = malloc (sizeof *F2) ;
	
		if (F1 && F2) {
			
			C1 = F1 ; C1->succ = ELF1->Table_Progbits ;
			
			while (C1->succ && alloc) {
				
				C2 = F2 ; C2->succ = ELF2->Table_Progbits ;
				
				while (C2->succ && strcmp(get_nom_section(ELF1, C1->succ->ind), get_nom_section(ELF2, C2->succ->ind))) { printf( "     1\n") ; C2 = C2->succ ; }
				
				if (!strcmp(get_nom_section(ELF1, C1->succ->ind), get_nom_section(ELF2, C2->succ->ind))) {
				
					
					ELF3->les++ ;
					
					ELF3->Entetes_Sections = realloc (ELF3->Entetes_Sections, ELF3->les *  sizeof *(ELF3->Entetes_Sections)) ;
					ELF3->Entetes_Sections[i] = malloc (sizeof **(ELF3->Entetes_Sections)) ;
					ELF3->Entetes_Sections[i]->sh_name = taille_shstrtab ;
					
					
					printf( "     2\n") ;
					
					memcpy (ELF3->Entetes_Sections[i], ELF1->Entetes_Sections[C1->succ->ind], sizeof **(ELF3->Entetes_Sections)) ;
					
					printf( "     3\n") ;
					
					printf("      size = %d\n", ELF3->Entetes_Sections[i]->sh_size) ;
					
					ELF3->Table_Chaines_ES = realloc (ELF3->Table_Chaines_ES, taille_shstrtab + strlen(get_nom_section(ELF1, C1->succ->ind)) + 1) ;
					
					strcpy (ELF3->Table_Chaines_ES + taille_shstrtab, get_nom_section(ELF1, C1->succ->ind)) ;
					
					taille_shstrtab += strlen(get_nom_section(ELF1, C1->succ->ind)) + 1 ;
					
					ELF3->Sections = realloc (ELF3->Sections, ELF3->les * sizeof *(ELF3->Sections)) ;
					ELF3->Sections[i] = (char *) malloc (C1->succ->taille + C2->succ->taille) ;
					
					memcpy (ELF3->Sections[i] , (char *) ELF1->Sections[C1->succ->ind], C1->succ->taille) ;
					memcpy (ELF3->Sections[i] + C1->succ->taille, (char *) ELF2->Sections[C2->succ->ind], C2->succ->taille) ;
					
					char indice[10] ;
			
					sprintf(indice, "%d", i) ;
					afficher_contenus_section (ELF3, indice) ;
					printf("\n\n") ;
					
					tmp = C1 ;
					C1 = C1->succ ;
					if (tmp) free (tmp) ;
					
					tmp = C2 ;
					C2 = C2->succ ;
					if (tmp) free (tmp) ;
					
					i++ ;
					
				}
					
				else
				
					C1 = C1->succ ;
				
		}
			
	}

	else if (F1) {
			
		free(F1) ; alloc = false ;
			
	}
			
	else
			
		 alloc = false ;
			 
	if (alloc) {
	
		C1->succ = ELF2->Table_Progbits ;
	
		C2 = F1 ;
	
		while (C2->succ) {
		
			ELF3->les++ ;
					
			ELF3->Entetes_Sections = realloc (ELF3->Entetes_Sections, ELF3->les *  sizeof *(ELF3->Entetes_Sections)) ;
			ELF3->Entetes_Sections[i] = malloc (sizeof **(ELF3->Entetes_Sections)) ;
			ELF3->Entetes_Sections[i]->sh_name = taille_shstrtab ;
					
			memcpy (ELF3->Entetes_Sections[i], ELF1->Entetes_Sections[C2->succ->ind], sizeof **(ELF3->Entetes_Sections)) ;
					
			ELF3->Sections = realloc (ELF3->Sections, ELF3->les * sizeof *(ELF3->Sections)) ;
			ELF3->Sections[i] = malloc (C2->succ->taille) ;
		
			if (C2->succ->fich == ELF1) {
				
				ELF3->Table_Chaines_ES = realloc (ELF3->Table_Chaines_ES, taille_shstrtab + strlen(get_nom_section(ELF1, C2->succ->ind)) + 1) ;
				memcpy (ELF3->Sections[i] , ELF1->Sections[C2->succ->ind], C2->succ->taille) ;
				strcpy (ELF3->Table_Chaines_ES + taille_shstrtab, get_nom_section(ELF1, C2->succ->ind)) ;
				taille_shstrtab += strlen(get_nom_section(ELF1, C2->succ->ind)) + 1 ;
				tmp = C2 ;
			
			}
			
			else {
				
				ELF3->Table_Chaines_ES = realloc (ELF3->Table_Chaines_ES, taille_shstrtab + strlen(get_nom_section(ELF2, C2->succ->ind)) + 1) ;
				memcpy (ELF3->Sections[i] , ELF2->Sections[C2->succ->ind], C2->succ->taille) ;
				strcpy (ELF3->Table_Chaines_ES + taille_shstrtab, get_nom_section(ELF2, C2->succ->ind)) ;
				taille_shstrtab += strlen(get_nom_section(ELF2, C2->succ->ind)) + 1 ;
				tmp = C2 ;
			
			}
		
			
			tmp = C2 ;
			C2 = C2->succ ;
			if (tmp) free (tmp) ;
		
		}
	
		free(F1) ; free(F2) ;
		
	
	}
	
	return alloc ;
		
}	
	
/*	for(int i = 0 ; i < ELF1->les && alloc ; i++) {
		
		Cellule_Progbits CP  = {-1, -1, 0} ;
		
		//cas des sections progbits à fusionner
		if(ELF1->Entetes_Sections[i]->sh_type == SHT_PROGBITS) {
		
			CP.indf1 = i ; CP.taille += ELF1->Entetes_Sections[i]->sh_size ;
			
			for(int j = 0 ; j < ELF2->les && !trouve_indf2 ; j++) {
			
				//cas où la secton progbits est présente dans les deux fichiers => concaténer
				if(ELF2->Entetes_Sections[j]->sh_type == SHT_PROGBITS && !strcmp(get_nom_section(ELF1, i), get_nom_section(ELF2, j))) {
				
					CP.indf2 = j ; CP.taille += ELF2->Entetes_Sections[j]->sh_size ;
					trouve_indf2 = true ;
					
				}
				
			}
			
			alloc = ajouter_en_queue (LP, &CP, sizeof CP, Q) ;
			(*nb_sects)++ ;
		
		}
		
	}
	
	return alloc ;
	
}

bool fusion_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3, char ** Contenu_Sections_Fich_Res) { //ELF1 et ELF2 déjà remplis
	
	bool alloc ; liste LP = liste_vide() ; Queue Q ; long int pos_buffer_donnees_fichres = 0, taille_sect_progbits ; int nb_sects = 0, i = 0 ;
	
	alloc = creer_liste_progbits (&LP, &Q, ELF1, ELF2, &nb_sects) ;
	
	ELF3->Sections = malloc (sizeof *(ELF3->Sections) * nb_sects) ;
	ELF3->Entetes_Sections = malloc (sizeof *(ELF3->Entetes_Sections) * nb_sects) ;
	
	printf("nbs = %d\n", nb_sects) ;
	
	if (alloc) {
	
		Cellule AC = LP ;
	
		while (alloc && AC) {
			
			Cellule_Progbits CP = *(Cellule_Progbits *)acceder(AC) ;
	
			if (CP.indf1 != -1 && CP.indf2 != -1)
				
				taille_sect_progbits = ELF1->Entetes_Sections[CP.indf1]->sh_size + ELF1->Entetes_Sections[CP.indf2]->sh_size ;
				
			else if (CP.indf1 != -1)

				taille_sect_progbits = ELF1->Entetes_Sections[CP.indf1]->sh_size ;
				
			else
				
				taille_sect_progbits = ELF2->Entetes_Sections[CP.indf2]->sh_size ;
				
			char * sect_progbits = malloc (taille_sect_progbits) ;
				
			if (sect_progbits) {
			
				if (CP.indf1 != -1) {
					
					memcpy (sect_progbits, ELF1->Sections[CP.indf1], ELF1->Entetes_Sections[CP.indf1]->sh_size) ;
					taille_sect_progbits = ELF1->Entetes_Sections[CP.indf1]->sh_size ;
					
				}
				
				else taille_sect_progbits = 0 ;
				
				if (CP.indf2 != -1)
				
					memcpy (sect_progbits + taille_sect_progbits, ELF2->Sections[CP.indf2], ELF2->Entetes_Sections[CP.indf2]->sh_size) ;
				
				memcpy(*Contenu_Sections_Fich_Res + pos_buffer_donnees_fichres, sect_progbits, taille_sect_progbits) ;
				
			
				ELF3->Sections[i] = (void *) *Contenu_Sections_Fich_Res + pos_buffer_donnees_fichres ;
			
				pos_buffer_donnees_fichres += pos_buffer_donnees_fichres ;
				
				Elf32_Shdr Entete ;
				
				Entete.sh_size = taille_sect_progbits ;
				Entete.sh_offset = pos_buffer_donnees_fichres ;
				
				memcpy(*Contenu_Sections_Fich_Res + pos_buffer_donnees_fichres, &Entete, sizeof Entete) ;
				
				ELF3->Entetes_Sections[i] = (Elf32_Shdr *) *Contenu_Sections_Fich_Res + pos_buffer_donnees_fichres ;
				
				pos_buffer_donnees_fichres += pos_buffer_donnees_fichres ;
				
				i++ ;
				
				avancer(&AC) ;
				
			}
			
			else alloc = false ;
			
		}
		
	}
	
	detruire_liste (&LP) ;
	
	ELF3->les = nb_sects ;
	
	return alloc ;
			
}*/





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
