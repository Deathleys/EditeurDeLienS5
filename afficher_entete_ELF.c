#include "afficher_entete_ELF.h"

static char ch[256] ;
static int l ;

void afficher_ligne (void (*aff)(Elf32_Ehdr *), Elf32_Ehdr *Entete) {
	
	CARRE(COULEUR_CARRE_ELF) ;
	aff(Entete) ;
	DESSINER_2BORDURES(COULEUR_CARRE_ELF,LONGUEUR_ELF) ;
	
}

void ecrire_ligne (int l) {
	
	int nb_esp = LONGUEUR_ELF - l - 4,  esp = nb_esp / 2 ;
		
	for (int i = 0 ; i < esp ; i++) printf(" ") ;
	printf(ch) ;
	for (int i = 0 ; i < (nb_esp & 1 ? esp + 1 : esp) ; i++) printf(" ") ;
	
	CARRE(COULEUR_CARRE_ELF) ; printf("\n") ;
	
}

void afficher_nombre_magique (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Nombre Magique : ") ;
	
	for (int i = EI_MAG0 ; i < EI_NIDENT ; i++)
		
		sprintf(ch + strlen(ch), "%.2x ", Entete->e_ident[i]) ;
		
	ecrire_ligne (strlen(ch)) ;
	
}

void afficher_classe (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "Classe : ") ;
	
	switch (Entete->e_ident[EI_CLASS]) {
	
		case ELFCLASS32 : sprintf(ch + strlen(ch), "ELF32") ; l = 0 ; break ;
		case ELFCLASS64 : sprintf(ch + strlen(ch), "ELF64") ; l = 0 ; break ;
		default : sprintf(ch + strlen(ch), "indéfinie") ; l = -1 ;
		
	}
	
	ecrire_ligne (l += strlen(ch)) ;
	
}

void afficher_encodage (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "Données : ") ;
	
	switch (Entete->e_ident[EI_DATA]) {
	
		case ELFDATA2LSB : sprintf(ch + strlen(ch), "complément à 2, système à octets de poids faible d'abord (little endian)") ; l = -4 ; break ;
		case ELFDATA2MSB : sprintf(ch + strlen(ch), "complément à 2, système à octets de poids fort d'abord (big endian)") ; l = -4 ; break ;
		default          : sprintf(ch + strlen(ch), "indéfini") ; l = -1 ;
		
	}
	
	ecrire_ligne (l += strlen(ch) - 1) ;
	
}

void afficher_version (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "Version : ") ;
	
	switch (Entete->e_ident[EI_VERSION]) {
	
		case EV_CURRENT : sprintf(ch + strlen(ch), "1 (courante)") ; l = 0 ; break ;
		default         : sprintf(ch + strlen(ch), "indéfinie") ; l = -21 ;
		
	}
	
	ecrire_ligne (l += strlen(ch)) ;
	
}

void afficher_OSABI (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "OS/ABI : ") ;
	
	l = 0 ;
	
	switch (Entete->e_ident[EI_OSABI]) {
		case  ELFOSABI_SYSV		  : sprintf(ch + strlen(ch), "UNIX - System V") ; break ;
		case  ELFOSABI_HPUX		  : sprintf(ch + strlen(ch), "HP - UX") ;  break ;
		case  ELFOSABI_NETBSD	  : sprintf(ch + strlen(ch), "NetBSD") ;  break ;
		case  ELFOSABI_LINUX	  : sprintf(ch + strlen(ch), "GNU - Linux") ;  break ;
		case  ELFOSABI_SOLARIS	  : sprintf(ch + strlen(ch), "Sun - Solaris") ;  break ;
		case  ELFOSABI_AIX		  : sprintf(ch + strlen(ch), "IBM - AIX") ;  break ;
		case  ELFOSABI_IRIX		  : sprintf(ch + strlen(ch), "SGI - Irix") ; break ;
		case  ELFOSABI_FREEBSD	  : sprintf(ch + strlen(ch), "FreeBSD") ; break ;
		case  ELFOSABI_TRU64	  : sprintf(ch + strlen(ch), "UNIX - Compaq TRU64 ") ; break ;
		case  ELFOSABI_MODESTO	  : sprintf(ch + strlen(ch), "Novell - Modesto") ; break ;
		case  ELFOSABI_OPENBSD	  : sprintf(ch + strlen(ch), "OpenBSD") ; break ;
		case  ELFOSABI_ARM_AEABI  : sprintf(ch + strlen(ch), "ARM - EABI") ; break ;
		case  ELFOSABI_ARM		  : sprintf(ch + strlen(ch), "ARM") ; break ;
		case  ELFOSABI_STANDALONE : sprintf(ch + strlen(ch), "Standalone - application embarquée") ;  l = -1 ; break ;
		default                   : sprintf(ch  + strlen(ch), "indéfini") ;  l = -1 ;
		
	}
	
	ecrire_ligne (l += strlen(ch)) ;
	
}

