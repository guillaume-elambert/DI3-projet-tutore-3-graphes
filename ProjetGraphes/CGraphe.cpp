#include "CGraphe.h"
#include "CString.h"
#include "CParser.h"
#include "CSommet.h"
#include "CArc.h"

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
int CGraphe::GPHChercherSommet(unsigned int uId)
{
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		if (pSOMGPHListeSommet[uBoucle].SOMGetId() == uId)
			return(uBoucle);
	return -1;
}

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
CGraphe::CGraphe(void)
{
	pSOMGPHListeSommet = new CSommet[0];
	uGPHMaxIdSommet = 0;
	uGPHTailleLSom = 0;
}

CGraphe::CGraphe(CGraphe & GPHParam) {
	uGPHMaxIdSommet = GPHParam.uGPHMaxIdSommet;
	uGPHTailleLSom = GPHParam.uGPHTailleLSom;
	pSOMGPHListeSommet = new CSommet[GPHParam.uGPHTailleLSom];
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		pSOMGPHListeSommet[uBoucle] = GPHParam.pSOMGPHListeSommet[uBoucle];
}

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
CGraphe::CGraphe(const CString & STRString)
{
	unsigned int uIndexBoucle = 0;
	unsigned int uNombreSommets = 0;
	unsigned int uNombreArcs = 0;
	unsigned int uDebutArc = 0;
	unsigned int uFinArc = 0;

	pSOMGPHListeSommet = new CSommet[0];
	uGPHMaxIdSommet = 0;
	uGPHTailleLSom = 0;

	CParser PARParser;
	PARParser.PARInitialiser(STRString);

	/*NombreSommet*/
	if (PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "NBSommets" && PARParser.PARLireValeur() >= 0)
	{
		uNombreSommets = PARParser.PARLireValeur();
	}
	else
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*NBArcs*/
	if (PARParser.PARSuivant() && PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "NBArcs" && PARParser.PARLireValeur() >= 0)
	{
		uNombreArcs = PARParser.PARLireValeur();
	}
	else
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*DebutTableau*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "debutTableau" || PARParser.PARLireNom() != "Sommets")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Ajout des sommets*/
	for (uIndexBoucle = 1; uIndexBoucle <= uNombreSommets; uIndexBoucle++)
	{
		/*Numero*/
		if (PARParser.PARSuivant() && PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "Numero")
		{
			GPHAjouterSommet(PARParser.PARLireValeur());
		}
		else
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}

		/*Saut de ligne*/
		if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}
	}
	/*FinTableau*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "finTableau")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*DebutTableau*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "debutTableau" || PARParser.PARLireNom() != "Arcs")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Ajout des arcs*/
	for (uIndexBoucle = 1; uIndexBoucle <= uNombreArcs; uIndexBoucle++)
	{
		/*Debut*/
		if (PARParser.PARSuivant() && PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "Debut")
		{
			uDebutArc = PARParser.PARLireValeur();
		}
		else
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}

		/*Virgule*/
		if (!PARParser.PARSuivant() || PARParser.PARLireType() != "virgule")
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}

		/*Fin*/
		if (PARParser.PARSuivant() && PARParser.PARLireType() == "entier" && PARParser.PARLireNom() == "Fin")
		{
			uFinArc = PARParser.PARLireValeur();
			GPHLierSommets(uDebutArc, uFinArc);
		}
		else
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}

		/*Saut de ligne*/
		if (!PARParser.PARSuivant() || PARParser.PARLireType() != "saut")
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}
	}
	/*FinTableau*/
	if (!PARParser.PARSuivant() || PARParser.PARLireType() != "finTableau")
	{
		PARParser.PARFinaliser();
		throw CException(Erreur_Syntaxe);
	}

	/*Saut de ligne*/
	while (PARParser.PARSuivant())
	{
		if (PARParser.PARLireType() != "saut")
		{
			PARParser.PARFinaliser();
			throw CException(Erreur_Syntaxe);
		}
	}
	PARParser.PARFinaliser();
}

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
CGraphe::~CGraphe(void)
{
	delete[] pSOMGPHListeSommet;
}

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
unsigned int CGraphe::GPHAjouterSommet(unsigned int uNumero)
{
	if (GPHChercherSommet(uNumero) != -1)
		throw CException(Sommet_Existant);

	CSommet SOMNouveauSommet(uNumero);
	uGPHMaxIdSommet++;

	if (uGPHTailleLSom == 0) {
		delete[] pSOMGPHListeSommet;
		pSOMGPHListeSommet = new CSommet[1];
		pSOMGPHListeSommet[0] = SOMNouveauSommet;
		uGPHTailleLSom++;
	}
	else {
		CSommet * pSOMNouvelleListe = new CSommet[uGPHTailleLSom + 1];
		unsigned int uBoucle;

		for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
			pSOMNouvelleListe[uBoucle] = pSOMGPHListeSommet[uBoucle];

		pSOMNouvelleListe[uGPHTailleLSom] = SOMNouveauSommet;
		delete[] pSOMGPHListeSommet;
		pSOMGPHListeSommet = new CSommet[uGPHTailleLSom + 1];

		for (uBoucle = 0; uBoucle < uGPHTailleLSom + 1; uBoucle++)
			pSOMGPHListeSommet[uBoucle] = pSOMNouvelleListe[uBoucle];

		uGPHTailleLSom++;
	}

	return uGPHMaxIdSommet - 1;
}

