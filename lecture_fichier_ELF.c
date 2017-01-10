#include "lecture_fichier_ELF.h"

char * lire_Donnees_ELF (Elf32_Ehdr Entete, FILE *f, long int *l) {
	
	long int 
	taille_entete_ELF = Entete.e_ehsize,
	taille_entete_programme = Entete.e_phentsize * Entete.e_phnum,
	taille_sections = Entete.e_shoff - taille_entete_programme - taille_entete_ELF,
	taille_entetes_sections = Entete.e_shentsize * Entete.e_shnum,
	taille_fichier = taille_entete_ELF + taille_entete_programme + taille_sections + taille_entetes_sections ;
	
	char * Donnees_ELF = malloc (taille_fichier) ;
	
	*l = taille_fichier ;
	
	return Donnees_ELF ;
	
}

donnees_ELF initialiser_donnees_ELF () {
	
	donnees_ELF ELF = malloc (sizeof *ELF) ;
	
	if (ELF) {
		
		// initialisation des champs :
		
		ELF->Entetes_Sections = NULL ;       // stocke les en-têtes de section
		ELF->Table_Symboles = NULL ;         // stocke les symboles de type Elf32_Sym 
		ELF->Table_Rel = NULL ;              // stocke les entrées de section de type Elf32_Rel
	
		ELF->Table_Chaines_ES = NULL ;       // table des chaines des noms des entêtes de section (.shstrtab)
		ELF->Table_Chaines = NULL ;          // table des chaines des noms de symbole (.strtab)
		ELF->Sections = NULL ;               // stocke le contenu des sections
	
		ELF->les = 0 ;                       // nombre d'en-têtes de section (ou nombre de sections) 
		ELF->lts = 0 ;			             // nombre de symboles
		
	}
	
	return ELF ;

}

bool lire_Entete_ELF (donnees_ELF *ELF, char ** Donnees_ELF, FILE *f, unsigned char * Magic_Number_ELF) {
	
	bool Fichier_ELF = false ; long int l = 0 ;
	Elf32_Ehdr Entete_ELF ;
	fread(&Entete_ELF, sizeof Entete_ELF, 1, f) ;
	
	
	if (est_fichier_ELF (Magic_Number_ELF, Entete_ELF) && Entete_ELF.e_ident[EI_CLASS] == CLASSE_32BITS) {
		
		*Donnees_ELF = lire_Donnees_ELF (Entete_ELF, f, &l) ;
		
		
		if (*Donnees_ELF) {
			
			memcpy(*Donnees_ELF, &Entete_ELF, Entete_ELF.e_ehsize) ;
	
			for (int i = Entete_ELF.e_ehsize ; i < l ; i++) (*Donnees_ELF)[i] = fgetc(f) ;
			
			*ELF = initialiser_donnees_ELF() ;
			
			if (*ELF) (*ELF)->Entete_ELF = (Elf32_Ehdr *) *Donnees_ELF ;
			
		}
		
		Fichier_ELF = true ;
	}
	
	return Fichier_ELF ; 
	
}

void lire_Entete_Programme (donnees_ELF ELF, char * Donnees_ELF) {

	if (ELF->Entete_ELF->e_phnum)
		
		ELF->Entete_Programme = (Elf32_Phdr *)(Donnees_ELF + ELF->Entete_ELF->e_phoff) ;

}

void lire_Section (donnees_ELF ELF, int ind_section, char * Donnees_ELF) {
	
	Elf32_Shdr *Entete_Section = ELF->Entetes_Sections[ind_section] ;
    ELF->Sections[ind_section] = (void *) (Donnees_ELF + Entete_Section->sh_offset) ;
		
}

bool lire_Table_Symboles (donnees_ELF ELF, int ind_table_symboles, char * Donnees_ELF) {
	
	bool alloc = false ;
	Elf32_Shdr *Entete_Table_Symboles = ELF->Entetes_Sections[ind_table_symboles] ;
	ELF->lts = ELF->Entetes_Sections[ind_table_symboles]->sh_size / ELF->Entetes_Sections[ind_table_symboles]->sh_entsize ;
	ELF->Table_Symboles = malloc (sizeof (Elf32_Sym) * ELF->lts) ;
	
	if (ELF->Table_Symboles) {
		
		alloc = true ;
	
		for (int i = 0 ; i < ELF->lts && alloc ; i++) 
		
			ELF->Table_Symboles[i] = (Elf32_Sym *) (Donnees_ELF + Entete_Table_Symboles->sh_offset + i * sizeof (Elf32_Sym)) ;
		
		
		
		ELF->Sections[ind_table_symboles] = (void *) ELF->Table_Symboles ;
	
	}
	
	return alloc ;
}

