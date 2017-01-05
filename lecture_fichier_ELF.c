#include "lecture_fichier_ELF.h"

void afficher_type_fichier (Elf32_Ehdr *Entete) {
	
	unsigned char type[4] ; int i ;
	
	for (i = EI_MAG1 ; i <= EI_MAG3 ; i	++) type[i-1] = Entete->e_ident[i] ;
	type[i] = 0 ;
	
	printf("Type du fichier : %s", type) ;
	
}



Elf32_Ehdr * lire_Entete_ELF (FILE *f) {
	
	Elf32_Ehdr *Entete = malloc (sizeof *Entete) ;
	
	fread(Entete, sizeof (Elf32_Ehdr), 1, f) ;
	
	if ((! is_big_endian () && Entete->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && Entete->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) {
		
		Entete->e_type = reverse_2(Entete->e_type);
		Entete->e_machine = reverse_2(Entete->e_machine);
		Entete->e_version = reverse_4(Entete->e_version);
	 	Entete->e_entry = reverse_4(Entete->e_entry);
		Entete->e_phoff = reverse_4(Entete->e_phoff);
		Entete->e_shoff = reverse_4(Entete->e_shoff);
		Entete->e_flags = reverse_4(Entete->e_flags);
		Entete->e_ehsize = reverse_2(Entete->e_ehsize);
		Entete->e_phentsize = reverse_2(Entete->e_phentsize);
		Entete->e_phnum = reverse_2(Entete->e_phnum);
		Entete->e_shentsize = reverse_2(Entete->e_shentsize);
		Entete->e_shnum = reverse_2(Entete->e_shnum);
		Entete->e_shstrndx = reverse_2(Entete->e_shstrndx);
	    
	}
	
	return Entete ;
}

Elf32_Phdr * lire_Entete_Programme (Elf32_Ehdr *Entete_ELF, FILE *f) {

	Elf32_Phdr *Entete_Programme = NULL ;

	if (Entete_ELF->e_phnum) {
		
		Entete_Programme = malloc (sizeof *Entete_Programme) ;
	
		fread(Entete_Programme, sizeof (Elf32_Phdr), 1, f) ;
		
	}
	
	return Entete_Programme ;
	
}

void lire_Text (donnees_ELF ELF, FILE *f) {

	ELF->ltext = ELF->Entete_ELF->e_shoff - ELF->Entete_ELF->e_ehsize - ELF->Entete_ELF->e_phnum * ELF->Entete_ELF->e_phentsize ;

	unsigned char * Text = malloc (ELF->ltext) ;
	
	for (int i = 0 ; i < ELF->ltext ; i++) {
	
		Text[i] = fgetc(f) ;
		
	}
	
	ELF->text = Text ;
	
}

void afficher_Text (donnees_ELF ELF) {

	int i = 0 ;
	
	while (i < ELF->ltext) {
	
		printf("%.8x  ", i) ;
	
		for (int j = 0 ; i < ELF->ltext && j < 8 ; j++) {
		
			printf("%.2x ", ELF->text[i]) ;
			i++ ;
			
		}
			
		printf(" ") ;
		
		for (int j = 0 ; i < ELF->ltext && j < 8 ; j++) {
		
			printf("%.2x ", ELF->text[i]) ;
			i++ ;
			
		}
		
		printf("\n") ;
		
	}
		
}

void lire_Entetes_Sections (donnees_ELF ELF, FILE *f) {
	
	for (int i = 0 ; i < ELF->les ; i++) {
	
		Elf32_Shdr *Entete_Section = malloc (sizeof *Entete_Section) ;
	
		fread(Entete_Section, sizeof (Elf32_Shdr), 1, f) ;
		
		ELF->Entetes_Sections[i] = Entete_Section ;
		
	}
	
}

int est_fichier_ELF (char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr *Entete) {

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
		
	}
			
	free ((*ELF)->Entetes_Sections) ;
	free ((*ELF)->text) ;
	free (*ELF) ;
	*ELF = NULL ;
	
}

int main (int argc, char **argv) {

	char Magic_Number_ELF[TAILLE_MAGIC_NUMBER] = {0x7f, 'E', 'L', 'F'} ;

	if (argc == 2) {

		FILE *f ;
	
		f = fopen(argv[1], "r") ;
		
		donnees_ELF ELF = malloc (sizeof *ELF) ;
		
		ELF->Entete_ELF = lire_Entete_ELF (f) ;
		
		if (est_fichier_ELF(Magic_Number_ELF, ELF->Entete_ELF) && ELF->Entete_ELF->e_ident[EI_CLASS] == CLASSE_32BITS) {
		
			ELF->Entete_Programme = lire_Entete_Programme (ELF->Entete_ELF, f) ;
			
			ELF->ind_etstrtab = ELF->Entete_ELF->e_shstrndx ;
			
			ELF->les = ELF->Entete_ELF->e_shnum ;
			
			lire_Text (ELF,f) ;
			
			ELF->Entetes_Sections = malloc (sizeof (Elf32_Shdr) * ELF->les) ;
			
			lire_Entetes_Sections (ELF, f) ;
	
			afficher_entete (ELF->Entete_ELF) ;
			
			printf("\n\n") ;
			
			afficher_Text(ELF) ;
			
			printf("\n") ;
			
			afficher_entetes_sections (ELF) ;
			
			liberer_struct_ELF (&ELF) ;
			
		}
		
		fclose(f) ;
	
	}
	
	return 0 ;
	
}
