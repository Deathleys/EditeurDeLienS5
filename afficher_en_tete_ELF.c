#include <stdio.h>
#include <stdlib.h>
#include <byteswap.h>
#include <elf.h>
#define MODE_BIG_ENDIAN 2

Elf32_Ehdr lire_Entete_ELF (FILE *f) {
	
	Elf32_Ehdr En_Tete ;
	
	fread(&En_Tete, sizeof (Elf32_Ehdr), 1, f) ;
	
	if (En_Tete.e_ident[EI_DATA] == MODE_BIG_ENDIAN) {
		
		En_Tete.e_type = __bswap_16(En_Tete.e_type);
		En_Tete.e_machine = __bswap_16(En_Tete.e_machine);
		En_Tete.e_version = __bswap_32(En_Tete.e_version);
	 	En_Tete.e_entry = __bswap_32(En_Tete.e_entry);
		En_Tete.e_phoff = __bswap_32(En_Tete.e_phoff);
		En_Tete.e_shoff = __bswap_32(En_Tete.e_shoff);
		En_Tete.e_flags = __bswap_32(En_Tete.e_flags);
		En_Tete.e_ehsize = __bswap_16(En_Tete.e_ehsize);
		En_Tete.e_phentsize = __bswap_16(En_Tete.e_phentsize);
		En_Tete.e_phnum = __bswap_16(En_Tete.e_phnum);
		En_Tete.e_shentsize = __bswap_16(En_Tete.e_shentsize);
		En_Tete.e_shnum = __bswap_16(En_Tete.e_shnum);
		En_Tete.e_shstrndx = __bswap_16(En_Tete.e_shstrndx);
	    
	}
	
	return En_Tete ;
}

void afficher_magic_number (Elf32_Ehdr En_Tete) {
	
	printf("Magic Number :\n\
EI_MAG0 : 0x%x\n\
EI_MAG1 : 0x%x\n\
EI_MAG2 : 0x%x\n\
EI_MAG3 : 0x%x",\
	En_Tete.e_ident[EI_MAG0], En_Tete.e_ident[EI_MAG1], En_Tete.e_ident[EI_MAG2], En_Tete.e_ident[EI_MAG3]) ;
		
}

void afficher_type_fichier (Elf32_Ehdr En_Tete) {
	
	unsigned char type[4] ; int i ;
	
	for (i = EI_MAG1 ; i <= EI_MAG3 ; i	++) type[i-1] = En_Tete.e_ident[i] ;
	type[i] = 0 ;
	
	printf("Type du fichier : %s", type) ;
	
}

void afficher_classe_fichier (Elf32_Ehdr En_Tete) {
	
	printf("Classe du fichier : ") ;
	
	switch (En_Tete.e_ident[EI_CLASS]) {
	
		case 1 : printf("32-bits") ; break ;
		case 2 : printf("64-bits") ; break ;
		default : printf("Indéterminée") ;
		
	}
	
}

void afficher_convention_encodage (Elf32_Ehdr En_Tete) {
	
	printf("Convention de l'encodage : ") ;
	
	switch (En_Tete.e_ident[EI_DATA]) {
	
		case 1 : printf("LITTLE ENDIAN") ; break ;
		case 2 : printf("BIG ENDIAN") ; break ;
		default : printf("Indéterminée") ;
		
	}
	
}

void afficher_version_fichier (Elf32_Ehdr En_Tete) {
	
	printf("Version du fichier : %s", En_Tete.e_ident[EI_VERSION] ? "Version courante" : "Indéterminée") ;
	
}


void afficher_type_objet (Elf32_Ehdr En_Tete) {
	
	printf("Type du fichier objet : ") ;
	
	switch (En_Tete.e_type) {
	
		case ET_NONE : printf("Indéterminé") ; break ;
		case ET_REL  : printf("Translatable") ; break ;
		case ET_EXEC : printf("Executable") ; break ;
		case ET_DYN  : printf("Dynamique") ; break ;
		case ET_CORE  : printf("\"Core\"") ; break ;
		default : printf("Spécifique au Processeur") ;
		
	}
	
}

void afficher_architecture (Elf32_Ehdr En_Tete) {
	
	printf("Architecture requise : ") ;
	
	switch (En_Tete.e_machine) {
	
		case EM_NONE : printf("Aucune") ; break ;
		case EM_M32  : printf("AT&T WE 32100") ; break ;
		case EM_SPARC : printf("SPARC") ; break ;
		case EM_386 : printf("Intel 80386") ; break ;
		case EM_68K : printf("Motorola 68000") ; break ;
		case EM_88K : printf("Motorola 88000") ; break ;
		case EM_860 : printf("Intel 80860") ; break ;
		case EM_MIPS : printf("MIPS RS3000") ; break ;
		default : printf("Non répertoriée") ;
		
	}
	
}

void afficher_version_fichier2 (Elf32_Ehdr En_Tete) {
	
	printf("Version du fichier2 : %s", En_Tete.e_version ? "Version courante" : "Indéterminée") ;
	
}

void afficher_adresse_entree (Elf32_Ehdr En_Tete) {
	
	printf("Adresse d'entrée : 0x%x", En_Tete.e_entry) ;
	
}

void afficher_offset_entete_programme (Elf32_Ehdr En_Tete) {
	
	printf("Offset de l'en-tête du programme : %d", En_Tete.e_phoff) ;
	
}

void afficher_offset_entete_sections (Elf32_Ehdr En_Tete) {
	
	printf("Offset de l'en-tête des sections : %d", En_Tete.e_shoff) ;
	
}

int main (int argc, char **argv) {

	if (argc == 2) {

		FILE *f ;
	
		f = fopen(argv[1], "r") ;
	
		Elf32_Ehdr En_Tete = lire_Entete_ELF (f) ;
	
		fclose(f) ;
	
		afficher_magic_number (En_Tete) ;
		printf("\n") ;
		afficher_type_fichier (En_Tete) ;
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
		afficher_version_fichier2 (En_Tete) ;
		printf("\n") ;
		afficher_adresse_entree (En_Tete) ;
		printf("\n") ;
		afficher_offset_entete_programme (En_Tete) ;
		printf("\n") ;
		afficher_offset_entete_sections (En_Tete) ;
		printf("\n") ;
	
}
	
	return 0 ;
	
}