void afficher_versionABI (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "Version ABI : ") ;
	
	sprintf(ch  + strlen(ch), "0x%x", Entete->e_ident[EI_ABIVERSION]) ;
		
	ecrire_ligne (strlen(ch)) ;
	
}


void afficher_type (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "Type : ") ;
	
	switch (Entete->e_type) {
	
		case ET_NONE                : sprintf(ch + strlen(ch), "indéterminé") ; l = -2 ; break ;
		case ET_REL                 : sprintf(ch + strlen(ch), "REL (Fichier de relocalisation)") ; l = 0 ; break ;
		case ET_EXEC                : sprintf(ch + strlen(ch), "EXEC (Fichier exécutable") ; l = -1 ; break ;
		case ET_DYN                 : sprintf(ch + strlen(ch), "DYN (Fichier partagé)") ; l = -1 ; break ;
		case ET_CORE                : sprintf(ch + strlen(ch), "CORE (Fichier généré par le processeur)") ; l = -3 ; break ;
		case ET_LOOS : case ET_HIOS : sprintf(ch + strlen(ch), "spécifique au système d'exploitation") ; l = -2 ; break ;
		default                     : sprintf(ch + strlen(ch), "spécifique au processeur") ; l = -1 ;
	}
	
	ecrire_ligne (l += strlen(ch)) ;
	
}

