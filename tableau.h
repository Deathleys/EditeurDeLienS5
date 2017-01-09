#ifndef TABLEAU_H
#define TABLEAU_H

#define COL 20

#define CARRE(C) printf("\033[%dm  \033[0m", C)

#define DESSINER_LIGNE(C,L) printf("\033[%dm", C) ;\
                            for (int i = 0 ; i < L ; i++ ) printf(" ") ;\
                            printf("\033[0m\n") ;

#define DESSINER_2BORDURES(C,L) CARRE(C) ;\
								for (int i = 0 ; i < L - 4 ; i++) printf(" ") ;\
								CARRE(C) ; printf("\n") ;

#define ECRIRE_TITRE(C1,T,C2,L) CARRE(C1) ;\
								for (int i = 0 ; i < (L - strlen(T)) / 2 ; i++) printf(" ") ;\
								printf("\033[1m\033[%dm%s\033[0m", C2,  T) ;\
								for (int i = 0 ; i < L - (L - strlen(T)) / 2 - strlen(T) - 4 ; i++) printf(" ") ;\
								CARRE(C1) ; printf("\n") ;

#define DESSINER_COL(C,L,N) for (int i = 0 ; i < N ; i++) {\
								for (int j = 0 ; j < L - 2 ; j++) printf(" ") ;\
								CARRE(C) ;\
							}

#endif
