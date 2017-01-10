#ifndef AFFICHER_TABLES_REIMPLANTATION_ELF_H
#define AFFICHER_TABLES_REIMPLANTATION_ELF_H

#include "type.h"
#include "tableau.h"

#define NB_COL_TR 4
#define COL_SYMTAB 40
#define LONGUEUR_TR (NB_COL_TR * COL + 2)
#define COULEUR_POLICE_TR 33
#define COULEUR_CARRE_TR 45

#define DESSINER_COL_NOM_TR() DESSINER_COL(COULEUR_CARRE_TR, COL_SYMTAB, 1)

#define DESSINER_COL_TR() CARRE(COULEUR_CARRE_TR) ; DESSINER_COL_NOM_TR ()  ;\
						   DESSINER_COL(COULEUR_CARRE_TR, LONGUEUR_TR / NB_COL_TR, NB_COL_TR) ; DESSINER_COL_NOM_TR ()  ; printf("\n")

char *TypeReimplantation[] = 
	{ 
		"R_ARM_NONE",
		"R_ARM_PC24",
		"R_ARM_ABS32",
		"R_ARM_REL32",
		"R_ARM_LDR_PC_G0", 
		"R_ARM_ABS16",
		"R_ARM_ABS12",
		"R_ARM_THM_ABS5",
		"R_ARM_ABS8",
		"R_ARM_SBREL32", 
		"R_ARM_THM_CALL",
		"R_ARM_THM_PC8",
		"R_ARM_BREL_ADJ",
		"R_ARM_TLS_DESC",
		"R_ARM_THM_SWI8", 
		"R_ARM_XPC25",
		"R_ARM_THM_XPC22",
		"R_ARM_TLS_DTPMOD32",
		"R_ARM_TLS_DTPOFF32",
		"R_ARM_TLS_TPOFF32",
		"R_ARM_COPY",
		"R_ARM_GLOB_DAT",
		"R_ARM_JUMP_SLOT",
		"R_ARM_RELATIVE",
		"R_ARM_GOTOFF32", 
		"R_ARM_BASE_PREL",
		"R_ARM_GOT_BREL",
		"R_ARM_PLT32",
		"R_ARM_CALL",
		"R_ARM_JUMP24",
		"R_ARM_THM_JUMP24",
		"R_ARM_BASE_ABS",
		"R_ARM_ALU_PSREL_7_0",
		"R_ARM_ALU_PSREL_15_8",
		"R_ARM_ALU_PSREL_23_15", 
		"R_ARM_LDR_SBREL_11_0_NC",
		"R_ARM_ALU_SBREL_19_12_NC",
		"R_ARM_ALU_SBREL_27_20_CK",
		"R_ARM_TARGET1",
		"R_ARM_SBREL31", 
		"R_ARM_V4BX",
		"R_ARM_TARGET2",
		"R_ARM_PREL31",
		"R_ARM_MOVW_ABS_NC",
		"R_ARM_MOVT_ABS", 
		"R_ARM_MOVW_PREL_NC",
		"R_ARM_MOVT_PREL",
		"R_ARM_THM_MOVW_ABS_NC",
		"R_ARM_THM_MOVT_ABS",
		"R_ARM_THM_MOVW_PREL_NC",
		"R_ARM_THM_MOVT_PREL"
	};

char *type_reimplantation(Elf32_Word r_info) ;

Elf32_Sym *indice_symbole(donnees_ELF ELF, Elf32_Word r_info) ;

Elf32_Word valeur_symbole (Elf32_Sym *symbole) ;

Elf32_Word info_symbole (Elf32_Word r_info) ;

void afficher_nom (char *nom) ;

void afficher_sections_reimplantation (donnees_ELF ELF) ;

#endif
