#ifndef FUSION_PROGBITS_ELF_H
#define FUSION_PROGBITS_ELF_H

#include "type.h"
#include "affichage_ELF.h"

char* get_nom_section(donnees_ELF ELF, int i);

void ajouter_nom_section(donnees_ELF ELF, char* nom);

void decalage_sections_suivantes(donnees_ELF ELF, int decalage, int i);

void concatenation_section_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3);

void ajout_section_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3);

void fusion_progbits(donnees_ELF ELF1, donnees_ELF ELF2, donnees_ELF ELF3);

#endif
