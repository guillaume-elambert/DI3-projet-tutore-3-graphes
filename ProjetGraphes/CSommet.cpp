#include "CSommet.h"

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
CSommet::CSommet(void)
{
	pARCSOMListeArcsArrivants = new CArc[0];
	pARCSOMListeArcsSortants = new CArc[0];
	uSOMId = 0;
	uSOMTailleListeA = 0;
	uSOMTailleListeS = 0;
}

/*************************************************
*****NOM : CSommet
**************************************************
*****Constructeur de confort
**************************************************
*****Entr�e : n�ant
*****N�cessite : unsigned int uNid l'Id du Sommet.
*****Sortie : n�ant
*****Entra�ne : Cr�action d'un CSommet d'uSOMId = uNid.
*************************************************/
CSommet::CSommet(unsigned int uNid) {
	pARCSOMListeArcsArrivants = new CArc[0];
	pARCSOMListeArcsSortants = new CArc[0];
	uSOMId = uNid;
	uSOMTailleListeA = 0;
	uSOMTailleListeS = 0;
}

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
CSommet::CSommet(CSommet & SOMParam)
{
	uSOMId = SOMParam.uSOMId;
	uSOMTailleListeA = SOMParam.uSOMTailleListeA;
	uSOMTailleListeS = SOMParam.uSOMTailleListeS;
	pARCSOMListeArcsArrivants = new CArc[SOMParam.uSOMTailleListeA];
	pARCSOMListeArcsSortants = new CArc[SOMParam.uSOMTailleListeS];

	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++)
		pARCSOMListeArcsArrivants[uBoucle] = SOMParam.pARCSOMListeArcsArrivants[uBoucle];
	for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++)
		pARCSOMListeArcsSortants[uBoucle] = SOMParam.pARCSOMListeArcsSortants[uBoucle];
}

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
CSommet::~CSommet(void)
{
	delete[] pARCSOMListeArcsArrivants;
	delete[] pARCSOMListeArcsSortants;
}

/*************************************************
*****NOM : SOMGetId
**************************************************
*****Destructeur par d�faut
**************************************************
*****Entr�e : n�ant
*****N�cessite : n�ant
*****Sortie : n�ant
*****Entra�ne : L'objet est pr�t � �tre d�sallou�.
*************************************************/
unsigned int CSommet::SOMGetId(void) {
	return uSOMId;
}

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
unsigned int CSommet::SOMGetTailleA()
{
	return uSOMTailleListeA;
}

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
unsigned int CSommet::SOMGetTailleS()
{
	return uSOMTailleListeS;
}

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
void CSommet::SOMAjouterArcArrivant(CArc & ARCParam) {

	//Verification qu'il n'y ai pas de doublons
	if (SOMChercherArcArrivant(ARCParam.ARCGetDestination()) == -1) {

		//Si la liste est vide, on l'initialise :
		if (uSOMTailleListeA == 0) {
			delete[] pARCSOMListeArcsArrivants;
			pARCSOMListeArcsArrivants = new CArc[1];
			pARCSOMListeArcsArrivants[0] = ARCParam;
			uSOMTailleListeA++;
		}
		//Sinon, on r�alloue
		else {

			CArc * pARCNouvelleListe = new CArc[uSOMTailleListeA + 2];

			unsigned int uBoucle;
			for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++) {
				pARCNouvelleListe[uBoucle] = pARCSOMListeArcsArrivants[uBoucle];
			}

			pARCNouvelleListe[uSOMTailleListeA] = ARCParam;
			uSOMTailleListeA++;

			delete[] pARCSOMListeArcsArrivants;
			pARCSOMListeArcsArrivants = new CArc[uSOMTailleListeA];


			for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++) {
				pARCSOMListeArcsArrivants[uBoucle] = pARCNouvelleListe[uBoucle];
			}

			delete[] pARCNouvelleListe;
		}
	}

}

