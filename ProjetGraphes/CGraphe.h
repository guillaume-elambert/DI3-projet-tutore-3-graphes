#ifndef CGRAPHE_H
#define CGRAPHE_H

#include "CSommet.h"
#include "CException.h"
#include "CParser.h"

#define Erreur_Graphe_Defaut 30
#define Erreur_Syntaxe 31
#define Sommet_Inconnu 32
#define Sommet_Existant 33
#define Arc_Inconnu 34
#define Arc_Existant 35

class CGraphe
{
private :

	CSommet * pSOMGPHListeSommet;
	unsigned int uGPHTailleLSom;
	unsigned int uGPHMaxIdSommet;

protected :

	/*************************************************
	*****NOM : GPHChercherSommet
	**************************************************
	*****Cherche si le somemt existe
	**************************************************
	*****Entr�e : Un numero de sommet
	*****N�cessite : n�ant
	*****Sortie : l'index du numero du sommet
	OU -1 si non trouv�
	*****Entra�ne : /
	*************************************************/
	int GPHChercherSommet(unsigned int uId);

public:

	/*************************************************
	*****NOM : CGraphe
	**************************************************
	*****Constructeur par d�faut
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Cr�ation d'un graphe vide et correctement initialis�.
	*************************************************/
	CGraphe(void);

	/*************************************************
	*****NOM : CGraphe
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entr�e : CGraphe & GPHParam
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Creation d'un nouveau graphe copie de GPHParam.
	*************************************************/
	CGraphe(CGraphe & GPHParam);

	/*************************************************
	*****NOM : CGraphe
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entr�e : sChemin, le chemin vers le fichier d'initialisation.
	*****N�cessite : Le fichier contenu dans sChemin est d'un format correcte.
	*****Sortie : n�ant
	*****Entra�ne : Cr�ation d'un graphe vide et correctement initialis� � partir du fichier stock� dans sChemin.
	OU Une bonne erreur des famille si le chemin ou le fichier est mauvais
	*************************************************/
	CGraphe(const CString & STRString);

	/*************************************************
	*****NOM : ~CGraphe
	**************************************************
	*****Destructeur par d�faut
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Le graphe est pr�t � �tre d�sallou� et ses ressources sont d�sallou�es.
	*************************************************/
	~CGraphe(void);

	/*************************************************
	*****NOM : GPHAjouterSommet
	**************************************************
	*****Ajoute un nouveau sommet dans le graphe.
	**************************************************
	*****Entr�e : Le numero du nouveau sommet
	*****N�cessite : n�ant
	*****Sortie : L'Id du nouveau sommet.
	*****Entra�ne : Un nouveau sommet est cr�� dans le graphe.
	*************************************************/
	unsigned int GPHAjouterSommet(unsigned int uNumero);

	/*************************************************
	*****NOM : GPHSupprimerSommet
	**************************************************
	*****Supprime un sommet dans le graphe.
	**************************************************
	*****Entr�e : SOMSommet un sommet du graphe.
	*****N�cessite : SOMSommet est un sommet du graphe.
	*****Sortie : n�ant
	*****Entra�ne : Supprime SOMSOmmet du graphe ainsi que tout les liens avec les autres sommets.
	**************************************************/

	void GPHSupprimerSommet(unsigned int uId);

	/*************************************************
	*****NOM : GPHLierSommets
	**************************************************
	*****Lie deux sommets du graphe.
	**************************************************
	*****Entr�e : CSommet SOMDepart, CSommet SOMArrivee.
	*****N�cessite : SOMDepart & SOMArrivee sont deux sommets du graphe.
	*****Sortie : n�ant
	*****Entra�ne : Les deux sommets sont li�s par un nouvel arc.
	*************************************************/
	void GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee);

	/*************************************************
	*****NOM : GPHDelierSommets
	**************************************************
	*****D�lie deux sommets du graphe.
	**************************************************
	*****Entr�e : CSommet SOMDepart, CSommet SOMArrivee.
	*****N�cessite : SOMDepart & SOMArrivee sont deux sommets li�s du graphe.
	*****Sortie : n�ant
	*****Entra�ne : Les deux sommets ne sont plus li�s par un nouvel arc.
	*************************************************/
	void GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee);

	/*************************************************
	*****NOM : GPHLireArcsS
	**************************************************
	*****Renvoie les id des arcs sortants d'un sommet.
	**************************************************
	*****Entr�e : unsigned int uId, le sommet � lire.
	*****N�cessite : Le sommet est dans le graphe.
	*****Sortie : Un tableau d'entier naturel contenant en premi�re position le nombre d'�l�ments scann�s. Sa taille sera donc de Tableau[0] + 1.
	*****Entra�ne : /
	*************************************************/
	unsigned int * GPHLireArcsS(unsigned int uId);

	/*************************************************
	*****NOM : GPHLireArcsA
	**************************************************
	*****Renvoie les id des arcs arrivants d'un sommet.
	**************************************************
	*****Entr�e : unsigned int uId, le sommet � lire.
	*****N�cessite : Le sommet est dans le graphe.
	*****Sortie : Un tableau d'entier naturel contenant en premi�re position le nombre d'�l�ments scann�s. Sa taille sera donc de Tableau[0] + 1.
	*****Entra�ne : /
	*************************************************/
	unsigned int * GPHLireArcsA(unsigned int uId);

	/*************************************************
	*****NOM : GPHAfficherSommet
	**************************************************
	*****Affiche le sommet
	**************************************************
	*****Entr�e : id du sommet
	*****N�cessite : cet id est valable
	*****Sortie : n�ant
	*****Entra�ne : L'affichage des sommets du graphes
	*************************************************/
	void GPHAfficherSommet(unsigned int uId);
	
	/*************************************************
	*****NOM : GPHAfficherGraphe
	**************************************************
	*****Affiche le graphez
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : L'affichage des sommets du graphes
	*************************************************/
	void GPHAfficherGraphe();

	/*************************************************
	*****NOM : GPHRenverserGraphe
	**************************************************
	*****Renverse le graphe.
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : Un nouveau graphe invers� par rapport � cet objet.
	*****Entra�ne : /
	*************************************************/
	CGraphe & GPHRenverserGraphe();

	/*************************************************
	*****NOM : CGraphe
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entr�e : CGraphe & GPHParam
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Creation d'un nouveau graphe copie de GPHParam.
	*************************************************/
	CGraphe & operator=(CGraphe & GPHParam);

	bool GPHLiees(unsigned int uSommetDep, unsigned int uSommetArr);
};

#endif