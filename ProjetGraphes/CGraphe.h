#ifndef CGRAPHE_H
#define CGRAPHE_H

#include <regex>
#include <fstream>
#include <string>
//#include "CGraphe.h"
#include "CSommet.h"
#include "CArc.h"
#include "CException.h"


#define Ouverture_Fichier_Impossible 1
#define Auto_Referencement			 2
#define Erreur_Syntaxe				 3
#define Erreur_NbSommets			 4
#define Erreur_NbArcs				 5
#define Sommet_Inconnu				 6
#define Sommet_Existant				 7
#define Arc_Inconnu					 8
#define Arc_Existant				 9

class CGraphe
{
private :

	CSommet * pSOMGPHListeSommet;
	unsigned int uGPHTailleLSom;


public:

	/*!
	 * Constructeur par d�faut
	 * 
	 */
	CGraphe(void);

	
	/*!
	 * Constructeur de recopie
	 * 
	 * \param GPHParam L'objet CGraphe � copier
	 */
	CGraphe(CGraphe & GPHParam);

	
	/*!
	 * Constructeur de confort
	 * Cr�ation d'un graphe vide et correctement initialis� � partir du fichier stock� dans sChemin. 
	 * OU Une erreur si le chemin ou le fichier est mauvais.
	 * 
	 * \param cpInput Le chemin vers le fichier contenant les informations du graphe � cr�er.
	 */
	CGraphe(const char * cpInput);


	/*!
	 * Destructeur par d�faut
	 * 
	 */
	~CGraphe(void);



	/*!
	 * Cherche si le sommet existe
	 *
	 * \param uId Un numero de sommet
	 * \return L'index du sommet cherch�
	 */
	int GPHChercherSommet(unsigned int uId);


	/*!
	 * Ajoute un nouveau sommet dans le graphe. 
	 * OU renvoie une erreur si le sommet existe d�j�
	 * 
	 * \param uNumero Le num�ro du nouveau sommet charch�.
	 * \return L'index du sommet cr��
	 */
	unsigned int GPHAjouterSommet(unsigned int uNumero);



	/*!
	 * Supprime un sommet dans le graphe.
	 * Supprime le sommet de numero uId du graphe ainsi que tout ses liens avec les autres sommets. 
	 * OU renvoie une erreur si le sommet n'existe pas
	 * 
	 * \param uId Num�ro du sommet � supprimer
	 */
	void GPHSupprimerSommet(unsigned int uId);



	/*!
	 * V�rifie si deux sommets sont li�s dans le sens sommet n� uSommetDep vers sommet n� uSommetArr
	 * 
	 * \param uSommetDep Le sommet de d�part
	 * \param uSommetArr Le sommet d'arriv�
	 * \return true si les deux sommets sons li�s dans le sens sommet n� uSommetDep vers sommet n� uSommetArr false sinon
	 */
	bool GPHLiees(unsigned int uSommetDep, unsigned int uSommetArr);


	/*!
	 * Lie deux sommets du graphe (cr�� l'arc Sommet de n� uIdDepart vers Sommet de n� uIdArrivee).
	 * OU renvoie une erreur s'il existe d�j� un arc dirig� entre les deux sommets (c�d de Sommet de n� uIdDepart vers Sommet de n� uIdArrivee)
	 * 
	 * \param uIdDepart Le num�ro du sommet de d�part
	 * \param uIdArrivee Le num�ro du sommet d'arriv�
	 */
	void GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee);

	

	/*!
	 * D�lie deux sommets du graphe (supprime l'arc Sommet de n� uIdDepart vers Sommet de n� uIdArrivee). 
	 * OU renvoie une erreur si l'arc n'existe pas
	 * 
	 * \param uIdDepart Le num�ro du sommet de d�part
	 * \param uIdArrivee Le num�ro du sommet d'arriv�
	 */
	void GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee);


	/*!
	 * Renvoie les num�ros des arcs sortants d'un sommet.
	 * 
	 * \param uId Le numero du sommet dont on veut les arcs sortants
	 * \return Un tableau d'entiers contenant les arcs sortant et en premi�re position le nombre d'�l�ments scann�s.
	 */
	unsigned int * GPHLireArcsS(unsigned int uId);


	/*!
	 * Renvoie les num�ros des arcs arrivants d'un sommet.
	 *
	 * \param uId Le numero du sommet dont on veut les arcs arrivants
	 * \return Un tableau d'entiers contenant les arcs arrivants et en premi�re position le nombre d'�l�ments scann�s.
	 */
	unsigned int * GPHLireArcsA(unsigned int uId);


	/*!
	 * Affiche le sommet de num�ro uId
	 * 
	 * \param uId Le num�ro du sommet � afficher
	 */
	void GPHAfficherSommet(unsigned int uId);
	
	

	/*!
	 * Affiche le graphe
	 * 
	 */
	void GPHAfficherGraphe();


	/*!
	 * Inverse les arcs du graphe : les arcs sortants deviennent arrivants et vice-versa
	 * 
	 * \return Un nouvel objet CGraphe, invers� par rapport � 'objet appelant
	 */
	CGraphe & GPHRenverserGraphe();


	/*!
	 * Surcharge de l'op�rateur =
	 * Copie le contenu de GPHParam dans l'objet appelant
	 *
	 * \param GPHParam L'objet CGraphe � copier
	 * \return Un pointeur sur l'objet appelant, copie de GPHParam
	 */
	CGraphe & operator=(CGraphe & GPHParam);
};

#endif