#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <byteswap.h>
#include "util.h"

#define TAILLE_MAGIC_NUMBER 4
#define MODE_BIG_ENDIAN 2
#define CLASSE_32BITS 1

typedef struct data_ELF {
	
	Elf32_Shdr **Entete ;
	int l ;
	int ind_etstrtab ;
	int ind_etsymtab ;
	
} *data_ELF ;

#endif
