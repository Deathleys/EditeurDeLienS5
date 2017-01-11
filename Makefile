#############################################################################
# Fichier Makefile du Projet INF352
#############################################################################
# utilisation des variables internes $< $@ $* $^
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dépendance
# $* : correspond au nom du fichier sans extension
# $^ : correspond aux noms des dépendances
#       (dans les règles génériques uniquement)
#############################################################################
# information sur la règle exécutée avec la commande @echo
# (une commande commençant par @ n'est pas affichée à l'écran)
#############################################################################


#############################################################################
# définition des variables locales
#############################################################################

#############################################################################
#       modifier si nécessaire les variables BASEDIR et LIBDIRX11           #

# repertoire de base de la librairie graphsimple au DLST - serveur turing
BASEDIR = $(HOME)

# chemin d'acces aux librairies X11 et Xpm au DLST - serveur turing
LIBDIRX11 = /usr/lib/x86_64-linux-gnu

#                                                                           #
#############################################################################


# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -Werror -std=c99 -Wpadded

# chemin d'accès aux librairies (interfaces)
INCDIR = $(BASEDIR)/include

# chemin d'accès aux librairies (binaires)
LIBDIR = $(BASEDIR)/lib

# options pour l'édition des liens
OBJETS_OPTS = -L$(LIBDIR) # -lgraphsimple \
              #-L$(LIBDIRX11) -lX11 -lrt -lm -lXpm

# options pour la recherche des fichiers .ali et .ads
INCLUDE_OPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g $(INCLUDEOPTS)

# liste des exécutables
EXECUTABLES = run


#############################################################################
# définition des règles
#############################################################################

########################################################
# la règle par défaut
all : run

########################################################
# règle générique : 
#  remplace les règles de compilation séparée de la forme
#	module.o : module.c module.h
#		$(CC) $(CFLAGS) -c module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) $(CFLAGS) -c $<

########################################################
# règles explicites de création des exécutables
	
run : fusion_progbits_ELF.o fusion_symboles_ELF.o main.o lecture_fichier_ELF.o afficher_tables_reimplantation_ELF.o afficher_symbole_ELF.o afficher_sections_contenu_ELF.o afficher_sections_ELF.o afficher_entete_ELF.o util.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Création de l'exécutable "$@
	@echo "---------------------------------------------"
	$(CC) $(CFLAGS) $^ -o $@

########################################################
# regle pour créer tous les exécutables
all_exec : $(EXECUTABLES)


########################################################
# règle pour "nettoyer" le répertoire
clean:
	@echo ""
	@echo "---------------------------------------------"
	@echo "Nettoyage du repertoire "
	@echo "---------------------------------------------"
	rm -fR $(EXECUTABLES) main.o fusion_symboles_ELF.o fusion_progbits_ELF.o afficher_tables_reimplantation_ELF.o afficher_symbole_ELF.o afficher_sections_contenu_ELF.o lecture_fichier_ELF.o afficher_sections_ELF.o afficher_entete_ELF.o util.o

