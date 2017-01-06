#############################################################################
# Fichier Makefile du Projet INF352
#############################################################################
# utilisation des variables internes $< $@ $* $^
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

#############################################################################
#       modifier si necessaire les variables BASEDIR et LIBDIRX11           #

# repertoire de base de la librairie graphsimple au DLST - serveur turing
BASEDIR = /Public/234_Public

# chemin d'acces aux librairies X11 et Xpm au DLST - serveur turing
LIBDIRX11 = /usr/lib/x86_64-linux-gnu

#                                                                           #
#############################################################################


# compilateur
CC = gcc

# options de compilation
CFLAGS = -Wall -Werror -std=c99

# chemin d'acces aux librairies (interfaces)
INCDIR = $(BASEDIR)/lib

# chemin d'acces aux librairies (binaires)
LIBDIR = $(BASEDIR)/lib

# options pour l'edition des liens
GNATLDOPTS = -L$(LIBDIR) -lgraphsimple \
             -L$(LIBDIRX11) -lX11 -lrt -lm -lXpm

# options pour la recherche des fichiers .ali et .ads
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = run


#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : run

########################################################
# regle generique : 
#  remplace les règles de compilation separée de la forme
#	module.o : module.c module.h
#		$(CC) $(CFLAGS) -c module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du paquetage "$*
	@echo "---------------------------------------------"
	$(CC) $(CFLAGS) -c $<

########################################################
# regles explicites de creation des executables
	
run : lecture_fichier_ELF.o afficher_sections_contenu_ELF.o afficher_sections_ELF.o afficher_entete_ELF.o util.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $(CFLAGS) $^ -o $@

########################################################
# regle pour créer tous les exécutables
all_exec : $(EXECUTABLES)


########################################################
# regle pour "nettoyer" le répertoire
clean:
	@echo ""
	@echo "---------------------------------------------"
	@echo "Nettoyage du repertoire "
	@echo "---------------------------------------------"
	rm -fR $(EXECUTABLES) afficher_sections_contenu_ELF.o lecture_fichier_ELF.o afficher_sections_ELF.o afficher_entete_ELF.o util.o

