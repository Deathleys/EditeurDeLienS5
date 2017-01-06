#include "afficher_tables_relocation_ELF.h"


//TODO modifier afficher
/*
Elf32_Rel lireRelocation(FILE* f, int numSec, int index, donnees_ELF ELF) {
    Elf32_Rel r;
    fseek(f, ELF->Entetes_Sections[numSec]->sh_offset + index * sizeof (Elf32_Rel), SEEK_SET);
    fread(&r, sizeof (Elf32_Rel), 1, f);
    if ((! is_big_endian () && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && ELF->Entete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) {
        r.r_info = __bswap_32(r.r_info);
        r.r_offset = __bswap_32(r.r_offset);
    }
    return r;
}

Elf32_Rel* lireRelocationsDeSection(FILE* f, int numSec, donnees_ELF ELF) {    
    int nbRel =(ELF->Entetes_Sections[numSec]->sh_size / sizeof (Elf32_Rel)); //calcul nb de relocations dans cette section
    Elf32_Rel* rs = malloc(nbRel * sizeof (Elf32_Rel)); //aloue un tableau de relocations de la bonne taille
    for (int i = 0; i < nbRel; i++) { //pour chaque relocation, l'insère dans le tableau
        rs[i] = lireRelocation(f, numSec, i, ELF);
        //printf("%08x\t%08x\t%08x\t%08x\n", rs[i].r_offset, rs[i].r_info, ELF32_R_TYPE(rs[i].r_info),ELF32_R_SYM(rs[i].r_info));
    }
    return rs;
}
*/
char *getTypeRelocation(Elf32_Word r_info){
	char *typeRelocation[] = 
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
		"R_ARM_ALU_PCREL_7_0",
		"R_ARM_ALU_PCREL_15_8",
		"R_ARM_ALU_PCREL_23_15", 
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
	return (char *)(typeRelocation[ELF32_R_TYPE(r_info)]);
}

void afficher_tables_relocation(FILE* f, donnees_ELF ELF) {

    for (int k = 0; k < ELF->lsr; k++) {
        int nbRel = ELF->Entetes_Sections[ELF->indiceRelocations[k]]->sh_size / sizeof (Elf32_Rel);
        printf("Section de relocalisation '");
        int i = ELF->Entetes_Sections[ELF->indiceRelocations[k]]->sh_name;
        while (ELF->Table_Chaines_ES[i] != '\0') {
            printf("%c", ELF->Table_Chaines_ES[i]);
            i++;
        }
        printf("' à l'adresse de décalage 0x%x contient %d entrees:\n", ELF->Entetes_Sections[ELF->indiceRelocations[k]]->sh_offset, nbRel);
        printf("Décalage\tInfo\t\tType\t\tSym_idx\n");
        for (int j = 0; j < nbRel; j++) {
            printf("%08x\t%08x\t%s\t%08x\n", ELF->Table_Relocation[k][j].r_offset, ELF->Table_Relocation[k][j].r_info, getTypeRelocation(ELF->Table_Relocation[k][j].r_info),ELF32_R_SYM(ELF->Table_Relocation[k][j].r_info));
        }
        printf("\n");
    }
}
/*
Elf32_Rel** lire_Table_Relocation(donnees_ELF ELF, FILE* f) { //effet de bord : rempli ELF->indiceRelocations et ELF->lsr

	ELF->lsr = 0;
	//calcul du nombre de sections de relocation
    	for (int i = 0; i < ELF->les; i++) {
		if (ELF->Entetes_Sections[i]->sh_type == SHT_REL) { //si la section est une section de relocation (on ne traite pas SHT_RELA)
	    		ELF->lsr = ELF->lsr + 1;
		}
    	}
    	
    	//alloue l'espace mémoire pour le tableau des offset et le tableau général de toutes les relocations
    	ELF->indiceRelocations = malloc(ELF->lsr * sizeof (int));
    	Elf32_Rel** toutesReloc = malloc(ELF->lsr * sizeof (Elf32_Rel*));
    	int indRel = 0;
	 for (int i = 0; i < ELF->les; i++) {
		if (ELF->Entetes_Sections[i]->sh_type == SHT_REL) {
	    		Elf32_Rel* sectionRelocation = lireRelocationsDeSection(f, i, ELF);
	    		toutesReloc[indRel] = sectionRelocation; //insère le tableau des relocations de la section actuelle dans le tableau général
	    		ELF->indiceRelocations[indRel] = i; //sauvegarde l'indice de cette section dans l'entete des sections
	    		indRel++;
		}
    	}
	return toutesReloc;

}*/
