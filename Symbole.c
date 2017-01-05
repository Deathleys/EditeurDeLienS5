void afficher_association_objet (Elf32_Sym *symbole) {
	
	//Vérifier ELF32_ST_TYPE()

	printf("Type de symbole et de liaison : ") ;
	
	switch ( ELF32_ST_TYPE(symbole->st_info) {
	
		case STT_NOTYPE : printf("Indéfini") ; break ;
		case STT_OBJECT  : printf("Donnée objet") ; break ;
		case STT_FUNC : printf("Fonction ou code exécutable") ; break ;
		case STT_SECTION  : printf("Section") ; break ;
		case STT_FILE  : printf("Fichier") ; break ; // A vérifier, donne le nom de fichier normalement.
		default : printf("Spécifique au Processeur") ;
		
	}
	
}

void afficher_portee_symbole (Elf32_Sym *symbole) {
	
	// Vérifier ELF32_ST_BIND()

	printf("Type de portée : ") ;
	
	switch (ELF32_ST_BIND(symbole->st_info)) {
	
		case STB_LOCAL : printf("Locale") ; break ;
		case STB_GLOBAL  : printf("Global") ; break ;
		case STB_WEAK : printf("Faible") ; break ;
		default : printf("Spécifique au Processeur") ;
		
	}
	
}

void afficher_valeur (Elf32_Sym *symbole) {

	printf("Valeur : ") ;
	
	printf("%d",symbole->st_value)
	
}

void afficher_taille (Elf32_Sym *symbole) {

	printf("Taille : ") ;
	
	printf("%d",symbole->st_size)
	
}

void afficher_association_objet (Elf32_Sym *symbole) {
	
	//Vérifier ELF32_ST_TYPE()

	printf("Type de visibilité : ") ;
	
	switch (symbole->other) {
	
		case STV_DEFAULT : printf("Indéfini") ; break ;
		case STV_HIDDEN : printf("Non valable dans d'autres modules") ; break ;
		case STV_PROTECTED  : printf("Préemptible ou non exporté") ; break ;
		default : printf("Spécifique au Processeur") ;
		
	}
	
}
