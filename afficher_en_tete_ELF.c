#include "afficher_en_tete_ELF.h"

void afficher_debut_magic_number (Elf32_Ehdr *En_Tete) {
	
	printf("%x %x %x %x ", En_Tete->e_ident[EI_MAG0], En_Tete->e_ident[EI_MAG1], En_Tete->e_ident[EI_MAG2], En_Tete->e_ident[EI_MAG3]) ;
		
}

void afficher_magic_number (Elf32_Ehdr *En_Tete) {
	
	printf("Magic Number : ") ;
	
	afficher_debut_magic_number(En_Tete) ;
	
	for (int i = EI_MAG3 + 1 ; i < EI_NIDENT ; i++)
		
		printf("%x ", En_Tete->e_ident[i]) ; 
		
}

void afficher_classe_fichier (Elf32_Ehdr *En_Tete) {
	
	printf("Classe du fichier : ") ;
	
	switch (En_Tete->e_ident[EI_CLASS]) {
	
		case 1 : printf("32-bits") ; break ;
		case 2 : printf("64-bits") ; break ;
		default : printf("Indéterminée") ;
		
	}
	
}

void afficher_convention_encodage (Elf32_Ehdr *En_Tete) {
	
	printf("Convention de l'encodage : ") ;
	
	switch (En_Tete->e_ident[EI_DATA]) {
	
		case 1 : printf("LITTLE ENDIAN") ; break ;
		case 2 : printf("BIG ENDIAN") ; break ;
		default : printf("Indéterminée") ;
		
	}
	
}

void afficher_version_fichier (Elf32_Ehdr *En_Tete) {
	
	printf("Version du fichier : %s", En_Tete->e_ident[EI_VERSION] == En_Tete->e_version ? "Version courante" : "Indéterminée") ;
	
}


void afficher_type_objet (Elf32_Ehdr *En_Tete) {
	
	printf("Type du fichier objet : ") ;
	
	switch (En_Tete->e_type) {
	
		case ET_NONE : printf("Indéterminé") ; break ;
		case ET_REL  : printf("Translatable") ; break ;
		case ET_EXEC : printf("Executable") ; break ;
		case ET_DYN  : printf("Dynamique") ; break ;
		case ET_CORE  : printf("\"Core\"") ; break ;
		default : printf("Spécifique au Processeur") ;
		
	}
	
}

void afficher_architecture (Elf32_Ehdr *En_Tete) {
	
	printf("Architecture requise : ") ;
	
	switch (En_Tete->e_machine) {
	
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

void afficher_version_fichier2 (Elf32_Ehdr *En_Tete) {
	
	printf("Version du fichier2 : %s", En_Tete->e_version ? "Version courante" : "Indéterminée") ;
	
}

void afficher_adresse_entree (Elf32_Ehdr *En_Tete) {
	
	printf("Adresse de la 1ère entrée : 0x%x", En_Tete->e_entry) ;
	
}

void afficher_offset_entete_programme (Elf32_Ehdr *En_Tete) {
	
	printf("Offset de l'en-tête du programme : %d", En_Tete->e_phoff) ;
	
}

void afficher_offset_entete_sections (Elf32_Ehdr *En_Tete) {
	
	printf("Offset des en-têtes de section : %d", En_Tete->e_shoff) ;
	
}

void afficher_fanions (Elf32_Ehdr *En_Tete) {
	
	printf("Fanions associés : 0x%x", En_Tete->e_flags) ;
	
}

void afficher_taille_entete (Elf32_Ehdr *En_Tete) {
	
	printf("Taille de l'en-tête du fichier ELF : %d octet(s)", En_Tete->e_ehsize) ;
	
}

void afficher_taille_entrees (Elf32_Ehdr *En_Tete) {
	
	printf("Taille des entrées de l'en-tête du programme : %d octet(s)", En_Tete->e_phentsize) ;
	
}

void afficher_nombre_entrees (Elf32_Ehdr *En_Tete) {
	
	printf("Nombre d'entrées de l'en-tête du programme : %d", En_Tete->e_phnum) ;
	
}

void afficher_taille_sections (Elf32_Ehdr *En_Tete) {
	
	printf("Taille d'une en-tête de section : %d octet(s)", En_Tete->e_shentsize) ;
	
}

void afficher_nombre_sections (Elf32_Ehdr *En_Tete) {
	
	printf("Nombre de sections : %d", En_Tete->e_shnum) ;
	
}

void afficher_taille_partie_section (Elf32_Ehdr *En_Tete) {
	
	printf("Taille de la partie section : %d octet(s)", En_Tete->e_shentsize * En_Tete->e_shnum) ;
	
}

void afficher_indice_entete_table_chaines (Elf32_Ehdr *En_Tete) {
	
	switch (En_Tete->e_shstrndx) {
		
		case SHN_UNDEF : printf("Table des chaines de caractères indéfinie") ; break ;
		default : printf("Indice de l'en-tête de section de la tables des chaines de caractères : %d", En_Tete->e_shstrndx) ;
		
	}
	
}

void afficher_entete (Elf32_Ehdr *En_Tete) {
	
	afficher_magic_number (En_Tete) ;
	printf("\n") ;
	afficher_classe_fichier (En_Tete) ;
	printf("\n") ;
	afficher_convention_encodage (En_Tete) ;
	printf("\n") ;
	afficher_version_fichier (En_Tete) ;
	printf("\n") ;
	afficher_type_objet (En_Tete) ;
	printf("\n") ;
	afficher_architecture (En_Tete) ;
	printf("\n") ;
	afficher_fanions (En_Tete) ;
	printf("\n") ;
	afficher_taille_entete (En_Tete) ;
	printf("\n") ;
	afficher_adresse_entree (En_Tete) ;
	printf("\n") ;
	afficher_offset_entete_programme (En_Tete) ;
	printf("\n") ;
	afficher_offset_entete_sections (En_Tete) ;
	printf("\n") ;
	afficher_taille_entrees (En_Tete) ;
	printf("\n") ;
	afficher_nombre_entrees (En_Tete) ;
	printf("\n") ;
	afficher_taille_sections (En_Tete) ;
	printf("\n") ;
	afficher_nombre_sections (En_Tete) ;
	printf("\n") ;
	afficher_taille_partie_section (En_Tete) ;
	printf("\n") ;
	afficher_indice_entete_table_chaines (En_Tete) ;
	
}
