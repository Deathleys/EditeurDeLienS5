#include "afficher_tables_reimplantation_ELF.h"

char *type_reimplantation(Elf32_Word r_info){
	
	return (char *)(TypeReimplantation[ELF32_R_TYPE(r_info)]) ;
	
}

Elf32_Sym *indice_symbole(donnees_ELF ELF, Elf32_Word r_info){
	
	return ELF->Table_Symboles[ELF32_R_SYM(r_info)] ;
}

Elf32_Word valeur_symbole (Elf32_Sym *symbole) {
	
	return symbole->st_value ;

}

Elf32_Word info_symbole (Elf32_Word r_info) {
	
	return ELF32_R_INFO(ELF32_R_SYM(r_info), ELF32_R_TYPE(r_info)) ;

}


void afficher_nom (char *nom) {
	
	if ((*nom)) {
		
		int l = strlen(nom), nb_esp = COL_SYMTAB - l - 2,  esp = nb_esp / 2 ;
		
		for (int i = 0 ; i < esp ; i++) printf(" ") ;
		printf("%s", nom) ;
		for (int i = 0 ; i < (nb_esp & 1 ? esp + 1 : esp) ; i++) printf(" ") ;
		
	}
		
	else
		
		printf("               INDEFINI               ") ;
	
}

void afficher_sections_reimplantation (donnees_ELF ELF) {

	Section_Rel *SR = ELF->Table_Rel ;
	
	while (SR) {
	
		char *nom_section = ELF->Table_Chaines_ES + ELF->Entetes_Sections[SR->ind]->sh_name ;
	
		printf("Affichage de la table de réimplantation %d / %s :\n\n", SR->ind, (nom_section[0] ? nom_section : "(pas de nom)")) ;
		
		char titre [100] ;
		
		sprintf(titre , "CONTENU DE LA SECTION [%.6i] : %s", SR->ind, nom_section) ;
	
		DESSINER_LIGNE(COULEUR_CARRE_TR, LONGUEUR_TR + 2 * COL_SYMTAB) ;
		DESSINER_2BORDURES(COULEUR_CARRE_TR, LONGUEUR_TR + 2 * COL_SYMTAB) ;
		ECRIRE_TITRE(COULEUR_CARRE_TR, titre, COULEUR_POLICE_TR, LONGUEUR_TR + 2 * COL_SYMTAB) ;
		DESSINER_2BORDURES(COULEUR_CARRE_TR, LONGUEUR_TR + 2 * COL_SYMTAB) ;
	
		DESSINER_LIGNE(COULEUR_CARRE_TR,LONGUEUR_TR + 2 * COL_SYMTAB) ;
		DESSINER_COL_TR() ;
	
		CARRE(COULEUR_CARRE_TR) ; printf("                NOMSYM                ") ;
		CARRE(COULEUR_CARRE_TR) ; printf("     [NUMERO]     ") ;
		CARRE(COULEUR_CARRE_TR) ; printf("      VALEUR      ") ;
		CARRE(COULEUR_CARRE_TR) ; printf("     DECALAGE     ") ;
		CARRE(COULEUR_CARRE_TR) ; printf("       INFO       ") ;
		CARRE(COULEUR_CARRE_TR) ; printf("                 TYPE                 ") ;
		CARRE(COULEUR_CARRE_TR) ; printf("\n") ;
	
		DESSINER_COL_TR() ; 
		DESSINER_LIGNE(COULEUR_CARRE_TR, LONGUEUR_TR + 2 * COL_SYMTAB) ;
		DESSINER_COL_TR() ;
		
		for (int j = 0 ; j < SR->nbr ; j++) {
		
			Elf32_Sym *Symbole = indice_symbole (ELF, SR->Entrees_Rel[j].r_info) ;
			Elf32_Word Valeur = valeur_symbole (Symbole) ;
			char * Nom_Symbole = *(ELF->Table_Chaines + Symbole->st_name) ? ELF->Table_Chaines + Symbole->st_name : ELF->Table_Chaines_ES + ELF->Entetes_Sections[Symbole->st_shndx]->sh_name ;
			
			CARRE(COULEUR_CARRE_TR) ;  afficher_nom (Nom_Symbole) ;
			CARRE(COULEUR_CARRE_TR) ;  printf("     [%06i]     ", j) ;
			CARRE(COULEUR_CARRE_TR) ;  printf("    0x%.8x    ", Valeur) ;
			CARRE(COULEUR_CARRE_TR) ;  printf("    0x%.8x    ", SR->Entrees_Rel[j].r_offset) ;
			CARRE(COULEUR_CARRE_TR) ;  printf("    0x%.8x    ", info_symbole(SR->Entrees_Rel[j].r_info)) ;
			CARRE(COULEUR_CARRE_TR) ;  afficher_nom (type_reimplantation(SR->Entrees_Rel[j].r_info)) ;
			CARRE(COULEUR_CARRE_TR) ;  printf("\n") ;
		
        
        }
        
        DESSINER_COL_TR() ;
		DESSINER_LIGNE(COULEUR_CARRE_TR, LONGUEUR_TR + 2 * COL_SYMTAB) ;
		printf("\n\n") ;
        
        SR = SR->succ ;
    }
}
