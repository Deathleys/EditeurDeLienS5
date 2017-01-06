#ifndef AFFICHER_SECTIONS_CONTENU_ELF_H
#define AFFICHER_SECTIONS_CONTENU_ELF_H

#include <stdlib.h>
#include <ctype.h>
#include "type.h"

int indice_nom_entete (donnees_ELF ELF, char *nom) ;

void afficherContenuSection(donnees_ELF ELF, int section);

void afficher_contenu_sections (donnees_ELF ELF, char * index_char) ;

#endif
