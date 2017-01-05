#include "afficher_entete_ELF.h"

void afficher_debut_magic_number (Elf32_Ehdr *Entete) {
	
	printf("%x %x %x %x ", Entete->e_ident[EI_MAG0], Entete->e_ident[EI_MAG1], Entete->e_ident[EI_MAG2], Entete->e_ident[EI_MAG3]) ;
		
}

void afficher_magic_number (Elf32_Ehdr *Entete) {
	
	printf("Magic Number : ") ;
	
	afficher_debut_magic_number(Entete) ;
	
	for (int i = EI_MAG3 + 1 ; i < EI_NIDENT ; i++)
		
		printf("%x ", Entete->e_ident[i]) ; 
		
}

void afficher_classe_fichier (Elf32_Ehdr *Entete) {
	
	printf("Classe du fichier : ") ;
	
	switch (Entete->e_ident[EI_CLASS]) {
	
		case 1 : printf("32-bits") ; break ;
		case 2 : printf("64-bits") ; break ;
		default : printf("Indéterminée") ;
		
	}
	
}

void afficher_convention_encodage (Elf32_Ehdr *Entete) {
	
	printf("Convention de l'encodage : ") ;
	
	switch (Entete->e_ident[EI_DATA]) {
	
		case 1 : printf("LITTLE ENDIAN") ; break ;
		case 2 : printf("BIG ENDIAN") ; break ;
		default : printf("Indéterminée") ;
		
	}
	
}

void afficher_version_fichier (Elf32_Ehdr *Entete) {
	
	printf("Version du fichier : %s", Entete->e_ident[EI_VERSION] == Entete->e_version ? "Version courante" : "Indéterminée") ;
	
}


void afficher_type_objet (Elf32_Ehdr *Entete) {
	
	printf("Type du fichier objet : ") ;
	
	switch (Entete->e_type) {
	
		case ET_NONE : printf("Indéterminé") ; break ;
		case ET_REL  : printf("Translatable") ; break ;
		case ET_EXEC : printf("Executable") ; break ;
		case ET_DYN  : printf("Dynamique") ; break ;
		case ET_CORE  : printf("\"Core\"") ; break ;
		default : printf("Spécifique au Processeur") ;
		
	}
	
}

void afficher_architecture (Elf32_Ehdr *Entete) {
	
	printf("Architecture requise : ") ;
	
	switch (Entete->e_machine) {
	
		case EM_NONE : printf("Aucune") ; break ;
		case EM_M32  : printf("AT&T WE 32100") ; break ;
		case EM_SPARC : printf("SPARC") ; break ;
		case EM_386 : printf("Intel 80386") ; break ;
		case EM_68K : printf("Motorola 68000") ; break ;
		case EM_88K : printf("Motorola 88000") ; break ;
		case EM_860 : printf("Intel 80860") ; break ;
		case EM_MIPS : printf("MIPS RS3000") ; break ;
		case EM_ARM : printf("ARM") ; break ;
		default : printf("Non répertoriée") ;
		
	}
	
}

void afficher_version_fichier2 (Elf32_Ehdr *Entete) {
	
	printf("Version du fichier2 : %s", Entete->e_version ? "Version courante" : "Indéterminée") ;
	
}

void afficher_adresse_entree (Elf32_Ehdr *Entete) {
	
	printf("Adresse de la 1ère entrée : 0x%x", Entete->e_entry) ;
	
}

void afficher_offset_entete_programme (Elf32_Ehdr *Entete) {
	
	printf("Offset de l'en-tête du programme : %d", Entete->e_phoff) ;
	
}

void afficher_offset_entete_sections (Elf32_Ehdr *Entete) {
	
	printf("Offset des en-têtes de section : %d", Entete->e_shoff) ;
	
}

void afficher_fanions (Elf32_Ehdr *Entete) {
	
	printf("Fanions associés : 0x%x", Entete->e_flags) ;
	
}

void afficher_taille_entete (Elf32_Ehdr *Entete) {
	
	printf("Taille de l'en-tête du fichier ELF : %d octet(s)", Entete->e_ehsize) ;
	
}

void afficher_taille_entrees (Elf32_Ehdr *Entete) {
	
	printf("Taille des entrées de l'en-tête du programme : %d octet(s)", Entete->e_phentsize) ;
	
}

void afficher_nombre_entrees (Elf32_Ehdr *Entete) {
	
	printf("Nombre d'entrées de l'en-tête du programme : %d", Entete->e_phnum) ;
	
}

void afficher_taille_sections (Elf32_Ehdr *Entete) {
	
	printf("Taille d'une en-tête de section : %d octet(s)", Entete->e_shentsize) ;
	
}

void afficher_nombre_sections (Elf32_Ehdr *Entete) {
	
	printf("Nombre de sections : %d", Entete->e_shnum) ;
	
}

void afficher_taille_partie_section (Elf32_Ehdr *Entete) {
	
	printf("Taille de la partie section : %d octet(s)", Entete->e_shentsize * Entete->e_shnum) ;
	
}

void afficher_indice_entete_table_chaines (Elf32_Ehdr *Entete) {
	
	switch (Entete->e_shstrndx) {
		
		case SHN_UNDEF : printf("Table des chaines de caractères indéfinie") ; break ;
		default : printf("Indice de l'en-tête de section de la tables des chaines de caractères : %d", Entete->e_shstrndx) ;
		
	}
	
}

void afficher_entete (Elf32_Ehdr *Entete) {
	
	afficher_magic_number (Entete) ;
	printf("\n") ;
	afficher_classe_fichier (Entete) ;
	printf("\n") ;
	afficher_convention_encodage (Entete) ;
	printf("\n") ;
	afficher_version_fichier (Entete) ;
	printf("\n") ;
	afficher_type_objet (Entete) ;
	printf("\n") ;
	afficher_architecture (Entete) ;
	printf("\n") ;
	afficher_fanions (Entete) ;
	printf("\n") ;
	afficher_taille_entete (Entete) ;
	printf("\n") ;
	afficher_adresse_entree (Entete) ;
	printf("\n") ;
	afficher_offset_entete_programme (Entete) ;
	printf("\n") ;
	afficher_offset_entete_sections (Entete) ;
	printf("\n") ;
	afficher_taille_entrees (Entete) ;
	printf("\n") ;
	afficher_nombre_entrees (Entete) ;
	printf("\n") ;
	afficher_taille_sections (Entete) ;
	printf("\n") ;
	afficher_nombre_sections (Entete) ;
	printf("\n") ;
	afficher_taille_partie_section (Entete) ;
	printf("\n") ;
	afficher_indice_entete_table_chaines (Entete) ;
	
}