void lire_Table_Chaines (donnees_ELF ELF, int ind_table, char ** Table, char * Donnees_ELF) {
	
	Elf32_Shdr *Entete_Table_Chaines = ELF->Entetes_Sections[ind_table] ;
  	*Table = (Donnees_ELF + Entete_Table_Chaines->sh_offset) ;
  	ELF->Sections[ind_table] = (void *) *Table ;
  	
}

bool lire_Section_Rel (donnees_ELF ELF, int ind_section_rel, Section_Rel **Table_Rel, char * Donnees_ELF) {
	
	Elf32_Shdr *Entete_Section_Rel = ELF->Entetes_Sections[ind_section_rel] ;
	
	bool alloc = false ;
	Section_Rel *SR = malloc (sizeof *SR) ;
	
	if (SR) {
		
		SR->nbr = Entete_Section_Rel->sh_size / sizeof *(SR->Entrees_Rel) ;
		
		SR->Entrees_Rel = (Elf32_Rel *)(Donnees_ELF + Entete_Section_Rel->sh_offset) ;
				
		SR->ind = ind_section_rel ;
		
		SR->succ = *Table_Rel ;
		
		*Table_Rel = SR ;
			
		alloc = true ;
			
	}
		
	ELF->Sections[ind_section_rel] = (void *) *Table_Rel ;
    
    return alloc ;

}

bool lire_Entetes_Sections (donnees_ELF ELF, char * Donnees_ELF) {
	
	bool alloc = true ;
	
	ELF->Entetes_Sections = malloc (sizeof (Elf32_Shdr) * ELF->les) ;
	ELF->Sections = malloc (sizeof (void *) * ELF->les) ;
	
	if (ELF->Entetes_Sections && ELF->Sections) {
	
		for (int i = 0 ; i < ELF->les && alloc ; i++) {
	
			ELF->Entetes_Sections[i] = (Elf32_Shdr *) (Donnees_ELF + ELF->Entete_ELF->e_shoff + i * sizeof (Elf32_Shdr)) ;
	
			if (i == ELF->Entete_ELF->e_shstrndx)
		
				lire_Table_Chaines (ELF, i, &(ELF->Table_Chaines_ES), Donnees_ELF) ;
	
			else if (ELF->Entetes_Sections[i]->sh_type == SHT_STRTAB)
		
				lire_Table_Chaines (ELF, i, &(ELF->Table_Chaines), Donnees_ELF) ;
	
			else if (ELF->Entetes_Sections[i]->sh_type == SHT_SYMTAB)
		
				alloc = lire_Table_Symboles (ELF, i, Donnees_ELF) ;
	
			else if (ELF->Entetes_Sections[i]->sh_type == SHT_REL)
			
				alloc = lire_Section_Rel (ELF, i, &(ELF->Table_Rel), Donnees_ELF) ;
	
			else 
			
				lire_Section (ELF, i, Donnees_ELF) ;
	
		}
		
	}
	
	return alloc ;
	
}

bool est_fichier_ELF (unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER], Elf32_Ehdr Entete) {

	int i, b = true ;
	
	for (i = EI_MAG0 ; i <= EI_MAG3 && b ; i++)
		
		b = Magic_Number_ELF[i] == Entete.e_ident[i]  ;
	
	return i == TAILLE_MAGIC_NUMBER ;
	
}

void lecture_fichier_ELF (donnees_ELF *ELF, char ** Donnees_ELF, FILE *f, char *nom_fich_ELF) {

	unsigned char Magic_Number_ELF[TAILLE_MAGIC_NUMBER] = {0x7f, 'E', 'L', 'F'} ;
		
	if (lire_Entete_ELF (ELF, Donnees_ELF, f, Magic_Number_ELF)) {
			
		if (*Donnees_ELF && *ELF) {
			
			//if ((! is_big_endian () && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) {
			
			lire_Entete_Programme (*ELF, *Donnees_ELF) ;

			(*ELF)->les = (*ELF)->Entete_ELF->e_shnum ;

			if (!lire_Entetes_Sections (*ELF, *Donnees_ELF)) 
				
				printf("Erreur allocation mémoire : processus avorté.\n") ;
	
		}
		
		else printf("Erreur allocation mémoire : processus avorté.\n") ;
		
	}
	
	else printf("Erreur lecture : %s n'est pas un fichier au format ELF de classe 32 bits\n", nom_fich_ELF) ;

}
