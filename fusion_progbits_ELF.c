#include "fusion_progbits_ELF.h"

char* get_nom_section(donnees_ELF ELF, int i) {

	return ELF->Table_Chaines_ES + ELF->Entetes_Sections[i]->sh_name ;
		
}

void ajouter_nom_section(donnees_ELF ELF, char* nom_section){
	char* nom = malloc(sizeof(nom_section));
	strcpy(nom, nom_section);
	int taille = ELF->Entetes_Sections[ELF->ind_etstrtabes]->sh_size;
	int longueur_nom = sizeof(nom) + 1;
	int nouvelle_taille = taille + longueur_nom;
	ELF->Table_Chaines_ES = (char *) realloc(ELF->Table_Chaines_ES, nouvelle_taille);
	for (int i = taille; i < nouvelle_taille-1; i++){
		ELF->Table_Chaines_ES[i] = nom[i-taille];
	}
	ELF->Table_Chaines_ES[nouvelle_taille-1] = '\0';
	decalage_sections_suivantes(ELF, longueur_nom, ELF->ind_etstrtabes);
	
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
						ELF3->Sections[i] = (Elf32_Shdr *) realloc(ELF3->Sections[i], ELF3->Entetes_Sections[i]->sh_size + ELF2->Entetes_Sections[j]->sh_size);
						if (ELF2->Sections[j] == NULL){
							fprintf(stderr, "Erreur d'allocation") ;
							exit(1);	
						}else{
							ELF3->Entetes_Sections[i]->sh_size += ELF2->Entetes_Sections[j]->sh_size; // augmentation de la taille donnée pour cette section
							decalage = ELF2->Entetes_Sections[j]->sh_size;
							
							
							//ELF3->Sections[i + ELF2->Entetes_Sections[j]->sh_size] = ELF2->Sections[j];// ajout du contenu de ELF2 après ELF1
							ELF3->Sections[i] = realloc(ELF3->Sections[i], ELF3->Entetes_Sections[i]->sh_size );
							memcpy(ELF3->Sections[i] + ELF1->Entetes_Sections[i]->sh_size,ELF2->Sections[j],ELF2->Entetes_Sections[j]->sh_size);

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
				ELF3->Sections = (void **) realloc(ELF3->Sections, sizeof(ELF3->Sections) * (ELF3->les + 1));
				ELF3->Sections[ELF3->les] = malloc(ELF3->Entetes_Sections[ELF3->les]->sh_size);
				
				memcpy(ELF3->Sections[ELF3->les], ELF2->Sections[i], ELF3->Entetes_Sections[ELF3->les]->sh_size);
				
				
				//shnum + 1 / les + 1 dans l'en-tête de ELF3
				ELF3->les = ELF3->les + 1;
				ELF3->Entete_ELF->e_shnum = ELF3->Entete_ELF->e_shnum + 1;
								
				ajouter_nom_section(ELF3, get_nom_section(ELF2, i));
				
				
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

	#include "lecture_fichier_ELF.h"


donnees_ELF initialiser_donnees_ELF () {
	
	donnees_ELF ELF = malloc (sizeof *ELF) ;
	
	if (ELF) {
		
		// initialisation des champs :
		
		ELF->Entete_ELF = NULL ;             // stocke l'en-tête du fichier ELF
		ELF->Entete_Programme = NULL ;       // stocke l'en-tête du programme (optionnel)
		ELF->Entetes_Sections = NULL ;       // stocke les en-têtes de section
		ELF->Table_Symboles = NULL ;         // stocke les symboles de type Elf32_Sym 
		ELF->Table_Rel = NULL ;              // stocke les entrées de section de type Elf32_Rel
	
		ELF->Table_Chaines_ES = NULL ;       // table des chaines des noms des entêtes de section (.shstrtab)
		ELF->Table_Chaines = NULL ;          // table des chaines des noms de symbole (.strtab)
		ELF->Sections = NULL ;               // stocke le contenu des sections
	
		ELF->les = 0 ;                       // nombre d'en-têtes de section (ou nombre de sections) 
		ELF->lts = 0 ;			             // nombre de symboles
		ELF->lsr = 0 ; 			             // nombre de sections de relocation
		
	}
	
	return ELF ;

}

bool lire_Entete_ELF (donnees_ELF ELF, FILE *f) {
	
	bool alloc = false ;
	Elf32_Ehdr *Entete_ELF = malloc (sizeof * Entete_ELF) ;
	
	if (Entete_ELF) {
	
		fread(Entete_ELF, sizeof * Entete_ELF, 1, f) ;
		ELF->Entete_ELF = Entete_ELF ;
		alloc =  true ;
		
	}
	
	return alloc ;
}

bool lire_Entete_Programme (donnees_ELF ELF, FILE *f) {
	
	bool alloc = true ;
	Elf32_Phdr *Entete_Programme = NULL ;

	if (ELF->Entete_ELF->e_phnum) {
		
		Entete_Programme = malloc (sizeof *Entete_Programme) ;
		
		if (Entete_Programme) {
			
			fseek(f, ELF->Entete_ELF->e_phoff, SEEK_SET) ;
	
			fread(Entete_Programme, sizeof (Elf32_Phdr), 1, f) ;
			ELF->Entete_Programme = Entete_Programme ;
			
		}
			
		else
			
			alloc = false ;
			
	}
	
	return alloc ;	
}

bool lire_Section (donnees_ELF ELF, int ind_section, FILE *f) {
	
	Elf32_Shdr *Entete_Section = ELF->Entetes_Sections[ind_section] ;
	
	bool alloc = false ;
    unsigned char * Section = malloc (Entete_Section->sh_size) ;
	    
    if (Section) {
    	
    	fseek(f, Entete_Section->sh_offset, SEEK_SET) ;
    
    	for (int i = 0 ; i < Entete_Section->sh_size ; i++)
       
			Section [i] = fgetc(f) ;
		
		ELF->Sections[ind_section] = (void *) Section ;
		alloc = true ;
    
    }
    
    return alloc ;	
}

bool lire_Table_Symboles (donnees_ELF ELF, FILE *f) {
	
	bool alloc = false ;
	
	ELF->Table_Symboles = malloc (sizeof (Elf32_Sym) * ELF->lts) ;
	
	if (ELF->Table_Symboles) {
		
		alloc = true ;
		fseek(f, ELF->Entetes_Sections[ELF->ind_etsymtab]->sh_offset, SEEK_SET) ;
	
		for (int i = 0 ; i < ELF->lts && alloc ; i++) {
		
			Elf32_Sym * Symbole = malloc (sizeof *Symbole) ;
			alloc = Symbole != NULL ;
			
			if (alloc) {
				
				fread(Symbole, sizeof (Elf32_Sym), 1, f) ;
				ELF->Table_Symboles[i] = Symbole ;
				
			}
			
		}	
	
	}
	
	return alloc ;	
}

bool lire_Table_Chaines_ES (donnees_ELF ELF, FILE *f) {
	
	Elf32_Shdr *Entete_Table_Chaines_ES = ELF->Entetes_Sections[ELF->ind_etstrtabes] ;
    
	bool alloc = false ;
	char * Table_Chaines_ES = malloc (Entete_Table_Chaines_ES->sh_size) ;
	
	if (Table_Chaines_ES) {
		
		fseek(f, Entete_Table_Chaines_ES->sh_offset, SEEK_SET) ;
    	
		for (int i = 0 ; i < Entete_Table_Chaines_ES->sh_size ; i++)
			
			Table_Chaines_ES [i] = fgetc(f) ;
    
  		ELF->Table_Chaines_ES = Table_Chaines_ES ;
  		alloc = true ;
  		
  	}
	
	return alloc ;
}

bool lire_Table_Chaines (donnees_ELF ELF, FILE *f) {
	
	Elf32_Shdr *Entete_Table_Chaines = ELF->Entetes_Sections[ELF->ind_etstrtab] ;
	
	bool alloc = false ;
	char * Table_Chaines = malloc (Entete_Table_Chaines->sh_size) ;
	
	if (Table_Chaines) {
	
    	fseek(f, Entete_Table_Chaines->sh_offset, SEEK_SET) ;
		
		for (int i = 0 ; i < Entete_Table_Chaines->sh_size ; i++)
		
			Table_Chaines [i] = fgetc(f) ;
    
  		ELF->Table_Chaines = Table_Chaines ;
  		alloc = true ;
  		
  	}
	
	return alloc ;
}

bool lire_Section_Rel (donnees_ELF ELF, int ind_section_rel, FILE *f) {
	
	Elf32_Shdr *Entete_Section_Rel = ELF->Entetes_Sections[ind_section_rel] ;
	
	bool alloc = false ;
	Cellule_Rel *Cel_Rel = malloc (sizeof *Cel_Rel) ;
	
	if (Cel_Rel) {
	
		Cel_Rel->Section_Rel = malloc (sizeof *(Cel_Rel->Section_Rel)) ;
		
		if (Cel_Rel->Section_Rel) {
		
			fseek(f, Entete_Section_Rel->sh_offset, SEEK_SET) ;
			fread(Cel_Rel->Section_Rel, sizeof *(Cel_Rel->Section_Rel), 1, f) ;
			ELF->Sections[ind_section_rel] = (void *) Cel_Rel ;
			Cel_Rel->succ = ELF->Table_Rel ;
			ELF->Table_Rel = Cel_Rel ;
			alloc = true ;
			
		}
			
		else free(Cel_Rel) ;
    
    }
    
    return alloc ;
}

bool lire_Entetes_Sections (donnees_ELF ELF, FILE *f) {
	
	int i ; long int save_pos ; bool alloc = false ;

	ELF->Entetes_Sections = malloc (sizeof (Elf32_Shdr) * ELF->les) ;
	ELF->Sections = malloc (sizeof (void *) * ELF->les) ;
	
	if (ELF->Entetes_Sections && ELF->Sections) {
		
		alloc = true ;
	
		fseek(f, ELF->Entete_ELF->e_shoff, SEEK_SET) ;
	
		for (i = 0 ; i < ELF->les && alloc ; i++) {
	
			Elf32_Shdr *Entete_Section = malloc (sizeof *Entete_Section) ;
			alloc = Entete_Section != NULL ;
			
			if (alloc) {
				
				fread(Entete_Section, sizeof (Elf32_Shdr), 1, f) ;
				ELF->Entetes_Sections[i] = Entete_Section ;
				
			}
		
			if (i == ELF->ind_etstrtabes) {
			
				save_pos = ftell(f) ;
				alloc = lire_Table_Chaines_ES (ELF, f) ;
				fseek(f, save_pos, SEEK_SET) ;
				ELF->Sections[i] = (void *) ELF->Table_Chaines_ES ;
			
			}
		
			else if (Entete_Section->sh_type == SHT_STRTAB) {
			
				save_pos = ftell(f) ;
				ELF->ind_etstrtab = i ;
				alloc = lire_Table_Chaines (ELF, f) ;
				fseek(f, save_pos, SEEK_SET) ;
				ELF->Sections[i] = (void *) ELF->Table_Chaines ;
			
			
			}
		
			else if (Entete_Section->sh_type == SHT_SYMTAB) {
			
				save_pos = ftell(f) ;
				ELF->ind_etsymtab = i ;
				ELF->lts = ELF->Entetes_Sections[ELF->ind_etsymtab]->sh_size / ELF->Entetes_Sections[ELF->ind_etsymtab]->sh_entsize ;
				alloc = lire_Table_Symboles (ELF, f) ;
				fseek(f, save_pos, SEEK_SET) ;
				ELF->Sections[i] = (void *) ELF->Table_Symboles ;
			
			
			}
		
			else if (Entete_Section->sh_type == SHT_REL) {
			
				save_pos = ftell(f) ;
				ELF->ind_etsymtab = i ;
				ELF->lts = ELF->Entetes_Sections[ELF->ind_etsymtab]->sh_size / ELF->Entetes_Sections[ELF->ind_etsymtab]->sh_entsize ;
				lire_Table_Symboles (ELF, f) ;
				fseek(f, save_pos, SEEK_SET) ;
				ELF->Sections[i] = (void *) ELF->Table_Symboles ;
			
			
			}
		
			else {
			
				save_pos = ftell(f) ;
				alloc = lire_Section (ELF, i, f) ;
				fseek(f, save_pos, SEEK_SET) ;
			
			}
		
		}
		
	}
	
	return alloc ;
	
}

int est_fichier_ELF (unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr *Entete) {

	int i, b = 1 ;
	
	for (i = EI_MAG0 ; i <= EI_MAG3 && b ; i++)
		
		b = Magic_Number_ELF[i] == Entete->e_ident[i]  ;
	
	return i == TAILLE_MAGIC_NUMBER ;
	
}

void liberer_donnees_ELF (donnees_ELF *ELF) {

	if ((*ELF)->Entete_ELF) free ((*ELF)->Entete_ELF) ;
			
	if ((*ELF)->Entete_Programme) free((*ELF)->Entete_Programme) ;
	
	if ((*ELF)->Entetes_Sections) {
			
		for (int i = 0 ; i < (*ELF)->les && (*ELF)->Entetes_Sections[i] ; i++)
			
			free((*ELF)->Entetes_Sections[i]) ;
			
		free ((*ELF)->Entetes_Sections) ;
	
	}
	
	if ((*ELF)->Sections) {
	
		for (int i = 0 ; i < (*ELF)->les && (*ELF)->Sections[i]!=NULL ; i++) {
			if (i != (*ELF)->ind_etsymtab){
			 	free((*ELF)->Sections[i]) ;
			}
			
		}
		free((*ELF)->Sections) ;
		
	}
	
	if ((*ELF)->Table_Symboles) {
	
		for (int i = 0 ; i < (*ELF)->lts && (*ELF)->Table_Symboles[i] ; i++)
		
			free((*ELF)->Table_Symboles[i]) ;
	
		free((*ELF)->Table_Symboles) ;
		
	}
	
	if (ELF) free (*ELF) ;
	
	*ELF = NULL ;
	
}

void lectureFichier(donnees_ELF ELF, FILE* f){

	unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER] = {0x7f, 'E', 'L', 'F'} ;

	if (ELF) {
		
		if (lire_Entete_ELF (ELF, f)) {
		
			//if ((! is_big_endian () && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) {
		
			if (est_fichier_ELF(Magic_Number_ELF, ELF->Entete_ELF) && ELF->Entete_ELF->e_ident[EI_CLASS] == CLASSE_32BITS) {
	
				if (lire_Entete_Programme (ELF, f)) {
	
					ELF->ind_etstrtabes = ELF->Entete_ELF->e_shstrndx ;
	
					ELF->les = ELF->Entete_ELF->e_shnum ;
	
					if (lire_Entetes_Sections (ELF, f)) {
						
					
					}
				
					else ;
			
				}
			
				else ;
	
			}
		
			else ;
		
		}
	
		else ;
	
	}

	else ;
}

int main (int argc, char **argv) {

	if (argc >= 2) {

		FILE *f1, *f2;
	
		f1 = fopen(argv[1], "r") ;
		if (!f1) {
			
			fprintf(stderr, "Le fichier %s n'existe pas", argv [1]) ;
			exit (1) ;
			
		}
		
		donnees_ELF ELF1 = initialiser_donnees_ELF() ;
		lectureFichier(ELF1, f1);
		
		fclose(f1) ;
		
		f1 = fopen(argv[1], "r") ;
		
		donnees_ELF ELF3 = initialiser_donnees_ELF() ;
		lectureFichier(ELF3, f1);
		
		fclose(f1) ;
		
		f2 = fopen(argv[2], "r") ;
		if (!f2) {
			
			fprintf(stderr, "Le fichier %s n'existe pas", argv [2]) ;
			exit (1) ;
			
		}

		donnees_ELF ELF2 = initialiser_donnees_ELF() ;
		lectureFichier(ELF2, f2);

		fclose(f2) ;
		
		fusion_progbits(ELF1, ELF2, ELF3);

		//afficher_entetes_section(ELF1);
		//afficher_entetes_section(ELF2);
		afficher_entetes_section(ELF3);
		
		char indice[10];

		for(int i=0;i<ELF3->les;i++){
			sprintf(indice,"%d",i);
			afficher_contenus_section (ELF3, indice) ;
		}
		
		liberer_donnees_ELF (&ELF1) ;
		liberer_donnees_ELF (&ELF2) ;
		//liberer_donnees_ELF (&ELF3) ;
		
		
	
	}
	
	else
		
		printf ("usage : %s fichier_ELF (indice/nom section)\n", argv[0]) ;
		
	return EXIT_SUCCESS ;
	
}
	
}
*/
