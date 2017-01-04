#include "lecture_fichier_ELF.h"

void afficher_type_fichier (Elf32_Ehdr *En_Tete) {
	
	unsigned char type[4] ; int i ;
	
	for (i = EI_MAG1 ; i <= EI_MAG3 ; i	++) type[i-1] = En_Tete->e_ident[i] ;
	type[i] = 0 ;
	
	printf("Type du fichier : %s", type) ;
	
}



Elf32_Ehdr * lire_Entete_ELF (FILE *f) {
	
	Elf32_Ehdr *En_Tete = malloc (sizeof *En_Tete) ;
	
	fread(En_Tete, sizeof (Elf32_Ehdr), 1, f) ;
	
	if ((! is_big_endian () && En_Tete->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && En_Tete->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) {
		
		En_Tete->e_type = reverse_2(En_Tete->e_type);
		En_Tete->e_machine = reverse_2(En_Tete->e_machine);
		En_Tete->e_version = reverse_4(En_Tete->e_version);
	 	En_Tete->e_entry = reverse_4(En_Tete->e_entry);
		En_Tete->e_phoff = reverse_4(En_Tete->e_phoff);
		En_Tete->e_shoff = reverse_4(En_Tete->e_shoff);
		En_Tete->e_flags = reverse_4(En_Tete->e_flags);
		En_Tete->e_ehsize = reverse_2(En_Tete->e_ehsize);
		En_Tete->e_phentsize = reverse_2(En_Tete->e_phentsize);
		En_Tete->e_phnum = reverse_2(En_Tete->e_phnum);
		En_Tete->e_shentsize = reverse_2(En_Tete->e_shentsize);
		En_Tete->e_shnum = reverse_2(En_Tete->e_shnum);
		En_Tete->e_shstrndx = reverse_2(En_Tete->e_shstrndx);
	    
	}
	
	return En_Tete ;
}

Elf32_Phdr * lire_Entete_Programme (Elf32_Ehdr *En_Tete, FILE *f) {

	Elf32_Phdr *En_Tete_Programme = NULL ;

	if (En_Tete->e_phnum) {
		
		En_Tete_Programme = malloc (sizeof *En_Tete_Programme) ;
	
		fread(En_Tete_Programme, sizeof (Elf32_Phdr), 1, f) ;
		
	}
	
	return En_Tete_Programme ;
	
}

void lire_Entetes_Sections (data_ELF Entetes_Sections, FILE *f) {
	
	for (int i = 0 ; i < Entetes_Sections->l ; i++) {
	
		Elf32_Shdr *Entete = malloc (sizeof *Entete) ;
	
		fread(Entete, sizeof (Elf32_Shdr), 1, f) ;
		
		Entetes_Sections->Entete[i] = Entete ;
		
	}
	
}

int est_fichier_ELF (char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr *En_Tete) {

	int i, b = 1 ;
	
	for (i = EI_MAG0 ; i <= EI_MAG3 && b ; i++)
		
		b = Magic_Number_ELF[i] == En_Tete->e_ident[i]  ;
	
	return i == TAILLE_MAGIC_NUMBER ;
	
}

int main (int argc, char **argv) {

	char Magic_Number_ELF[TAILLE_MAGIC_NUMBER] = {0x7f, 'E', 'L', 'F'} ;

	if (argc == 2) {

		FILE *f ;
	
		f = fopen(argv[1], "r") ;
		
		Elf32_Ehdr *En_Tete = lire_Entete_ELF (f) ;
		
		if (est_fichier_ELF(Magic_Number_ELF, En_Tete) && En_Tete->e_ident[EI_CLASS] == CLASSE_32BITS) {
		
			Elf32_Phdr *En_Tete_Programme = lire_Entete_Programme (En_Tete, f) ;
			
			data_ELF Entetes_Sections ;
			
			Entetes_Sections = malloc (sizeof *Entetes_Sections) ;
			
			Entetes_Sections->ind_etstrtab = En_Tete->e_shstrndx ;
			
			Entetes_Sections->l = En_Tete->e_shnum ;
			
			Entetes_Sections->Entete = malloc (sizeof (Elf32_Shdr) * Entetes_Sections->l) ;
			
			lire_Entetes_Sections (Entetes_Sections, f) ;
	
			afficher_entete (En_Tete) ;
			
			printf("\n") ;
			
			afficher_entetes_sections (Entetes_Sections) ;
			
			free(En_Tete) ;
			
			if (En_Tete_Programme) free(En_Tete_Programme) ;
			
			for (int i = 0 ; i < Entetes_Sections->l ; i++) {
		
				free(Entetes_Sections->Entete[i]) ;
		
			}
			
			free (Entetes_Sections->Entete) ;
			free (Entetes_Sections) ;
			
		}
		
		fclose(f) ;
	
	}
	
	return 0 ;
	
}
