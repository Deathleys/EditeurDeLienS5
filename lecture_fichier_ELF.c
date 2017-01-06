#include "lecture_fichier_ELF.h"


void lire_Entete_ELF (donnees_ELF ELF, FILE *f) {
	
	Elf32_Ehdr *Entete_ELF = malloc (sizeof * Entete_ELF) ;
	
	fread(Entete_ELF, sizeof * Entete_ELF, 1, f) ;
	
	ELF->Entete_ELF = Entete_ELF ;
}

void lire_Entete_Programme (donnees_ELF ELF, FILE *f) {

	Elf32_Phdr *Entete_Programme = NULL ;
	
	fseek(f, ELF->Entete_ELF->e_phoff, SEEK_SET);

	if (ELF->Entete_ELF->e_phnum) {
		
		Entete_Programme = malloc (sizeof *Entete_Programme) ;
	
		fread(Entete_Programme, sizeof (Elf32_Phdr), 1, f) ;
		
	}
	
	ELF->Entete_Programme = Entete_Programme ;
	
}

void lire_Section (donnees_ELF ELF, int ind_section, FILE *f) {
	
	Elf32_Shdr *Entete_Section = ELF->Entetes_Sections[ind_section] ;
    
    fseek(f, Entete_Section->sh_offset, SEEK_SET);
    
    unsigned char * Section = malloc (Entete_Section->sh_size);
    
    for (int i = 0; i < Entete_Section->sh_size; i++) {
       
       Section [i] = fgetc(f);
    
    }
    
  	ELF->Sections[ind_section] = (void *) Section ;
	
}

void lire_Table_Symboles (donnees_ELF ELF, FILE *f) {
	
	ELF->Table_Symboles = malloc (sizeof (Elf32_Sym) * ELF->lts) ;
	
	fseek(f, ELF->Entetes_Sections[ELF->ind_etsymtab]->sh_offset, SEEK_SET);
	
	for (int i = 0 ; i < ELF->lts ; i++) {
		
		Elf32_Sym * Symbole = malloc (sizeof *Symbole) ;
	
		fread(Symbole, sizeof (Elf32_Sym), 1, f) ;
		
		ELF->Table_Symboles[i] = Symbole ;
	
	}
	
}

void lire_Table_Chaines_ES (donnees_ELF ELF, FILE *f) {
	
	Elf32_Shdr *Entete_Table_Chaines_ES = ELF->Entetes_Sections[ELF->ind_etstrtabes] ;
    
    fseek(f, Entete_Table_Chaines_ES->sh_offset, SEEK_SET);
    
    unsigned char * Table_Chaines_ES = malloc (Entete_Table_Chaines_ES->sh_size);
    
    for (int i = 0; i < Entete_Table_Chaines_ES->sh_size; i++) {
       
       Table_Chaines_ES [i] = fgetc(f);
    
    }
    
  	ELF->Table_Chaines_ES = Table_Chaines_ES ;
	
}

void lire_Table_Chaines (donnees_ELF ELF, FILE *f) {
	
	Elf32_Shdr *Entete_Table_Chaines = ELF->Entetes_Sections[ELF->ind_etstrtab] ;
    
    fseek(f, Entete_Table_Chaines->sh_offset, SEEK_SET) ;
    
    unsigned char * Table_Chaines = malloc (Entete_Table_Chaines->sh_size) ;
    
    for (int i = 0 ; i < Entete_Table_Chaines->sh_size; i++) {
       
       Table_Chaines [i] = fgetc(f);
    
    }
    
   ELF->Table_Chaines = Table_Chaines ;
	
}

