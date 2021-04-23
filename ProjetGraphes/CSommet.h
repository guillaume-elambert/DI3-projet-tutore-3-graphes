#ifndef CSOMMET_H
#define CSOMMET_H

#include <iostream>
#include <string>
#include "CException.h"
#include "CArc.h"

#define Lecture_Impossible 20


class CSommet
{
private:
	unsigned int uSOMId;
	CArc * pARCSOMListeArcsArrivants;
	unsigned int uSOMTailleListeA;
	CArc * pARCSOMListeArcsSortants;
	unsigned int uSOMTailleListeS;

public:
	/*************************************************
	*****NOM : CSommet
	**************************************************
	*****Constructeur par d�faut
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Cr�action d'un CSommet d'uSOMId = 0.
	*************************************************/
	CSommet(void);
	/*************************************************
	*****NOM : CSommet
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entr�e : unsigned int uNid l'Id du Sommet.
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Cr�action d'un CSommet d'uSOMId = uNid.
	*************************************************/
	CSommet(unsigned int uNid);
	/*************************************************
	*****NOM : CSommet
	**************************************************
	*****Constructeur de recopie
	**************************************************
	*****Entr�e : CSommet & SOMParam
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Cr�ation d'un CSommet copie de SOMParam.
	*************************************************/
	CSommet(CSommet & SOMParam);

	/*************************************************
	*****NOM : ~CSommet
	**************************************************
	*****Destructeur par d�faut
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : L'objet est pr�t � �tre d�sallou�.
	*************************************************/
	~CSommet(void);

	/*************************************************
	*****NOM : SOMGetId
	**************************************************
	*****Accesseur en lecture de uSOMId.
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : uSOMId
	*****Entra�ne : /
	*************************************************/
	unsigned int SOMGetId();

	/*************************************************
	*****NOM : SOMLireTailleE
	**************************************************
	*****Accesseur en lecture de uSOMTailleListeArrivants.
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : uSOMTailleListeArrivants
	*****Entra�ne : /
	*************************************************/
	unsigned int SOMGetTailleA();

	/*************************************************
	*****NOM : SOMLireTailleE
	**************************************************
	*****Accesseur en lecture de uSOMTailleListeA.
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : uSOMTailleListeS
	*****Entra�ne : /
	*************************************************/
	unsigned int SOMGetTailleS();

	/*************************************************
	*****NOM : SOMAjouterArcArrivant
	**************************************************
	*****Ajoute un arc arrivant.
	**************************************************
	*****Entr�e : CArc ARCParam
	*****N�cessite : ARCParam n'est pas d�j� dans la liste des arcs arrivants.
	*****Sortie : n�ant
	*****Entra�ne : La liste des arcs contient maintenant ARCParam.
	*************************************************/
	void SOMAjouterArcArrivant(CArc & ARCParam);


	/*************************************************
	*****NOM : SOMRetirerArcArrivant
	**************************************************
	*****Retire un arc arrivant.
	**************************************************
	*****Entr�e : CArc ARCParam
	*****N�cessite : ARCParam est dans la liste des arcs arrivants.
	*****Sortie : n�ant
	*****Entra�ne : La liste des arcs ne contient maintenant plus ARCParam.
	*************************************************/
	void SOMRetirerArcArrivant(CArc & ARCParam);


	/*************************************************
	*****NOM : SOMChercherArcArrivant
	**************************************************
	*****Recherche un arc d'id particulier.
	**************************************************
	*****Entr�e : unsigned int uSOMIdDestination
	*****N�cessite : n�ant
	*****Sortie : la position de l'arc cherch� dans la liste si il y est, -1 sinon.
	*****Entra�ne : /
	*************************************************/
	int SOMChercherArcArrivant(unsigned int uSOMIdDestination);


	/*************************************************
	*****NOM : SOMLireListeA
	**************************************************
	*****Lis l'arc en position uPos de la liste.
	**************************************************
	*****Entr�e : unsigned int uPos
	*****N�cessite : uPos < uSOMTailleListeA - 1
	*****Sortie : n�ant
	*****Entra�ne : /
	*************************************************/
	CArc SOMLireListeA(unsigned int uPos);


	/*************************************************
	*****NOM : SOMAjouterArcSortant
	**************************************************
	*****Ajoute un arc sortant.
	**************************************************
	*****Entr�e : CArc ARCParam
	*****N�cessite : ARCParam n'est pas d�j� dans la liste des arcs sortants.
	*****Sortie : n�ant
	*****Entra�ne : La liste des arcs contient maintenant ARCParam.
	*************************************************/
	void SOMAjouterArcSortant(CArc & ARCParam);


	/*************************************************
	*****NOM : SOMRetirerArcSortant
	**************************************************
	*****Retire un arc sortant.
	**************************************************
	*****Entr�e : CArc ARCParam
	*****N�cessite : ARCParam est dans la liste des arcs sortants.
	*****Sortie : n�ant
	*****Entra�ne : La liste des arcs ne contient maintenant plus ARCParam.
	*************************************************/
	void SOMRetirerArcSortant(CArc & ARCParam);


	/*************************************************
	*****NOM : SOMChercherArcSortant
	**************************************************
	*****Recherche un arc d'id particulier.
	**************************************************
	*****Entr�e : unsigned int uSOMIdDestination
	*****N�cessite : n�ant
	*****Sortie : la position de l'arc cherch� dans la liste si il y est, -1 sinon.
	*****Entra�ne : /
	*************************************************/
	int SOMChercherArcSortant(unsigned int uSOMIdDestination);


	/*************************************************
	*****NOM : SOMLireListeS
	**************************************************
	*****Lis l'arc en position uPos de la liste.
	**************************************************
	*****Entr�e : unsigned int uPos
	*****N�cessite : uPos < uSOMTailleListeS
	*****Sortie : n�ant
	*****Entra�ne : /
	*************************************************/
	CArc SOMLireListeS(unsigned int uPos);


	/*************************************************
	*****NOM : operator=
	**************************************************
	*****Surcharge de l'op�rateur =
	**************************************************
	*****Entr�e : const CSommet & SOMParam
	*****N�cessite : n�ant
	*****Sortie : CSommet &
	*****Entra�ne : L'objet deviens une copie de SOMParam
	*************************************************/
	CSommet & operator=(const CSommet & SOMParam);


	/*************************************************
	*****NOM : SOMLies
	**************************************************
	*****Teste si deux sommets sont li�s dans le sens *this -> SOMParam
	**************************************************
	*****Entr�e : CSommet & SOMParam
	*****N�cessite : n�ant
	*****Sortie : bool bTeste
	*****Entra�ne : Si il existe un arc allant de cet objet vers SOMParam, bTeste = true. bTeste = false sinon.
	*************************************************/
	bool SOMLies(CSommet & SOMParam);


	/*************************************************
	*****NOM : SOMInverser
	**************************************************
	*****Inverse les arcs entrants et sortants.
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : /
	*************************************************/
	void SOMInverser();


	/*************************************************
	*****NOM : SOMAfficherSommet
	**************************************************
	*****Affiche le graphe sur la sortie standard.
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : /
	*************************************************/
	void SOMAfficherSommet();
};

#endif