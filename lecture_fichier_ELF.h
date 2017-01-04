#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>
#include "afficher_en_tete_ELF.h"
#include "util.h"

#define TAILLE_MAGIC_NUMBER 4

char Magic_Number[TAILLE_MAGIC_NUMBER] = {0x7f, 'E', 'L', 'F'} ;
