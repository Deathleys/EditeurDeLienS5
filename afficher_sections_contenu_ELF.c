#include "afficher_sections_contenu_ELF.h"

void get_nom_section(char* str, Elf32_Shdr* En_Tete_Section, char* nom) {
	int i = En_Tete_Section->sh_name;
	strcpy(nom,&str[i]);
}

int getIndexByName(Elf32_Ehdr* En_Tete_ELF, Elf32_Shdr** Entetes_Section, char *tableNoms, char* nomSection){
	
	for (int i = 0; i < En_Tete_ELF->e_shnum; i++) {
		char shdr_name[100]={""};

		get_nom_section(tableNoms, Entetes_Section[i], shdr_name);

		if(strcmp(nomSection, shdr_name) == 0) return i;
	}

	return 0;
        
}

unsigned char* getContenuSection(Elf32_Shdr* Entete_Section, FILE* f){

	fseek(f,Entete_Section->sh_offset, SEEK_SET);

	unsigned char* contenu = malloc(sizeof (unsigned char)*Entete_Section->sh_size);

	fread(contenu, Entete_Section->sh_size, 1, f);
	for (int i = 0; i < Entete_Section->sh_size; i++) {
		fread(contenu, 1, 1, f);
	}
	/*for (int i = 0; i < shdr->sh_size; i=i+4) {
		printf("%02x%02x%02x%02x\n", contenu[i], contenu[i+1], contenu[i+2],contenu[i+3]);
	}
	for (int i = 1; i <= shdr->sh_size; i++) {
		printf("%02x", contenu[i]);
		if(i%4==0)printf(" ");		
	}
	printf("\n");*/
	return contenu;
}

void afficherContenuSection(unsigned char* contenu){
	//TODO utiliser afficher_Text
}

//retourne l'indice correspondant au second argument passé au progamme (nombre ou nom)
int getIndex(donnees_ELF ELF, FILE *f , char* index_char) {

	int index = atoi(index_char);

    	if( index > 0 && index < ELF->Entete_ELF->e_shnum)
    		return index;
	else 
    		return getIndexByName(ELF->Entete_ELF, ELF->Entetes_Sections, ELF->Table_Chaines, index_char);			
}


void afficher_contenu_sections (donnees_ELF ELF, FILE *f ,char *index_char ) {
	
	int indexSection = 0;

	indexSection = getIndex(ELF, f, index_char);

	if (indexSection == 0)
    		printf("La section n'a pas de données à être vidangé.");
    	else{
		printf("Vidange héxadécimale de la section \"%s\"",index_char);
    		unsigned char* contenuSection = getContenuSection(ELF->Entetes_Sections[indexSection], f);
    		afficherContenuSection(contenuSection);
    	}

}

/*
int main (int argc, char **argv) {

	char Magic_Number_ELF[TAILLE_MAGIC_NUMBER] = {0x7f, 'E', 'L', 'F'} ;

	if (argc >= 3) {

		FILE *f ;
	
		f = fopen(argv[1], "r") ;
		
		donnees_ELF ELF = malloc (sizeof *ELF) ;
		
		ELF->Entete_ELF = lire_Entete_ELF (f) ;
		//ELF->Entete_ELF == En_Tete_ELF
		
		if (est_fichier_ELF(Magic_Number_ELF, ELF->Entete_ELF) && ELF->Entete_ELF->e_ident[EI_CLASS] == CLASSE_32BITS) {
		
			ELF->Entete_Programme = lire_Entete_Programme (ELF->Entete_ELF, f) ;
			
			ELF->ind_etstrtab = ELF->Entete_ELF->e_shstrndx ;
			
			ELF->les = ELF->Entete_ELF->e_shnum ;
			
			lire_Text (ELF,f) ;
			
			ELF->Entetes_Sections = malloc (sizeof (Elf32_Shdr) * ELF->les) ;
			
			lire_Entetes_Sections (ELF, f) ;
	
			afficher_entete (ELF->Entete_ELF) ;
			
			printf("\n\n") ;
			
			afficher_Text(ELF) ;
			
			printf("\n") ;
			
			afficher_entetes_sections (ELF) ;

			if (argc == 3) {
				afficher_contenu_sections(ELF,f,argv[2]);
			}
			
			liberer_struct_ELF (&ELF) ;
			
		}
		
		fclose(f) ;
	
	}
	
	return 0 ;
	
}*/