/*************************************************
*****NOM : SOMRetirerArcArrivant
**************************************************
*****Retire un arc arrivant.
**************************************************
*****Entr�e : CArc ARCParam
*****N�cessite : ARCParam est dans la liste des arcs arrivant.
*****Sortie : n�ant
*****Entra�ne : La liste des arcs ne contient maintenant plus ARCParam.
*************************************************/
void CSommet::SOMRetirerArcArrivant(CArc & ARCParam) {

	if (uSOMTailleListeA == 1) {
		delete[] pARCSOMListeArcsArrivants;
		pARCSOMListeArcsArrivants = new CArc[0];
		uSOMTailleListeA--;
	}
	else if (SOMChercherArcArrivant(ARCParam.ARCGetDestination()) != -1) {

		CArc * pARCNouvelleListe = new CArc[uSOMTailleListeA - 1];
		unsigned int uBoucle;
		unsigned int uCpt = 0;
		for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++) {
			if (pARCSOMListeArcsArrivants[uBoucle].ARCGetDestination() == ARCParam.ARCGetDestination())
				uBoucle++;
			pARCNouvelleListe[uCpt] = pARCSOMListeArcsArrivants[uBoucle];
			uCpt++;
		}

		for (uBoucle = 0; uBoucle < uSOMTailleListeA - 1; uBoucle++) {
			pARCSOMListeArcsArrivants[uBoucle] = pARCNouvelleListe[uBoucle];
		}
		uSOMTailleListeA--;
	}
}

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
int CSommet::SOMChercherArcArrivant(unsigned int uSOMIdDestination)
{
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++) {
		if (pARCSOMListeArcsArrivants[uBoucle].ARCGetDestination() == uSOMIdDestination)
			return uBoucle;
	}
	return -1;
}

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
CArc CSommet::SOMLireListeA(unsigned int uPos)
{
	if (uPos > uSOMTailleListeA - 1) {
		char sExceptionMessage[] = "";
		sprintf_s(sExceptionMessage, 255, "CSommet::SOMLireListeA(unsigned int uPos) : Impossible de lire l'arc d'arrivee %d.\n", uPos);
		throw CException(Lecture_Impossible, sExceptionMessage);
	}
		
	return pARCSOMListeArcsArrivants[uPos];
}