void afficher_machine (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "Machine : ") ;
	
	l = 0 ;
	
	switch (Entete->e_machine) {
	
		case EM_NONE        : sprintf(ch + strlen(ch),"Aucune") ; break ;
		case EM_M32         : sprintf(ch + strlen(ch),"AT&T WE 32100") ; break ;
		case EM_SPARC       : sprintf(ch + strlen(ch),"Sun SPARC") ; break ;
		case EM_386         : sprintf(ch + strlen(ch),"Intel 80386") ; break ;
		case EM_68K         : sprintf(ch + strlen(ch),"Motorola m68k family") ; break ;
		case EM_88K         : sprintf(ch + strlen(ch),"Motorola m88k family") ; break ;
		case EM_860         : sprintf(ch + strlen(ch),"Intel 80860") ; break ;
		case EM_MIPS        : sprintf(ch + strlen(ch),"MIPS RS3000 big-endian") ; break ;
		case EM_S370        : sprintf(ch + strlen(ch),"IBM System/370") ; break ;
		case EM_MIPS_RS3_LE : sprintf(ch + strlen(ch),"MIPS R3000 little-endian") ; break ;
		case EM_PARISC      : sprintf(ch + strlen(ch),"HPPA") ; break ;
		case EM_VPP500      : sprintf(ch + strlen(ch),"Fujitsu VPP500") ; break ;
		case EM_SPARC32PLUS : sprintf(ch + strlen(ch),"Sun's \"v8plus\"") ; break ;
		case EM_960         : sprintf(ch + strlen(ch),"Intel 80960") ; break ;
		case EM_PPC         : sprintf(ch + strlen(ch),"PowerPC") ; break ;
		case EM_PPC64       : sprintf(ch + strlen(ch),"PowerPC 64-bit") ; break ;
		case EM_S390        : sprintf(ch + strlen(ch),"IBM S390") ; break ;
		case EM_V800        : sprintf(ch + strlen(ch),"NEC V800 series") ; break ;
		case EM_FR20        : sprintf(ch + strlen(ch),"Fujitsu FR20") ; break ;
		case EM_RH32        : sprintf(ch + strlen(ch),"TRW RH-32") ; break ;
		case EM_RCE         : sprintf(ch + strlen(ch),"Motorola RCE") ; break ;
		case EM_ARM         : sprintf(ch + strlen(ch),"ARM") ; break ;
		case EM_FAKE_ALPHA  : sprintf(ch + strlen(ch),"Digital Alpha") ; break ;
		case EM_SH          : sprintf(ch + strlen(ch),"Hitachi SH") ; break ;
		case EM_SPARCV9     : sprintf(ch + strlen(ch),"SPARC v9 64-bit") ; break ;
		case EM_TRICORE     : sprintf(ch + strlen(ch),"Siemens Tricore") ; break ;
		case EM_ARC         : sprintf(ch + strlen(ch),"Argonaut RISC Core") ; break ;
		case EM_H8_300      : sprintf(ch + strlen(ch),"Hitachi H8/300") ; break ;
		case EM_H8_300H     : sprintf(ch + strlen(ch),"Hitachi H8/300H") ; break ;
		case EM_H8S         : sprintf(ch + strlen(ch),"Hitachi H8S") ; break ;
		case EM_H8_500      : sprintf(ch + strlen(ch),"Hitachi H8/500") ; break ;
		case EM_IA_64       : sprintf(ch + strlen(ch),"Intel Merced") ; break ;
		case EM_MIPS_X      : sprintf(ch + strlen(ch),"Stanford MIPS-X") ; break ;
		case EM_COLDFIRE    : sprintf(ch + strlen(ch),"Motorola Coldfire") ; break ;
		case EM_68HC12      : sprintf(ch + strlen(ch),"Motorola M68HC12") ; break ;
		case EM_MMA         : sprintf(ch + strlen(ch),"Fujitsu MMA Multimedia Accelerator") ; break ;
		case EM_PCP         : sprintf(ch + strlen(ch),"Siemens PCP") ; break ;
		case EM_NCPU        : sprintf(ch + strlen(ch),"Sony nCPU embeeded RISC") ; break ;
		case EM_NDR1        : sprintf(ch + strlen(ch),"Denso NDR1 microprocessor") ; break ;
		case EM_STARCORE    : sprintf(ch + strlen(ch),"Motorola Start*Core processor") ; break ;
		case EM_ME16        : sprintf(ch + strlen(ch),"Toyota ME16 processor") ; break ;
		case EM_ST100       : sprintf(ch + strlen(ch),"STMicroelectronic ST100 processor") ; break ;
		case EM_TINYJ       : sprintf(ch + strlen(ch),"Advanced Logic Corp. Tinyj emb.fam") ; break ;
		case EM_X86_64      : sprintf(ch + strlen(ch),"AMD x86-64 architecture") ; break ;
		case EM_PDSP        : sprintf(ch + strlen(ch),"Sony DSP Processor") ; break ;
		case EM_FX66        : sprintf(ch + strlen(ch),"Siemens FX66 microcontroller") ; break ;
		case EM_ST9PLUS     : sprintf(ch + strlen(ch),"STMicroelectronics ST9+ 8/16 mc") ; break ;
		case EM_ST7         : sprintf(ch + strlen(ch),"STmicroelectronics ST7 8 bit mc") ; break ;
		case EM_68HC16      : sprintf(ch + strlen(ch),"Motorola MC68HC16 microcontroller") ; break ;
		case EM_68HC11      : sprintf(ch + strlen(ch),"Motorola MC68HC11 microcontroller") ; break ;
		case EM_68HC08      : sprintf(ch + strlen(ch),"Motorola MC68HC08 microcontroller") ; break ;
		case EM_68HC05      : sprintf(ch + strlen(ch),"Motorola MC68HC05 microcontroller") ; break ;
		case EM_SVX         : sprintf(ch + strlen(ch),"Silicon Graphics SVx") ; break ;
		case EM_ST19        : sprintf(ch + strlen(ch),"STMicroelectronics ST19 8 bit mc") ; break ;
		case EM_VAX         : sprintf(ch + strlen(ch),"Digital VAX") ; break ;
		case EM_CRIS        : sprintf(ch + strlen(ch),"Axis Communications 32-bit embedded processor") ; break ;
		case EM_JAVELIN     : sprintf(ch + strlen(ch),"Infineon Technologies 32-bit embedded processor") ; break ;
		case EM_FIREPATH    : sprintf(ch + strlen(ch),"Element 14 64-bit DSP Processor") ; break ;
		case EM_ZSP         : sprintf(ch + strlen(ch),"LSI Logic 16-bit DSP Processor") ; break ;
		case EM_MMIX        : sprintf(ch + strlen(ch),"Donald Knuth's educational 64-bit processor") ; break ;
		case EM_HUANY       : sprintf(ch + strlen(ch),"Harvard University machine-independent object files") ; break ;
		case EM_PRISM       : sprintf(ch + strlen(ch),"SiTera Prism") ; break ;
		case EM_AVR         : sprintf(ch + strlen(ch),"Atmel AVR 8-bit microcontroller") ; break ;
		case EM_FR30        : sprintf(ch + strlen(ch),"Fujitsu FR30") ; break ;
		case EM_D10V        : sprintf(ch + strlen(ch),"Mitsubishi D10V") ; break ;
		case EM_D30V        : sprintf(ch + strlen(ch),"Mitsubishi D30V") ; break ;
		case EM_V850        : sprintf(ch + strlen(ch),"NEC v850") ; break ;
		case EM_M32R        : sprintf(ch + strlen(ch),"Mitsubishi M32R") ; break ;
		case EM_MN10300     : sprintf(ch + strlen(ch),"Matsushita MN10300") ; break ;
		case EM_MN10200     : sprintf(ch + strlen(ch),"Matsushita MN10200") ; break ;
		case EM_PJ          : sprintf(ch + strlen(ch),"picoJava") ; break ;
		case EM_OPENRISC    : sprintf(ch + strlen(ch),"OpenRISC 32-bit embedded processor") ; break ;
		case EM_ARC_A5      : sprintf(ch + strlen(ch),"ARC Cores Tangent-A5") ; break ;
		case EM_XTENSA      : sprintf(ch + strlen(ch),"Tensilica Xtensa Architecture") ; break ;
		case EM_AARCH64     : sprintf(ch + strlen(ch),"ARM AARCH64") ; break ;
		case EM_TILEPRO     : sprintf(ch + strlen(ch),"Tilera TILEPro") ; break ;
		case EM_MICROBLAZE  : sprintf(ch + strlen(ch),"Xilinx MicroBlaze") ; break ;
		case EM_TILEGX      : sprintf(ch + strlen(ch),"Tilera TILE-Gx") ; break ;
		default             : sprintf(ch + strlen(ch),"Non répertoriée") ; l = -2 ;
		
	}
	
	ecrire_ligne (l += strlen(ch)) ;
	
}