/*************************************************
*****NOM : GPHSupprimerSommet
**************************************************
*****Supprime un sommet dans le graphe.
**************************************************
*****Entr�e : SOMSommet un sommet du graphe.
*****N�cessite : SOMSommet est un sommet du graphe.
*****Sortie : n�ant
*****Entra�ne : Supprime SOMSOmmet du graphe ainsi que tout les liens avec les autres sommets.
*************************************************

1/ Si SOM n'existe pas => Exception
2/Chercher tout les sommets li� � SOM
3/Les d�lier
4/Echanger la position de ListeSOM[End] et SOM dans ListeSom.
5/R�allouer ListeSOM � la taille TailleListeSOM - 1
6/FIN
*/
void CGraphe::GPHSupprimerSommet(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);
	if (iPos != -1) {
		unsigned int uBoucle = 0;
		for (uBoucle = 0; uBoucle < uGPHMaxIdSommet; uBoucle++) {
			GPHDelierSommets(uId, uBoucle);
			GPHAfficherGraphe();
			GPHDelierSommets(uBoucle, uId);
			GPHAfficherGraphe();
		}
		CSommet * pSOMNouvelleListe = new CSommet[uGPHTailleLSom - 1];
		unsigned int uCpt = 0;
		for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
			if (pSOMGPHListeSommet[uBoucle].SOMGetId() == uId)
				uBoucle++;
			pSOMNouvelleListe[uCpt] = pSOMGPHListeSommet[uBoucle];
			uCpt++;
		}
		delete[] pSOMGPHListeSommet;
		pSOMGPHListeSommet = new CSommet[uGPHTailleLSom - 1];
		for (uBoucle = 0; uBoucle < uGPHTailleLSom - 1; uBoucle++)
			pSOMGPHListeSommet[uBoucle] = pSOMNouvelleListe[uBoucle];
		delete[] pSOMNouvelleListe;
		uGPHTailleLSom--;
	}
}

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
void CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee)
{
	int iPosDep = GPHChercherSommet(uIdDepart);
	int iPosArr = GPHChercherSommet(uIdArrivee);
	if (iPosArr != -1 && iPosDep != -1)
	{
		if (pSOMGPHListeSommet[iPosDep].SOMChercherArcSortant(uIdArrivee) != -1)
			throw CException(Arc_Existant);

		CArc ARCNArcA(uIdArrivee);
		CArc ARCNArcD(uIdDepart);
		pSOMGPHListeSommet[iPosDep].SOMAjouterArcSortant(ARCNArcA);
		pSOMGPHListeSommet[iPosArr].SOMAjouterArcArrivant(ARCNArcD);
	}
	else
	{
		throw CException(Sommet_Inconnu);
	}
}

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
void CGraphe::GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee)
{
	int iPosDep = GPHChercherSommet(uIdDepart);
	int iPosArr = GPHChercherSommet(uIdArrivee);

	cout << pSOMGPHListeSommet[iPosDep].SOMLies(pSOMGPHListeSommet[iPosArr]) << endl;

	if (iPosArr != -1 && iPosDep != -1 && pSOMGPHListeSommet[iPosDep].SOMLies(pSOMGPHListeSommet[iPosArr]) == true) {
		CArc ARCNArcA(uIdArrivee);
		CArc ARCNArcD(uIdDepart);
		pSOMGPHListeSommet[iPosDep].SOMRetirerArcSortant(ARCNArcA);
		pSOMGPHListeSommet[iPosArr].SOMRetirerArcArrivant(ARCNArcD);
	}
	else
	{
		//throw CException(Sommet_Inconnu);
	}
}

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
unsigned int * CGraphe::GPHLireArcsS(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);
	if (iPos == -1)
		return nullptr;
	if (pSOMGPHListeSommet[iPos].SOMGetTailleS() == 0)
		return nullptr;
	unsigned int uBoucle;
	unsigned int * puTableau = new unsigned int[pSOMGPHListeSommet[iPos].SOMGetTailleS() + 1];
	for (uBoucle = 1; uBoucle < pSOMGPHListeSommet[iPos].SOMGetTailleS() + 1; uBoucle++)
		puTableau[uBoucle] = pSOMGPHListeSommet[iPos].SOMLireListeS(uBoucle).ARCGetDestination();
	puTableau[0] = pSOMGPHListeSommet[iPos].SOMGetTailleS();
	return puTableau;
}


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
unsigned int * CGraphe::GPHLireArcsA(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);
	if (iPos == -1)
		return nullptr;
	if (pSOMGPHListeSommet[iPos].SOMGetTailleA() == 0)
		return nullptr;
	unsigned int uBoucle;
	unsigned int * puTableau = new unsigned int[pSOMGPHListeSommet[iPos].SOMGetTailleA() + 1];
	for (uBoucle = 1; uBoucle < pSOMGPHListeSommet[iPos].SOMGetTailleA() + 1; uBoucle++)
		puTableau[uBoucle] = pSOMGPHListeSommet[iPos].SOMLireListeA(uBoucle).ARCGetDestination();
	puTableau[0] = pSOMGPHListeSommet[iPos].SOMGetTailleA();
	return puTableau;
}

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
void CGraphe::GPHAfficherSommet(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);
	if (iPos != -1) {
		pSOMGPHListeSommet[iPos].SOMAfficherSommet();
	}
	else {
		cout << "Le sommet n'est pas dans le graphe." << endl;
	}
}

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
void CGraphe::GPHAfficherGraphe()
{
	cout << "Nb sommets : " << uGPHTailleLSom << endl;
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		pSOMGPHListeSommet[uBoucle].SOMAfficherSommet();
	cout << endl;
}

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
CGraphe & CGraphe::GPHRenverserGraphe() {
	CGraphe * GPHGrapheRenv = new CGraphe(*this);
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		GPHGrapheRenv->pSOMGPHListeSommet[uBoucle].SOMInverser();
	}
	return *GPHGrapheRenv;
}

CGraphe & CGraphe::operator=(CGraphe & GPHParam)
{
	delete[] pSOMGPHListeSommet;
	uGPHMaxIdSommet = GPHParam.uGPHMaxIdSommet;
	uGPHTailleLSom = GPHParam.uGPHTailleLSom;
	pSOMGPHListeSommet = new CSommet[GPHParam.uGPHTailleLSom];
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		pSOMGPHListeSommet[uBoucle] = GPHParam.pSOMGPHListeSommet[uBoucle];
	return *this;
}

bool CGraphe::GPHLiees(unsigned int uSommetDep, unsigned int uSommetArr)
{
	if (GPHChercherSommet(uSommetDep) != -1 && GPHChercherSommet(uSommetArr) != -1)
		return(pSOMGPHListeSommet[GPHChercherSommet(uSommetDep)].SOMLies(pSOMGPHListeSommet[GPHChercherSommet(uSommetArr)]));
	return false;
}
