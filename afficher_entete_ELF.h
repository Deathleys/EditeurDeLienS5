#ifndef AFFICHER_ENTETE_ELF_H
#define AFFICHER_ENTETE_ELF_H

#include "type.h"
#include "tableau.h"

#define TITRE_ELF "EN-TETE FICHIER ELF :"
#define LONGUEUR_ELF 130
#define COULEUR_POLICE_ELF 35
#define COULEUR_CARRE_ELF 42

void afficher_nombre_magique (Elf32_Ehdr *Entete) ;

void afficher_classe (Elf32_Ehdr *Entete) ;

void afficher_encodage (Elf32_Ehdr *Entete) ;

void afficher_version (Elf32_Ehdr *Entete) ;

void afficher_OSABI (Elf32_Ehdr *Entete) ;

void afficher_versionABI (Elf32_Ehdr *Entete) ;

void afficher_type (Elf32_Ehdr *Entete) ;

void afficher_machine (Elf32_Ehdr *Entete) ;

void afficher_point_entree (Elf32_Ehdr *Entete) ;

void afficher_decalage_entetes_programme (Elf32_Ehdr *Entete) ;

void afficher_decalage_entetes_section (Elf32_Ehdr *Entete) ;

void afficher_fanions (Elf32_Ehdr *Entete) ;

void afficher_taille_entete (Elf32_Ehdr *Entete) ;

void afficher_taille_section_programme (Elf32_Ehdr *Entete) ;

void afficher_nombre_sections_programme (Elf32_Ehdr *Entete) ;

void afficher_taille_entete_section (Elf32_Ehdr *Entete) ;

void afficher_nombre_entetes_section (Elf32_Ehdr *Entete) ;

void afficher_taille_partie_section (Elf32_Ehdr *Entete) ;

void afficher_indice_shstrtab (Elf32_Ehdr *Entete) ;

void afficher_entete_ELF (Elf32_Ehdr *Entete) ;

#endif