void afficher_point_entree (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "  Adresse du point d'entrée : ") ;
	
	sprintf(ch  + strlen(ch), "0x%x", Entete->e_entry) ;
		
	ecrire_ligne (strlen(ch) - 1) ;
	
}

void afficher_decalage_entetes_programme (Elf32_Ehdr *Entete) {
	
	sprintf(ch, "  Début des en-têtes de programme : ") ;
	
	sprintf(ch  + strlen(ch), "%d (octets dans le fichier)", Entete->e_phoff) ;
	
	ecrire_ligne (strlen(ch) - 2) ;
	
}

void afficher_decalage_entetes_section (Elf32_Ehdr *Entete) {
	
	
	sprintf(ch, "Début des en-têtes de section : ") ;
	
	sprintf(ch  + strlen(ch), "%d (octets dans le fichier)", Entete->e_shoff) ;
	
	ecrire_ligne (strlen(ch) - 2) ;
	
}

void afficher_fanions (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Fanions : ") ;
	
	sprintf(ch  + strlen(ch), "0x%.8x", Entete->e_flags) ;
		
	ecrire_ligne (strlen(ch)) ;

}

void afficher_taille_entete (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Taille de cet en-tête : ") ;
	
	sprintf(ch  + strlen(ch), "%d (octets)", Entete->e_ehsize) ;
	
	ecrire_ligne (strlen(ch) - 1) ;

}

