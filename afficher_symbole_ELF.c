#include "afficher_symbole_ELF.h"

void afficher_valeur_symbole (Elf32_Sym *Symbole) {
	
	printf("    0x%.8x    ", Symbole->st_value) ;
	
}

void afficher_taille_symbole (Elf32_Sym *Symbole) {
	
	printf("    0x%.8x    ", Symbole->st_size) ;
	
}

void afficher_type_symbole(Elf32_Sym *Symbole) {
	
	switch (ELF32_ST_TYPE(Symbole->st_info)) {
	
		case STT_NOTYPE   : printf("     INDEFINI     ") ; break ;
		case STT_OBJECT   : printf("      OBJET       ") ; break ;
		case STT_FUNC     : printf("     FONCTION     ") ; break ;
		case STT_SECTION  : printf("     SECTION      ") ; break ;
		case STT_FILE     : printf("     FICHIER      ") ; break ;
		case STT_LOPROC   : printf("     SPECPROC     ") ; break ;
		case STT_HIPROC   : printf("     SPECPROC     ") ; break ;
		default           : printf("      ERREUR      ") ;
		
	}
	
}

void afficher_portee_symbole (Elf32_Sym *Symbole) {
	
	switch (ELF32_ST_BIND(Symbole->st_info)) {
	
		case STB_LOCAL   : printf("      LOCALE      ") ; break ;
		case STB_GLOBAL  : printf("      GLOBALE     ") ; break ;
		case STB_WEAK    : printf("      FAIBLE      ") ; break ;
		case STB_LOPROC  : printf("     SPECPROC     ") ; break ;
		case STB_HIPROC  : printf("     SPECPROC     ") ; break ;
		default          : printf("      ERREUR      ") ;
		
	}
	
}

void afficher_visibilite_symbole(Elf32_Sym *Symbole) {
	
	switch (Symbole->st_other) {
	
		case STV_DEFAULT    : printf("     INDEFINI     ") ; break ;
		case STV_HIDDEN     : printf("       NVAM       ") ; break ;
		case STV_PROTECTED  : printf("       PONE       ") ; break ;
		default             : printf("      ERREUR      ") ;
		
	}
	
}

void afficher_ndx_symbole(Elf32_Sym *Symbole) {

	switch (Symbole->st_shndx) {
		
		case 0     : printf("       UND        ") ; break ;
		case 65521 : printf("       ABS        ") ; break ;
		case 65522 : printf("       COM        ") ; break ;
		default    : printf("     [%06i]     ", Symbole->st_shndx) ;	
	
	}
}

void afficher_nom_symbole(donnees_ELF ELF, int i) {
	
	char * nom = ELF->Table_Chaines + ELF->Table_Symboles[i]->st_name ;
	
	if ((*nom)) {
		
		int l = strlen(nom), nb_esp = COL_SYMTAB - l - 2,  esp = nb_esp / 2 ;
		
		for (int i = 0 ; i < esp ; i++) printf(" ") ;
		printf(nom) ;
		for (int i = 0 ; i < (nb_esp & 1 ? esp + 1 : esp) ; i++) printf(" ") ;
		
	}
		
	else
		
		printf("               INDEFINI               ") ;
	
}

void afficher_legende_table_symboles() {

	printf("\nVisibilité : NVAM (Non Valable dans d'Autres Modules), PONE (Préemptible Ou Non Exporté)");

}

void afficher_table_symboles (donnees_ELF ELF) {

	DESSINER_LIGNE(COULEUR_CARRE_TS, LONGUEUR_TS + COL_SYMTAB) ;
	DESSINER_2BORDURES(COULEUR_CARRE_TS, LONGUEUR_TS + COL_SYMTAB) ;
	ECRIRE_TITRE(COULEUR_CARRE_TS, TITRE_TS, COULEUR_POLICE_TS, LONGUEUR_TS + COL_SYMTAB) ;
	DESSINER_2BORDURES(COULEUR_CARRE_TS, LONGUEUR_TS + COL_SYMTAB) ;
	
	DESSINER_LIGNE(COULEUR_CARRE_TS,LONGUEUR_TS + COL_SYMTAB) ;
	DESSINER_COL_TS() ;
	
	CARRE(COULEUR_CARRE_TS) ; printf("                NOMSYM                ") ;
	CARRE(COULEUR_CARRE_TS) ; printf("     [NUMERO]     ") ;
	CARRE(COULEUR_CARRE_TS) ; printf("      VALEUR      ") ;
	CARRE(COULEUR_CARRE_TS) ; printf("      TAILLE      ") ;
	CARRE(COULEUR_CARRE_TS) ; printf("       TYPE       ") ;
	CARRE(COULEUR_CARRE_TS) ; printf("       LIEN       ") ;
	CARRE(COULEUR_CARRE_TS) ; printf("    VISIBILITE    ") ;
	CARRE(COULEUR_CARRE_TS) ; printf("      INDICE      ") ;
	CARRE(COULEUR_CARRE_TS) ; printf("\n") ;
	
	DESSINER_COL_TS() ;
	DESSINER_LIGNE(COULEUR_CARRE_TS, LONGUEUR_TS + COL_SYMTAB) ;
	DESSINER_COL_TS() ;
	
    for (int i = 0 ; i < ELF->lts ; i++) {
		
		CARRE(COULEUR_CARRE_TS) ;  afficher_nom_symbole(ELF, i) ;
		CARRE(COULEUR_CARRE_TS) ;  printf("     [%06i]     ", i) ;
		CARRE(COULEUR_CARRE_TS) ;  afficher_valeur_symbole (ELF->Table_Symboles[i]) ;
		CARRE(COULEUR_CARRE_TS) ;  afficher_taille_symbole (ELF->Table_Symboles[i]) ;
		CARRE(COULEUR_CARRE_TS) ;  afficher_type_symbole (ELF->Table_Symboles[i]) ;
		CARRE(COULEUR_CARRE_TS) ;  afficher_portee_symbole (ELF->Table_Symboles[i]) ;
		CARRE(COULEUR_CARRE_TS) ;  afficher_visibilite_symbole(ELF->Table_Symboles[i]) ;
		CARRE(COULEUR_CARRE_TS) ;  afficher_ndx_symbole(ELF->Table_Symboles[i]) ;
		CARRE(COULEUR_CARRE_TS) ;  printf("\n") ;
		
	}
	
	DESSINER_COL_TS() ;
	DESSINER_LIGNE(COULEUR_CARRE_TS, LONGUEUR_TS + COL_SYMTAB) ;
	
	afficher_legende_table_symboles() ;
	
}
