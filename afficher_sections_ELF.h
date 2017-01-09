#ifndef AFFICHER_SECTIONS_ELF_H
#define AFFICHER_SECTIONS_ELF_H

#include "type.h"
#include "tableau.h"

#define TITRE_ES "EN-TETES DES SECTIONS :"
#define NB_COL_ES 7
#define COL_NOM_ES 40
#define LONGUEUR_ES (NB_COL_ES * COL + 2)
#define COULEUR_POLICE_ES 32
#define COULEUR_CARRE_ES 45

#define DESSINER_COL_NOM_ES() DESSINER_COL(COULEUR_CARRE_ES, COL_NOM_ES, 1)

#define DESSINER_COL_ES() CARRE(COULEUR_CARRE_ES) ; DESSINER_COL_NOM_ES ()  ;\
						   DESSINER_COL(COULEUR_CARRE_ES, LONGUEUR_ES / NB_COL_ES, NB_COL_ES) ; printf("\n")

// Affiche le type de la section (PROGBITS,SYMTAB,STRTAB, etc.)
void afficher_type_section (Elf32_Shdr* Entete_Section) ;

// Affiche l'adresse où commence la section
void afficher_addr_section(Elf32_Shdr* Entete_Section) ;

// Affiche 
void afficher_decalage_section(Elf32_Shdr* Entete_Section) ;

// Affiche la position (offset) de la section par rapport au début du fichier 
void afficher_size_section(Elf32_Shdr* Entete_Section) ;

// Affiche les informatiosn d'allocation
void afficher_info_section(Elf32_Shdr* Entete_Section) ;

// Affiche les permissions
void afficher_flags_section(Elf32_Shdr* Entete_Section) ;

// Affiche une légende pour les permissions
void afficher_legende_flags() ;

// Affiche le nom de la section
void afficher_nom_section(donnees_ELF ELF, int i) ;

// Affiche les informations demandées ( numéro, nom, taille, type, informations  d'allocation, permissions, offset...)
void afficher_entetes_section (donnees_ELF Entetes_Sections) ;


#endif