void CSommet::SOMAjouterArcSortant(CArc & ARCParam)
{

	//Verification qu'il n'y ai pas de doublons
	if (SOMChercherArcSortant(ARCParam.ARCGetDestination()) == -1) {

		//Si la liste est vide, on l'initialise :
		if (uSOMTailleListeS == 0) {
			delete[] pARCSOMListeArcsSortants;
			pARCSOMListeArcsSortants = new CArc[1];
			pARCSOMListeArcsSortants[0] = ARCParam;
			uSOMTailleListeS++;
		}
		//Sinon, on r�alloue
		else {

			CArc * pARCNouvelleListe = new CArc[uSOMTailleListeS + 2];

			unsigned int uBoucle;
			for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++) {
				pARCNouvelleListe[uBoucle] = pARCSOMListeArcsSortants[uBoucle];
			}

			pARCNouvelleListe[uSOMTailleListeS] = ARCParam;
			uSOMTailleListeS++;

			delete[] pARCSOMListeArcsSortants;
			pARCSOMListeArcsSortants = new CArc[uSOMTailleListeS];


			for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++) {
				pARCSOMListeArcsSortants[uBoucle] = pARCNouvelleListe[uBoucle];
			}

			delete[] pARCNouvelleListe;
		}
	}


}

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
void CSommet::SOMRetirerArcSortant(CArc & ARCParam)
{
	if (uSOMTailleListeS == 1) {
		delete[] pARCSOMListeArcsSortants;
		pARCSOMListeArcsSortants = new CArc[0];
		uSOMTailleListeS--;
	}
	else if (SOMChercherArcSortant(ARCParam.ARCGetDestination()) != -1) {

		CArc * pARCNouvelleListe = new CArc[uSOMTailleListeS - 1];
		unsigned int uBoucle;
		for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++) {
			if (pARCSOMListeArcsSortants[uBoucle].ARCGetDestination() == ARCParam.ARCGetDestination())
				uBoucle++;
			pARCNouvelleListe[uBoucle] = pARCSOMListeArcsSortants[uBoucle];
		}

		for (uBoucle = 0; uBoucle < uSOMTailleListeS - 1; uBoucle++) {
			pARCSOMListeArcsSortants[uBoucle] = pARCNouvelleListe[uBoucle];
		}
		uSOMTailleListeS--;
	}
}

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
int CSommet::SOMChercherArcSortant(unsigned int uSOMIdDestination)
{
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++) {
		if (pARCSOMListeArcsSortants[uBoucle].ARCGetDestination() == uSOMIdDestination)
			return uBoucle;
	}
	return -1;
}

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
CArc CSommet::SOMLireListeS(unsigned int uPos)
{
	if (uPos > uSOMTailleListeS - 1) {
		char sExceptionMessage[] = "";
		sprintf_s(sExceptionMessage, 255, "CSommet::SOMLireListeS(unsigned int uPos) : Impossible de lire l'arc de sorti %d.\n", uPos);
		throw CException(Lecture_Impossible, sExceptionMessage);
	}
	return pARCSOMListeArcsSortants[uPos];
}

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
CSommet & CSommet::operator=(const CSommet & SOMParam)
{
	if (this != &SOMParam) {
		uSOMId = SOMParam.uSOMId;
		uSOMTailleListeA = SOMParam.uSOMTailleListeA;
		uSOMTailleListeS = SOMParam.uSOMTailleListeS;
		delete[] pARCSOMListeArcsArrivants;
		delete[] pARCSOMListeArcsSortants;
		pARCSOMListeArcsArrivants = new CArc[SOMParam.uSOMTailleListeA];
		pARCSOMListeArcsSortants = new CArc[SOMParam.uSOMTailleListeS];

		unsigned int uBoucle;
		for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++)
			pARCSOMListeArcsArrivants[uBoucle] = SOMParam.pARCSOMListeArcsArrivants[uBoucle];
		for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++)
			pARCSOMListeArcsSortants[uBoucle] = SOMParam.pARCSOMListeArcsSortants[uBoucle];
	}
	return *this;
}

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
bool CSommet::SOMLies(CSommet & SOMParam)
{
	unsigned int uBoucle;
	unsigned int uValeurTeste = 0;
	for (uBoucle = 0; uBoucle < SOMParam.uSOMTailleListeA; uBoucle++) {
		if (SOMParam.pARCSOMListeArcsArrivants[uBoucle].ARCGetDestination() == SOMGetId()) {
			uValeurTeste++;
		}
	}
	for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++) {
		if (pARCSOMListeArcsSortants[uBoucle].ARCGetDestination() == SOMParam.SOMGetId()) {
			uValeurTeste++;
		}
	}
	if (uValeurTeste == 2)
		return true;
	return false;
}


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
void CSommet::SOMInverser() {
	CArc *ARCTmp = this->pARCSOMListeArcsArrivants;
	unsigned uiNbArrivants = this->uSOMTailleListeA;

	this->pARCSOMListeArcsArrivants = this->pARCSOMListeArcsSortants;
	this->uSOMTailleListeA = this->uSOMTailleListeS;

	this->pARCSOMListeArcsSortants = ARCTmp;
	this->uSOMTailleListeS = uiNbArrivants;

	/*CArc * pARCTmp = new CArc[uSOMTailleListeA];
	unsigned int uBoucle;
	unsigned int uTmp;

	for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++)
		pARCTmp[uBoucle] = pARCSOMListeArcsArrivants[uBoucle];

	delete[] pARCSOMListeArcsArrivants;
	pARCSOMListeArcsArrivants = new CArc[uSOMTailleListeS];

	for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++)
		pARCSOMListeArcsArrivants[uBoucle] = pARCSOMListeArcsSortants[uBoucle];

	delete[] pARCSOMListeArcsSortants;
	pARCSOMListeArcsSortants = new CArc[uSOMTailleListeA];

	for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++)
		pARCSOMListeArcsSortants[uBoucle] = pARCTmp[uBoucle];

	delete[] pARCTmp;
	uTmp = uSOMTailleListeA;
	uSOMTailleListeA = uSOMTailleListeS;
	uSOMTailleListeS = uTmp;*/
}


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
void CSommet::SOMAfficherSommet() {
	unsigned int uBoucle;
	std::cout << "L'ID du sommet est : " << uSOMId << std::endl;
	
	std::cout << "La liste des arcs arrivants est :" << std::endl;
	for (uBoucle = 0; uBoucle < uSOMTailleListeA; uBoucle++)
		std::cout << "\t" << pARCSOMListeArcsArrivants[uBoucle].ARCGetDestination() << ((uBoucle+1) % 3 == 0 ? "\n" : "");

	if (uBoucle % 3 != 0){
		std::cout << std::endl;
	}
	
	std::cout << "La liste des arcs sortants est :" << std::endl;
	for (uBoucle = 0; uBoucle < uSOMTailleListeS; uBoucle++)
		std::cout << "\t" << pARCSOMListeArcsSortants[uBoucle].ARCGetDestination() << ((uBoucle+1) % 3 == 0 ? "\n" : "");
	if (uBoucle % 3 != 0){
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