void afficher_taille_section_programme (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Taille d'une section du programme : ") ;
	
	sprintf(ch  + strlen(ch), "%d (octets)", Entete->e_phentsize) ;
	
	ecrire_ligne (strlen(ch)) ;

}

void afficher_nombre_sections_programme (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Nombre de sections du programme : ") ;
	
	sprintf(ch  + strlen(ch), "%d", Entete->e_phnum) ;
	
	ecrire_ligne (strlen(ch)) ;

}

void afficher_taille_entete_section (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Taille des en-têtes de section : ") ;
	
	sprintf(ch  + strlen(ch), "%d (octets)", Entete->e_shentsize) ;
	
	ecrire_ligne (strlen(ch) - 1) ;

}

void afficher_nombre_entetes_section (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Nombre d'en-têtes de section : ") ;
	
	sprintf(ch + strlen(ch), "%d", Entete->e_shnum) ;
	
	ecrire_ligne (strlen(ch) - 1) ;

}

void afficher_taille_partie_section (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Taille de la partie section : ") ;
	
	sprintf(ch + strlen(ch), "%d (octets)", Entete->e_shentsize * Entete->e_shnum) ;
	
	ecrire_ligne (strlen(ch)) ;

}

void afficher_indice_shstrtab (Elf32_Ehdr *Entete) {
		
	sprintf(ch, "Indice de la table des noms des en-têtes de section : ") ;
	
	switch (Entete->e_shstrndx) {
		
		case SHN_UNDEF : sprintf(ch  + strlen(ch), "indéfini") ; l = 2 ; break ;
		default        : sprintf(ch  + strlen(ch), "%d", Entete->e_shstrndx) ; l = 0 ;
		
	}
	
	ecrire_ligne (l += strlen(ch) - 1) ;

}

void afficher_entete_ELF (Elf32_Ehdr *Entete) {
	
	DESSINER_LIGNE(COULEUR_CARRE_ELF,LONGUEUR_ELF) ;
	DESSINER_2BORDURES(COULEUR_CARRE_ELF,LONGUEUR_ELF) ;
	ECRIRE_TITRE(COULEUR_CARRE_ELF, TITRE_ELF, COULEUR_POLICE_ELF, LONGUEUR_ELF) ;
	DESSINER_2BORDURES(COULEUR_CARRE_ELF,LONGUEUR_ELF) ;
	DESSINER_LIGNE(COULEUR_CARRE_ELF,LONGUEUR_ELF) ;
	DESSINER_2BORDURES(COULEUR_CARRE_ELF,LONGUEUR_ELF) ;
	
	afficher_ligne(afficher_nombre_magique, Entete) ;
	afficher_ligne(afficher_classe, Entete) ;
	afficher_ligne(afficher_encodage, Entete) ;
	afficher_ligne(afficher_version, Entete) ;
	afficher_ligne(afficher_OSABI, Entete) ;
	afficher_ligne(afficher_versionABI, Entete) ;
	afficher_ligne(afficher_type, Entete) ;
	afficher_ligne(afficher_machine, Entete) ;
	afficher_ligne(afficher_fanions, Entete) ;
	afficher_ligne(afficher_taille_entete, Entete) ;
	afficher_ligne(afficher_point_entree, Entete) ;
	afficher_ligne(afficher_decalage_entetes_programme, Entete) ;
	afficher_ligne(afficher_decalage_entetes_section, Entete) ;
	afficher_ligne(afficher_taille_section_programme, Entete) ;
	afficher_ligne(afficher_nombre_sections_programme, Entete) ;
	afficher_ligne(afficher_taille_entete_section, Entete) ;
	afficher_ligne(afficher_nombre_entetes_section, Entete) ;
	afficher_ligne(afficher_taille_partie_section, Entete) ;
	afficher_ligne(afficher_indice_shstrtab, Entete) ;
	
	DESSINER_LIGNE(COULEUR_CARRE_ELF, LONGUEUR_ELF) ;
	
}
