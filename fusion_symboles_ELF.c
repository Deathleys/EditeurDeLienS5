


	
				

				

				

				
	
Liste=table2
nbSymboleTable1=table1.nbSymbole
nbSymboleListe=table2.nbSymbole
table symbole (nouvelleTable)
nbSymbNouvelle=0

Pour i allant de 1 à nbSymboleTable1

	Si table1[i].lien=LOCAL				// Symboles LOCAUX => ON GARDE
		Ajouter(nouvelleTable,table1[i])
		nbSymbNouvelle+1
		
	Sinon Si table1[i].lien=GLOBAL				
		Pour j allant de 1 à nbSymboleListe
			Si table1[i].name=table2[j].name
				Si !table1[i].ndx=UND && !table2[j].ndx=UND 					// mêmes noms et définis => on arrête l'édition des liens
					Afficher("Erreur, impossible de linker")
					ToutLiberer
					ArreterProgramme
				Sinon si table1[i].ndx=UND && !table2[j].ndx=UND				// mêmes noms , un seul défini => on garde le symbole défini
					Ajouter(nouvelleTable,table2[j])
				Sinon si !table1[i].ndx=UND && table2[j].ndx=UND				// mêmes noms , un seul défini => on garde le symbole défini
					Ajouter(nouvelleTable,table1[i])				
				Sinon 															// mêmes noms, non définis => on en garde un non défini
					Ajouter(nouvelleTable,table1[i])
				EnleverElémentListe(Liste[j])
				nbSymboleBuffer-1
				nbSymbNouvelle+1
				
																			// Remarque : on garde TOUJOURS un seul symbole GLOBAL
Pour j allant de 1 à nbSymboleBuffer+1
	Ajouter(nouvelleTable,table2[j])
	nbSymbNouvelle+1