void lire_Entetes_Sections (donnees_ELF ELF, FILE *f) {

	int i ; long int save_pos ;

	ELF->Entetes_Sections = malloc (sizeof (Elf32_Shdr) * ELF->les) ;
	ELF->Sections = malloc (sizeof (void *) * ELF->les) ;
	
	fseek(f, ELF->Entete_ELF->e_shoff, SEEK_SET) ;
	
	for (i = 0 ; i < ELF->les ; i++) {
	
		Elf32_Shdr *Entete_Section = malloc (sizeof *Entete_Section) ;
	
		fread(Entete_Section, sizeof (Elf32_Shdr), 1, f) ;
		
		ELF->Entetes_Sections[i] = Entete_Section ;
		
		
		if (i == ELF->ind_etstrtabes) {
			
			save_pos = ftell(f) ;
			lire_Table_Chaines_ES (ELF, f) ;
			fseek(f, save_pos, SEEK_SET) ;
			ELF->Sections[i] = (void *) ELF->Table_Chaines_ES ;
			
		}
		
		else if (Entete_Section->sh_type == SHT_STRTAB) {
			
			save_pos = ftell(f) ;
			ELF->ind_etstrtab = i ;
			lire_Table_Chaines (ELF, f) ;
			fseek(f, save_pos, SEEK_SET) ;
			ELF->Sections[i] = (void *) ELF->Table_Chaines ;
			
			
		}
		
		else if (Entete_Section->sh_type == SHT_SYMTAB) {
			
			save_pos = ftell(f) ;
			ELF->ind_etsymtab = i ;
			ELF->lts = ELF->Entetes_Sections[ELF->ind_etsymtab]->sh_size / ELF->Entetes_Sections[ELF->ind_etsymtab]->sh_entsize ;
			lire_Table_Symboles (ELF, f) ;
			fseek(f, save_pos, SEEK_SET) ;
			ELF->Sections[i] = (void *) ELF->Table_Symboles ;
			
			
		}
		
		else {
			
			save_pos = ftell(f) ;
			lire_Section (ELF, i, f) ;
			fseek(f, save_pos, SEEK_SET) ;
			
		}
	}
	
}



/*void afficher_noms_symboles (donnees_ELF ELF) {

	for (int i = 0 ; i < ELF->lts ; i++) {
	
		printf("%s\n" , ELF->Table_Chaines + ELF->Table_Symboles[i]->st_name) ;
	
	}
	
}*/


int est_fichier_ELF (unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr *Entete) {

	int i, b = 1 ;
	
	for (i = EI_MAG0 ; i <= EI_MAG3 && b ; i++)
		
		b = Magic_Number_ELF[i] == Entete->e_ident[i]  ;
	
	return i == TAILLE_MAGIC_NUMBER ;
	
}

void liberer_struct_ELF (donnees_ELF *ELF) {

	free ((*ELF)->Entete_ELF) ;
			
	if ((*ELF)->Entete_Programme) free((*ELF)->Entete_Programme) ;
			
	for (int i = 0 ; i < (*ELF)->les ; i++) {
		
		free((*ELF)->Entetes_Sections[i]) ;
		if (i != (*ELF)->ind_etsymtab) free((*ELF)->Sections[i]) ;
		
	}
			
	free ((*ELF)->Entetes_Sections) ;
	free((*ELF)->Sections) ;
	
	for (int i = 0 ; i < (*ELF)->lts ; i++) {
		
		free((*ELF)->Table_Symboles[i]) ;
		
	}
	
	free((*ELF)->Table_Symboles) ;
	
	free (*ELF) ;
	
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
		
		donnees_ELF ELF = malloc (sizeof *ELF) ;
		
		lire_Entete_ELF (ELF, f) ;
		
		
		//if ((! is_big_endian () && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) {
			
			
		
		if (est_fichier_ELF(Magic_Number_ELF, ELF->Entete_ELF) && ELF->Entete_ELF->e_ident[EI_CLASS] == CLASSE_32BITS) {
		
			lire_Entete_Programme (ELF, f) ;
			
			ELF->ind_etstrtabes = ELF->Entete_ELF->e_shstrndx ;
			
			ELF->les = ELF->Entete_ELF->e_shnum ;
			
			lire_Entetes_Sections (ELF, f) ;
			
			//afficher_noms_symboles (ELF) ;
	
			afficher_entete (ELF->Entete_ELF) ;
			
			printf("\n\n") ;
			
			afficher_entetes_sections (ELF) ;
			
			if (argc == 3) {
			
				afficher_contenu_sections (ELF, argv[2]) ;
				
			}
			
			liberer_struct_ELF (&ELF) ;
			
		}
		
		fclose(f) ;
	
	}
	
	return 0 ;
	
}
