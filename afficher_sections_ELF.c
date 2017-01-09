#include "afficher_sections_ELF.h"

void afficher_type_section (Elf32_Shdr* Entete_Section) {
	
	switch (Entete_Section->sh_type) {
            case SHT_NULL            : printf("     INDEFINI     ");
                break;
            case SHT_PROGBITS        : printf("     PROGBITS     ");
                break;
            case SHT_SYMTAB          : printf("      TABSYM      ");
                break;
            case SHT_STRTAB          : printf("      TABCHN      ");
                break;
            case SHT_RELA            : printf("       RELA       ");
                break;
            case SHT_HASH            : printf("     TAB_HACH     ");
                break;
            case SHT_DYNAMIC         : printf("    DYNAMIQUE     ");
                break;
            case SHT_NOTE            : printf("       NOTE       ");
                break;
            case SHT_NOBITS          : printf("       VIDE       ");
                break;
            case SHT_REL             : printf("       REL        ");
                break;
            case SHT_SHLIB           : printf("    SECT_INDEF    ");
                break;
            case SHT_DYNSYM          : printf("    TAB_SYMDYN    ");
                break;
            case SHT_LOPROC          : printf("     SPECPROC     ");
                break;
            case SHT_HIPROC          : printf("     SPECPROC     ");
                break;
            case SHT_LOUSER          : printf("     RSRV_APP     ");
                break;
            case SHT_HIUSER          : printf("     RSRV_APP     ");
                break;
            case SHT_ARM_EXIDX       : printf("  ARM_SECT_DRLMT  ");
            	break;
            case SHT_ARM_PREEMPTMAP  : printf("  ARM_DET_PREEMP  ");
                break;
            case SHT_ARM_ATTRIBUTES  : printf("  ARM_SECT_ATRBT  ");
                break;
            default                  : printf("      ERREUR      ") ;
            
	}
	
}

void afficher_adresse_section(Elf32_Shdr* Entete_Section) {
        
        if (Entete_Section->sh_addr)            
           
           printf("     0x%.8x     ", Entete_Section->sh_addr) ;
        
        else
           
           printf("    INDEFINIE     ") ;
}

void afficher_decalage_section(Elf32_Shdr* Entete_Section) {
        
        printf("    0x%.8x    ", Entete_Section->sh_offset);

}

void afficher_taille_section(Elf32_Shdr* Entete_Section) {
       
       printf("    0x%.8x    ", Entete_Section->sh_size);
}

void afficher_info_section(Elf32_Shdr* Entete_Section) {   
        
        
        printf("    0x%.8x    ", Entete_Section->sh_info);

}

void afficher_flags_section(Elf32_Shdr* Entete_Section) {
		
	if(Entete_Section->sh_flags == 0) printf("      AUCUNE      ");
	
	else {
		
		printf("       ") ;
		if (((Entete_Section->sh_flags >> 0) & 1) == 1) printf("W") ; else printf("-") ;
        if (((Entete_Section->sh_flags >> 1) & 1) == 1) printf("A") ; else printf("-") ;
        if (((Entete_Section->sh_flags >> 2) & 1) == 1) printf("X") ; else printf("-") ;
        if (Entete_Section->sh_flags == SHF_MASKPROC)   printf("P") ; else printf("-") ;
        printf("       ") ;
   
   }
   
}

void afficher_legende_fanions() {

	printf("\nPermissions: W (écriture), A (allocation), X (exécution), P (spécifique au processeur)\n");

}

void afficher_nom_section(donnees_ELF ELF, int i) {

	char * nom = ELF->Table_Chaines_ES + ELF->Entetes_Sections[i]->sh_name ;
	
	if ((*nom)) {
		
		int l = strlen(nom), nb_esp = COL_NOM_ES - l - 2,  esp = nb_esp / 2 ;
		
		for (int i = 0 ; i < esp ; i++) printf(" ") ;
		printf(nom) ;
		for (int i = 0 ; i < (nb_esp & 1 ? esp + 1 : esp) ; i++) printf(" ") ;
		
	}
		
	else
		
		printf("               INDEFINI               ") ;	
	
}

void afficher_entetes_section (donnees_ELF ELF) {

	DESSINER_LIGNE(COULEUR_CARRE_ES, LONGUEUR_ES + COL_NOM_ES) ;
	DESSINER_2BORDURES(COULEUR_CARRE_ES, LONGUEUR_ES + COL_NOM_ES) ;
	ECRIRE_TITRE(COULEUR_CARRE_ES, TITRE_ES, COULEUR_POLICE_ES, LONGUEUR_ES + COL_NOM_ES) ;
	DESSINER_2BORDURES(COULEUR_CARRE_ES, LONGUEUR_ES + COL_NOM_ES) ;
	
	DESSINER_LIGNE(COULEUR_CARRE_ES,LONGUEUR_ES + COL_NOM_ES) ;
	DESSINER_COL_ES () ;
	CARRE(COULEUR_CARRE_ES) ; printf("                NOM_ES                ") ;
	CARRE(COULEUR_CARRE_ES) ; printf("     [NUMERO]     ") ;
	CARRE(COULEUR_CARRE_ES) ; printf("     ADRESSE      ") ;
	CARRE(COULEUR_CARRE_ES) ; printf("      TAILLE      ") ;
	CARRE(COULEUR_CARRE_ES) ; printf("       TYPE       ") ;
	CARRE(COULEUR_CARRE_ES) ; printf("       INFO       ") ;
	CARRE(COULEUR_CARRE_ES) ; printf("       PERM       ") ;
	CARRE(COULEUR_CARRE_ES) ; printf("     DECALAGE     ") ;
	CARRE(COULEUR_CARRE_ES) ; printf("\n") ;
	DESSINER_COL_ES () ;
	DESSINER_LIGNE(COULEUR_CARRE_ES, LONGUEUR_ES + COL_NOM_ES) ;
	DESSINER_COL_ES () ;
	
    for (int i = 0 ; i < ELF->les ; i++) {
		
		CARRE(COULEUR_CARRE_ES) ;  afficher_nom_section(ELF, i) ;
		CARRE(COULEUR_CARRE_ES) ;  printf("     [%06i]     ", i) ;
		CARRE(COULEUR_CARRE_ES) ;  afficher_adresse_section(ELF->Entetes_Sections[i]) ;
		CARRE(COULEUR_CARRE_ES) ;  afficher_taille_section(ELF->Entetes_Sections[i]) ;
		CARRE(COULEUR_CARRE_ES) ;  afficher_type_section(ELF->Entetes_Sections[i]) ;
		CARRE(COULEUR_CARRE_ES) ;  afficher_info_section(ELF->Entetes_Sections[i]) ; 
		CARRE(COULEUR_CARRE_ES) ;  afficher_flags_section(ELF->Entetes_Sections[i]) ;
		CARRE(COULEUR_CARRE_ES) ;  afficher_decalage_section(ELF->Entetes_Sections[i]) ;
		CARRE(COULEUR_CARRE_ES) ;  printf("\n") ;
		
	}
	
	DESSINER_COL_ES () ;
	DESSINER_LIGNE(COULEUR_CARRE_ES,LONGUEUR_ES + COL_NOM_ES) ;
	
	afficher_legende_fanions() ;
	
}
