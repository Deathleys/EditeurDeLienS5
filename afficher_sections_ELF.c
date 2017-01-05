#include "afficher_sections_ELF.h"

void afficher_type_section (Elf32_Shdr* Entete_Section) {
	
	switch (Entete_Section->sh_type) {
            case SHT_NULL: printf("NULL\t\t");
                break;
            case SHT_PROGBITS: printf("PROGBITS\t");
                break;
            case SHT_SYMTAB: printf("SYMTAB\t\t");
                break;
            case SHT_STRTAB: printf("STRTAB\t\t");
                break;
            case SHT_RELA: printf("RELA\t\t");
                break;
            case SHT_HASH: printf("HASH\t\t");
                break;
            case SHT_DYNAMIC: printf("DYNAMIC\t\t");
                break;
            case SHT_NOTE: printf("NOTE\t\t");
                break;
            case SHT_NOBITS: printf("NOBITS\t\t");
                break;
            case SHT_REL: printf("REL\t\t");
                break;
            case SHT_SHLIB: printf("SHLIB\t\t");
                break;
            case SHT_DYNSYM: printf("DYNSYM\t\t");
                break;
            case SHT_LOPROC: printf("LOPROC\t\t");
                break;
            case SHT_HIPROC: printf("HIPROC\t\t");
                break;
            case SHT_LOUSER: printf("LOUSER\t\t");
                break;
            case SHT_HIUSER: printf("HIUSER\t\t");
                break;
            case SHT_ARM_EXIDX: printf("ARM_EXIDX\t");
            	break;
            case SHT_ARM_PREEMPTMAP: printf("ARM_PREEMPTMAP\t");
                break;
            case SHT_ARM_ATTRIBUTES: printf("ARM_ATTRIBUTES\t");
                break;
            default: printf("Indéterminé\t") ;
            
	}
	
}

void afficher_addr_section(Elf32_Shdr* Entete_Section) {
        if (Entete_Section->sh_addr != 0) {
            printf("%u\t", Entete_Section->sh_addr);
        } else {
            printf("undef\t");
        }
}

void afficher_decalage_section(Elf32_Shdr* Entete_Section) {
        printf("%06x\t", Entete_Section->sh_offset);
}

void afficher_size_section(Elf32_Shdr* Entete_Section) {
        printf("%06u\t", Entete_Section->sh_size);
}

void afficher_info_section(Elf32_Shdr* Entete_Section) {   
        printf("%u\t", Entete_Section->sh_info);
}

void afficher_flags_section(Elf32_Shdr* Entete_Section) { 
	if(Entete_Section->sh_flags == 0) printf("NONE");
	else {
		if (((Entete_Section->sh_flags >> 0) & 1) == 1) printf("W");
        	if (((Entete_Section->sh_flags >> 1) & 1) == 1) printf("A");
        	if (((Entete_Section->sh_flags >> 2) & 1) == 1) printf("X");
        	if (Entete_Section->sh_flags == SHF_MASKPROC) printf("P");
        }
        printf("\t");
}

void afficher_legende_flags() {

	printf("Permissions:\nW (écriture), A (allocation), X (exécution), P (spécifique au processeur)\n");

}

char* getTableNoms(donnees_ELF ELF, FILE *f) {
    	Elf32_Shdr *StringTable = ELF->Entetes_Sections[ELF->ind_etstrtab] ;
    	fseek(f, StringTable->sh_offset, SEEK_SET);
    	char* str = malloc(StringTable->sh_size);
    	for (int index = 0; index < StringTable->sh_size; index++) {
        	str[index] = fgetc(f);
    	}
    	return str;
}

void afficher_nom_section(char* str, Elf32_Shdr* Entete_Section) { 
	int i = Entete_Section->sh_name;
        while (str[i] != '\0') {
            printf("%c", str[i]);
            i++;
        }	
	
}

void afficher_entetes_sections (donnees_ELF ELF) {

	int i ;
	
	//char* tableNoms = getTableNoms(ELF);

	printf("[Nr]\tTaille\tType\t\tInfo\tPerm.\tDecal.\tNom\n");	
    		
    for (i = 0 ; i < ELF->les ; i++) {
	
		printf("[%i]\t", i);
		afficher_size_section(ELF->Entetes_Sections[i]);
		afficher_type_section(ELF->Entetes_Sections[i]);
		afficher_info_section(ELF->Entetes_Sections[i]);
		afficher_flags_section(ELF->Entetes_Sections[i]);
		afficher_decalage_section(ELF->Entetes_Sections[i]);
		//afficher_nom_section(tableNoms, Entetes_Sections->Entete[i]);
		printf("\n");
		
	}
	
}
	
/*	

int main (int argc, char **argv) {

	if (argc == 2) {
		FILE *f ;
		int i;
		
		f = fopen(argv[1], "r") ;
	
		//récupération de l'entete du fichier ELF
		Elf32_Ehdr* Entete_ELF = lire_Entete_ELF (f) ;
		
		//récupération de l'entete des sections
		int nbSections = Entete_ELF->e_shnum;
    		Elf32_Shdr* table_Entete_Sections[nbSections];
    		
    		
    		//création de la table des sections
    		for (i = 0; i < nbSections; i++) {
    			table_Entete_Sections[i] = malloc(sizeof (Elf32_Shdr));
    			table_Entete_Sections[i] = lire_Entete_Section(f, i, Entete_ELF);
    		}
    		
    		

    		//lecture de la table des sections
    		printf("[Nr]\tTaille\tType\t\tInfo\tPerm.\tDecal.\tNom\n");	
    		for (i = 0; i < nbSections; i++) {
        		printf("[%i]\t", i);
        		afficher_size_section(table_Entete_Sections[i]);
    			afficher_type_section(table_Entete_Sections[i]);
    			afficher_info_section(table_Entete_Sections[i]);
    			afficher_flags_section(table_Entete_Sections[i]);
			afficher_decalage_section(table_Entete_Sections[i]);
			afficher_nom_section(tableNoms,table_Entete_Sections[i]);
			printf("\n");
       			
    		}
    		afficher_legende_flags();
		fclose(f) ;

	
	}
	
	return 0 ;
	
}*/
