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
	
		for (int i = 0 ; i < (*ELF)->les && (*ELF)->Sections[i] ; i++) 
		
			if (i != (*ELF)->ind_etsymtab) free((*ELF)->Sections[i]) ;
			
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

int main (int argc, char **argv) {

	unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER] = {0x7f, 'E', 'L', 'F'} ;

	if (argc >= 2) {

		FILE *f ;
	
		f = fopen(argv[1], "r") ;
		
		if (!f) {
			
			fprintf(stderr, "Le fichier %s n'existe pas", argv [1]) ;
			exit (1) ;
			
		}
		
		donnees_ELF ELF = initialiser_donnees_ELF() ;
		
		if (ELF) {
		
			if (lire_Entete_ELF (ELF, f)) {
				
				//if ((! is_big_endian () && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) {
				
				if (est_fichier_ELF(Magic_Number_ELF, ELF->Entete_ELF) && ELF->Entete_ELF->e_ident[EI_CLASS] == CLASSE_32BITS) {
			
					if (lire_Entete_Programme (ELF, f)) {
			
						ELF->ind_etstrtabes = ELF->Entete_ELF->e_shstrndx ;
			
						ELF->les = ELF->Entete_ELF->e_shnum ;
			
						if (lire_Entetes_Sections (ELF, f)) {
	
							afficher_entete_ELF (ELF->Entete_ELF) ;
			
							printf("\n\n") ;
			
							afficher_entetes_section (ELF) ;
			
							printf("\n\n") ;
			
							if (argc == 3) {
			
								afficher_contenus_section (ELF, argv[2]) ;
				
								printf("\n\n") ;
				
							}
			
							afficher_table_symboles (ELF) ;
						}
						
						else printf("Erreur allocation mémoire : processus avorté.\n") ;
					
					}
					
					else printf("Erreur allocation mémoire : processus avorté.\n") ;
			
				}
				
				else printf("Erreur allocation mémoire : processus avorté.\n") ;
				
			}
			
			else printf("Erreur allocation mémoire : processus avorté.\n") ;
			
		}
		
		else printf("Erreur allocation mémoire : processus avorté.\n") ;
		
		liberer_donnees_ELF (&ELF) ;
		fclose(f) ;
	
	}
	
	else
		
		printf ("usage : %s fichier_ELF (indice/nom section)\n", argv[0]) ;
		
	return EXIT_SUCCESS ;
	
}
