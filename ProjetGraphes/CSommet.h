#ifndef CSOMMET_H
#define CSOMMET_H

#include <iostream>
#include <string>
#include "CException.h"
#include "CArc.h"

#define Lecture_Impossible	20
#define Alloc_Echouee		21


class CSommet
{
private:
	unsigned int uSOMId;
	CArc * pARCSOMListeArcsArrivants;
	unsigned int uSOMTailleListeA;
	CArc * pARCSOMListeArcsSortants;
	unsigned int uSOMTailleListeS;

public:
	
	/*!
	 * Constructeur par d�faut
	 * 
	 */
	CSommet(void);
	

	/*!
	 * Constructeur de confort
	 * 
	 * \param uNid Le num�ro du sommet
	 */
	CSommet(unsigned int uNid);

	
	/*!
	 * Constructeur de recopie. 
	 * Cr�� d'un CSommet copie de SOMParam.
	 * 
	 * \param SOMParam L'objet CSommet � copier
	 */
	CSommet(CSommet & SOMParam);

	
	/*!
	 * Destructeur par d�faut
	 * 
	 */
	~CSommet(void);

	

	/*!
	 * Accesseur en lecture de uSOMId.
	 * 
	 * \return Le num�ro du sommet
	 */
	unsigned int SOMGetId();


	/*!
	 * Accesseur en lecture de uSOMTailleListeArrivants.
	 * 
	 * \return Le nombre d'arcs arrivants au sommet
	 */
	unsigned int SOMGetTailleA();


	/*!
	 * Accesseur en lecture de uSOMTailleListeS.
	 * 
	 * \return Le nombre d'arcs partants du sommet
	 */
	unsigned int SOMGetTailleS();


	/*!
	 * Ajoute un arc arrivant au sommet.
	 * 
	 * \param ARCParam L'objet CArc � ajouter � la liste des arcs arrivants
	 * \pre ARCParam n'est pas d�j� dans la liste des arcs arrivants.
	 */
	void SOMAjouterArcArrivant(unsigned int uDestination);


	/*!
	 * Retire un arc arrivant au sommet.
	 * 
	 * \param ARCParam L'objet CArc � supprimer de la liste des arcs arrivants
	 * \pre ARCParam est dans la liste des arcs arrivants.
	 */
	void SOMRetirerArcArrivant(unsigned int uDestination);



	/*!
	 * Recherche l'arc arrivant ayant pour point de d�part le sommet num�ro uSOMIdDestination.
	 * 
	 * \param uSOMIdDestination Le num�ro du sommet de d�part de l'arc
	 * \return La position de l'arc cherch� dans la liste des arcs arrivants si il y est, -1 sinon.
	 */
	int SOMChercherArcArrivant(unsigned int uSOMIdDestination);


	
	/*!
	 * Lis l'arc arrivant en position uPos de la liste pARCSOMListeArcsArrivants.
	 * 
	 * \param uPos La position de l'arc dans la liste pARCSOMListeArcsArrivants
	 * \pre  0 <= uPos <= uSOMTailleListeA - 1
	 * \return Objet CArc � la position uPos dans la liste des arcs entrants
	 */
	CArc SOMLireListeA(unsigned int uPos);



	/*!
	 * Ajoute un arc sortant.
	 * 
	 * \param ARCParam L'objet CArc � ajouter � la liste des arcs sortants du sommet
	 * \pre ARCParam n'est pas d�j� dans la liste des arcs sortants.
	 */
	void SOMAjouterArcSortant(unsigned int uDestination);


	/*!
	 * Retire un arc sortant.
	 * 
	 * \param ARCParam L'objet CArc � supprimer de la liste des arcs sortants du sommet
	 * \pre ARCParam est dans la liste des arcs sortants.
	 */
	void SOMRetirerArcSortant(unsigned int uDestination);


	/*!
	 * Recherche l'arc partant ayant pour point d'arriv� le sommet num�ro uSOMIdDestination.
	 * 
	 * \param uSOMIdDestination Le num�ro du sommet d'arriv� de l'arc
	 * \return La position de l'arc cherch� dans la liste des arcs sortants si il y est, -1 sinon.
	 */
	int SOMChercherArcSortant(unsigned int uSOMIdDestination);


	/*!
	 * Lis l'arc en position uPos de la liste pARCSOMListeArcsSortants.
	 * 
	 * \param uPos La position de l'arc dans la liste pARCSOMListeArcsSortants
	 * \pre  0 <= uPos <= uSOMTailleListeS - 1
	 * \return Objet CArc � la position uPos dans la liste des arcs sortants
	 */
	CArc SOMLireListeS(unsigned int uPos);


	/*!
	 * Teste si deux sommets sont li�s dans le sens *this -> SOMParam
	 * 
	 * \param SOMParam true s'il existe un arc allant de cet objet vers SOMParam, false sinon.
	 * \return 
	 */
	bool SOMLies(CSommet & SOMParam);


	/*!
	 * Inverse les arcs entrants et sortants. 
	 * Les CArcs arrivants deviennent les CArcs sortants et vice-versa
	 * 
	 */
	void SOMInverser();


	/*!
	 * Affiche le graphe sur la sortie standard.
	 * 
	 */
	void SOMAfficherSommet();


	/*!
	 * Surcharge de l'operateur =
	 * Copie le contenu de SOMParam dans l'objet appelant
	 * 
	 * \param SOMParam L'objet CSommet � copier
	 * \return Un pointeur sur l'objet appelant, copie de SOMParam
	 */
	CSommet & operator=(const CSommet & SOMParam);
};

#endif