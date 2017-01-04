#include <stdio.h>
#include <stdlib.h>
#include <byteswap.h>
#include <elf.h>
#include "util.h"
#define MODE_BIG_ENDIAN 2

Elf32_Ehdr* lire_Entete_ELF (FILE *f) {
	
	Elf32_Ehdr *En_Tete = malloc (sizeof *En_Tete) ;
	
	fread(En_Tete, sizeof (Elf32_Ehdr), 1, f) ;
	if ((! is_big_endian () && En_Tete->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && En_Tete->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) {
		En_Tete->e_type = reverse_2(En_Tete->e_type);
		En_Tete->e_machine = reverse_2(En_Tete->e_machine);
		En_Tete->e_version = reverse_4(En_Tete->e_version);
	 	En_Tete->e_entry = reverse_4(En_Tete->e_entry);
		En_Tete->e_phoff = reverse_4(En_Tete->e_phoff);
		En_Tete->e_shoff = reverse_4(En_Tete->e_shoff);
		En_Tete->e_flags = reverse_4(En_Tete->e_flags);
		En_Tete->e_ehsize = reverse_2(En_Tete->e_ehsize);
		En_Tete->e_phentsize = reverse_2(En_Tete->e_phentsize);
		En_Tete->e_phnum = reverse_2(En_Tete->e_phnum);
		En_Tete->e_shentsize = reverse_2(En_Tete->e_shentsize);
		En_Tete->e_shnum = reverse_2(En_Tete->e_shnum);
		En_Tete->e_shstrndx = reverse_2(En_Tete->e_shstrndx);
	    
	}
	return En_Tete ;
}

Elf32_Shdr* lire_Entete_Section(FILE* f, int index, Elf32_Ehdr* En_Tete_ELF) {
    
    Elf32_Shdr* En_Tete_Section;
    
    fseek(f, En_Tete_ELF->e_shoff + index * sizeof (Elf32_Shdr), SEEK_SET);
    
    En_Tete_Section = malloc(sizeof (Elf32_Shdr));

    fread(En_Tete_Section, sizeof (Elf32_Shdr), 1, f);

    if ((! is_big_endian () && En_Tete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN) || (is_big_endian() && En_Tete_ELF->e_ident[EI_DATA] == MODE_BIG_ENDIAN)) { // 5 correspondant à l'octet étant le big ou little
        En_Tete_Section->sh_name = __bswap_32(En_Tete_Section->sh_name);
        En_Tete_Section->sh_type = __bswap_32(En_Tete_Section->sh_type);
        En_Tete_Section->sh_flags = __bswap_32(En_Tete_Section->sh_flags);
        En_Tete_Section->sh_addr = __bswap_32(En_Tete_Section->sh_addr);
        En_Tete_Section->sh_offset = __bswap_32(En_Tete_Section->sh_offset);
        En_Tete_Section->sh_size = __bswap_32(En_Tete_Section->sh_size);
        En_Tete_Section->sh_link = __bswap_32(En_Tete_Section->sh_link);
        En_Tete_Section->sh_info = __bswap_32(En_Tete_Section->sh_info);
        En_Tete_Section->sh_addralign = __bswap_32(En_Tete_Section->sh_addralign);
        En_Tete_Section->sh_entsize = __bswap_32(En_Tete_Section->sh_entsize);
    }
    return En_Tete_Section;
}

void afficher_type_section (Elf32_Shdr* En_Tete_Section) {
	
	switch (En_Tete_Section->sh_type) {
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
                //ARM
            //case SHT_ARM_EXIDX: printf("ARM_EXIDX\t");
               // break;
            //case SHT_ARM_PREEMPTMAP: printf("ARM_PREEMPTMAP\t");
            //    break;
            //case SHT_ARM_ATTRIBUTES: printf("ARM_ATTRIBUTES\t");
            //    break;
            //case SHT_ARM_DEBUGOVERLAY: printf("ARM_DEBUGOVERLAY\t");
            //    break;
            //case SHT_ARM_OVERLAYSECTION: printf("ARM_OVERLAYSECTION\t");
            //    break;
            default: printf("unknown type\t");
                break;		
	}
	
}

void afficher_addr_section(Elf32_Shdr* En_Tete_Section) {
        if (En_Tete_Section->sh_addr != 0) {
            printf("%u\t", En_Tete_Section->sh_addr);
        } else {
            printf("undef\t");
        }
}

void afficher_decalage_section(Elf32_Shdr* En_Tete_Section) {
        printf("%06x\t", En_Tete_Section->sh_offset);
}

void afficher_size_section(Elf32_Shdr* En_Tete_Section) {
        printf("%06u\t", En_Tete_Section->sh_size);
}

void afficher_info_section(Elf32_Shdr* En_Tete_Section) {   
        printf("%u\t", En_Tete_Section->sh_info);
}

void afficher_flags_section(Elf32_Shdr* En_Tete_Section) { 
	if(En_Tete_Section->sh_flags == 0) printf("NONE");
	else {
		if (((En_Tete_Section->sh_flags >> 0) & 1) == 1) printf("W");
        	if (((En_Tete_Section->sh_flags >> 1) & 1) == 1) printf("A");
        	if (((En_Tete_Section->sh_flags >> 2) & 1) == 1) printf("X");
        	if (En_Tete_Section->sh_flags == SHF_MASKPROC) printf("P");
        }
        printf("\t");
}

void afficher_legende_flags() {

	printf("Permissions:\nW (écriture), A (allocation), X (exécution), P (spécifique au processeur)\n");

}

char* getTableNoms(FILE* f, Elf32_Ehdr* En_Tete_ELF) {
    	Elf32_Shdr* stringTable = lire_Entete_Section(f, En_Tete_ELF->e_shstrndx, En_Tete_ELF);
    	fseek(f, stringTable->sh_offset, SEEK_SET);
    	char* str = malloc(stringTable->sh_size);
    	for (int index = 0; index < stringTable->sh_size; index++) {
        	str[index] = fgetc(f);
    	}
    	return str;
}

void afficher_nom_section(char* str, Elf32_Shdr* En_Tete_Section) { 
	int i = En_Tete_Section->sh_name;
        while (str[i] != '\0') {
            printf("%c", str[i]);
            i++;
        }	
	
}


int main (int argc, char **argv) {

	if (argc == 2) {
		FILE *f ;
		int i;
		
		f = fopen(argv[1], "r") ;
	
		//récupération de l'entete du fichier ELF
		Elf32_Ehdr* En_Tete_ELF = lire_Entete_ELF (f) ;
		
		//récupération de l'entete des sections
		int nbSections = En_Tete_ELF->e_shnum;
    		Elf32_Shdr* table_Entete_Sections[nbSections];
    		
    		
    		//création de la table des sections
    		for (i = 0; i < nbSections; i++) {
    			table_Entete_Sections[i] = malloc(sizeof (Elf32_Shdr));
    			table_Entete_Sections[i] = lire_Entete_Section(f, i, En_Tete_ELF);
    		}
    		
    		char* tableNoms = getTableNoms(f,En_Tete_ELF);

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
	
}
