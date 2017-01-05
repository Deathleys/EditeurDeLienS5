#ifndef AFFICHER_ENTETE_ELF_H
#define AFFICHER_ENTETE_ELF_H

#include "type.h"

void afficher_magic_number (Elf32_Ehdr *Entete) ;

void afficher_classe_fichier (Elf32_Ehdr *Entete) ;

void afficher_convention_encodage (Elf32_Ehdr *Entete) ;

void afficher_version_fichier (Elf32_Ehdr *Entete) ;

void afficher_type_objet (Elf32_Ehdr *Entete) ;

void afficher_architecture (Elf32_Ehdr *Entete) ;

void afficher_version_fichier2 (Elf32_Ehdr *Entete) ;

void afficher_adresse_entree (Elf32_Ehdr *Entete) ;

void afficher_offset_entete_programme (Elf32_Ehdr *Entete) ;

void afficher_offset_entete_sections (Elf32_Ehdr *Entete) ;

void afficher_fanions (Elf32_Ehdr *Entete) ;

void afficher_taille_entete (Elf32_Ehdr *Entete) ;

void afficher_taille_entrees (Elf32_Ehdr *Entete) ;

void afficher_nombre_entrees (Elf32_Ehdr *Entete) ;

void afficher_taille_sections (Elf32_Ehdr *Entete) ;

void afficher_nombre_sections (Elf32_Ehdr *Entete) ;

void afficher_taille_partie_section (Elf32_Ehdr *Entete) ;

void afficher_entete (Elf32_Ehdr *Entete) ;

#endif
