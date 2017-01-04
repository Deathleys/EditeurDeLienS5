#include <stdio.h>
#include <stdlib.h>
#include <byteswap.h>
#include <elf.h>
#include <string.h>
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

char* getTableNoms(FILE* f, Elf32_Ehdr* En_Tete_ELF) {
    	Elf32_Shdr* stringTable = lire_Entete_Section(f, En_Tete_ELF->e_shstrndx, En_Tete_ELF);
    	fseek(f, stringTable->sh_offset, SEEK_SET);
    	char* str = malloc(stringTable->sh_size);
    	for (int index = 0; index < stringTable->sh_size; index++) {
        	str[index] = fgetc(f);
    	}
    	return str;
}

char* getName(char* tableNoms, )

int getIndex(int nbSections, char* tableNoms, char* nomSection){
	int i = 0;
	int i = En_Tete_Section->sh_name;
        while (str[i] != '\0') {
            printf("%c", str[i]);
            i++;
        }
	while (i < nbSections && strcmp((char*)tableNoms[i], nomSection) != 0){
		i++;
	}
	if (i < nbSections){
		return i;
	} else{
		return 0;
	}
}

char* getContenuSection(int indexSection, Elf32_Ehdr* En_Tete_ELF, FILE* f){
	Elf32_Shdr* shdr = lire_Entete_Section(f, indexSection, En_Tete_ELF);
	fseek(f, shdr->sh_offset, SEEK_SET);
	char* contenu = malloc(shdr->sh_size);
	fread(contenu, shdr->sh_size, 1, f);
	return contenu;
}

void afficherContenuSection(char* contenu){
	printf("%s", contenu);
}

int main (int argc, char **argv) {
	int indexSection;
	if (argc == 3) {
		FILE *f = fopen(argv[1], "r") ;

		//récupération de l'entete du fichier ELF
		Elf32_Ehdr* En_Tete_ELF = lire_Entete_ELF (f) ;
		
		//récupération de l'entete des sections
		int nbSections = En_Tete_ELF->e_shnum;

    		char* tableNoms = getTableNoms(f,En_Tete_ELF);
    		
		//test si l'argument est le nom ou l'indice de la section
    		if(atoi(argv[2])>0 && atoi(argv[2])<nbSections) {
    			indexSection = atoi(argv[2]);
    		} else {
    			indexSection = getIndex(nbSections, tableNoms, argv[2]);
    		}
    		
    		if (indexSection == 0){
    			printf("La section n'a pas de données à être vidangé.");
    		} else{
    			char* contenuSection = getContenuSection(indexSection, En_Tete_ELF, f);
    			afficherContenuSection(contenuSection);
    		}
    		
		fclose(f) ;

	
	}
	
	return 0 ;
	
}
