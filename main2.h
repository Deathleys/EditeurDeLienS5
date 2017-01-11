#ifndef MAIN_H
#define MAIN_H

#include "type.h"
#include "lecture_fichier_ELF.h"
#include "affichage_ELF.h"
#include "fusion_progbits_ELF.h"
#include "fusion_symboles_ELF.h"
	
void initialiser_descripteur(FILE **f, char * nom_fichier, char *mode);

#endif
