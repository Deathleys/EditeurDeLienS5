#include "fusion_progbits_ELF.h"

char* get_nom_section(donnees_ELF ELF, int i) {

	return ELF->Table_Chaines_ES + ELF->Entetes_Sections[i]->sh_name ;
		
}

void ajouter_nom_section(donnees_ELF ELF, char* nom_section){
	char* nom = malloc(sizeof(nom_section));
	strcpy(nom, nom_section);
	int taille = ELF->Entetes_Sections[ELF->Entete_ELF->e_shstrndx]->sh_size;
	int longueur_nom = sizeof(nom) + 1;
	int nouvelle_taille = taille + longueur_nom;
	ELF->Table_Chaines_ES = (char *) realloc(ELF->Table_Chaines_ES, nouvelle_taille);
	for (int i = taille; i < nouvelle_taille-1; i++){
		ELF->Table_Chaines_ES[i] = nom[i-taille];
	}
	ELF->Table_Chaines_ES[nouvelle_taille-1] = '\0';
	decalage_sections_suivantes(ELF, longueur_nom, ELF->Entete_ELF->e_shstrndx);
	
	//changement sh_name de la section
	ELF->Entetes_Sections[ELF->les-1]->sh_name = taille;
}

void decalage_sections_suivantes(donnees_ELF ELF, int decalage, int i){
	//shoff: début des en-têtes de section 
	if (ELF->Entetes_Sections[i]->sh_offset < ELF->Entete_ELF->e_shoff){
		ELF->Entete_ELF->e_shoff += decalage;
	}

	//phoff: début de l'en-tête du programme
	if (ELF->Entetes_Sections[i]->sh_offset < ELF->Entete_ELF->e_phoff){
		ELF->Entete_ELF->e_phoff += decalage;
	}

	//décalage des sections suivante
	for (int k = i+1; k < ELF->les; k++){
		ELF->Entetes_Sections[k]->sh_offset += decalage;
	}
}

//fusion des sections progbits de même nom de ELF1 et ELF2 dans ELF3
void concatenation_section_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3){

	for(int i = 0; i < ELF1->les; i++) {
		int decalage = 0;
		//cas des sections progbits à fusionner
		if(ELF1->Entetes_Sections[i]->sh_type == SHT_PROGBITS) {
			for(int j = 0; j < ELF2->les; j++) {
			
				//cas où la secton progbits est présente dans les deux fichiers => concaténer
				if(ELF2->Entetes_Sections[j]->sh_type == SHT_PROGBITS && strcmp(get_nom_section(ELF1, i),get_nom_section(ELF2, j))==0) {
					if (ELF2->Entetes_Sections[j]->sh_size != 0){

						ELF3->Entetes_Sections[i]->sh_size += ELF2->Entetes_Sections[j]->sh_size; // augmentation de la taille donnée pour cette section
						decalage = ELF2->Entetes_Sections[j]->sh_size;

						ELF3->Sections[i] = realloc(ELF3->Sections[i], ELF3->Entetes_Sections[i]->sh_size );


						memcpy(ELF3->Sections[i] + ELF1->Entetes_Sections[i]->sh_size,ELF2->Sections[j],ELF2->Entetes_Sections[j]->sh_size);
						
					}
				}
			}
		}
		if (decalage != 0){
			decalage_sections_suivantes(ELF3, decalage, i);
			
		}
	}
}

//Si la section progbits de ELF2 n'est pas dans ELF1, on l'ajoute dans ELF3
void ajout_section_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3){
	for(int i = 0; i < ELF2->les; i++) { //fusion des sections progbits de même nom
		int trouve = 0;
		//cas des sections progbits à fusionner
		if(ELF2->Entetes_Sections[i]->sh_type == SHT_PROGBITS) {
			for(int j = 0; j < ELF1->les; j++) {
			
				//cas où la secton progbits est présente dans les deux fichiers => concaténer
				if(ELF1->Entetes_Sections[j]->sh_type == SHT_PROGBITS && strcmp(get_nom_section(ELF1, j),get_nom_section(ELF2, i))==0) {
					trouve = 1;
				}
			}
			
			if (trouve == 0){
				//En-tête de section
				ELF3->Entetes_Sections = (Elf32_Shdr **) realloc(ELF3->Entetes_Sections, sizeof (Elf32_Shdr) * (ELF3->les + 1));
				Elf32_Shdr *nouvelle_section = malloc(sizeof(Elf32_Shdr));
				*nouvelle_section = *(ELF2->Entetes_Sections[i]);
				
				ELF3->Entetes_Sections[ELF3->les] = nouvelle_section;
				
				ELF3->Entetes_Sections[ELF3->les]->sh_offset = ELF3->Entetes_Sections[ELF3->les-1]->sh_offset + ELF3->Entetes_Sections[ELF3->les-1]->sh_size;

				//Contenu de section
				
				ELF3->Sections = (char **) realloc(ELF3->Sections, sizeof(char *) * (ELF3->les + 1));
				ELF3->Sections[ELF3->les] = malloc(ELF3->Entetes_Sections[ELF3->les]->sh_size);
				memcpy(ELF3->Sections[ELF3->les], ELF2->Sections[i], ELF3->Entetes_Sections[ELF3->les]->sh_size);
				
				
				//shnum + 1 / les + 1 dans l'en-tête de ELF3
				ELF3->les = ELF3->les + 1;
				ELF3->Entete_ELF->e_shnum = ELF3->Entete_ELF->e_shnum + 1;				
				ajouter_nom_section(ELF3, get_nom_section(ELF2, i));			
			}
		}
	}
	
}

void fusion_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3) { //ELF1 et ELF2 déjà remplis
	concatenation_section_progbits(ELF1, ELF2, ELF3);
	ajout_section_progbits(ELF1, ELF2, ELF3);
}

