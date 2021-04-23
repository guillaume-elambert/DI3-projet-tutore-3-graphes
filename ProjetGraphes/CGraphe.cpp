#include "CGraphe.h"



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
CGraphe::CGraphe(const char *cpChemin)
{

	//Initialisation par d�faut
	pSOMGPHListeSommet = new CSommet[0];
	uGPHMaxIdSommet = 0;
	uGPHTailleLSom = 0;

	char sExceptionMessage[] = "";

	std::string sFileContent(""), sBuffer;
	std::fstream FILfichier(cpChemin);

	if (FILfichier.is_open())
	{
		while (std::getline(FILfichier, sBuffer)) {
			//On concat�ne la ligne courrante avec les lignes pr�c�dentes
			//On ajoute on retour � la ligne si la ligne courrante n'est pas la derni�re du fichier
			sFileContent += sBuffer + (!FILfichier.eof() ? "\n" : "");
		}

	}
	else {
		FILfichier.close();
		sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpChemin) : Impossible d'ouvrir le fichier \"%s\"\n", cpChemin);
		throw CException(Ouverture_Fichier_Impossible, sExceptionMessage);
	}

	FILfichier.close();
	const char *cpInput = sFileContent.c_str();

	std::string sRegexResult;
	std::regex rRegex("NBSommets[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\nNBArcs[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\nSommets[ \\t]*=[ \\t]*(\\[)[ \\t]*\\n((?:Numero[ \\t]*=[ \\t]*[0-9]+\\n)*)\\][ \\t]*\\nArcs[ \\t]*=[ \\t]*(\\[)[ \\t]*\\n((?:Debut[ \\t]*=[ \\t]*[0-9]+[ \\t]*,[ \\t]*Fin[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\n)*)\\]\\s*");
	//std::regex rRegex("NBSommets=([0-9]+)\\nNBArcs=([0-9]+)\\nSommets=(\\[)\\n((?:Numero=[0-9]+\\n)*)\\]\\nArcs=(\\[)\\n((?:Debut=[0-9]+, Fin=([0-9]+)\\n)*)\\]");
	std::cmatch cmMatchGlobal, cmMatchNumeric;

	int iNbSommets, iNbArcs;
	int iNbInit = 0;

	std::regex rNumericRegex("[0-9]+");

	//Entr�e : Le fichier correspond � l'expression r�guli�re
	if (std::regex_match(cpInput, cmMatchGlobal, rRegex)) {

		//On parcourt l'ensemble des r�sultats des groupes de capture du fichier
		for (unsigned uiRegexIndex = 1; uiRegexIndex < cmMatchGlobal.size(); ++uiRegexIndex) {
			sRegexResult = cmMatchGlobal[uiRegexIndex].str();

			//On v�rifie si la ligne suivante est une initialisation du contenu
			switch (sRegexResult[sRegexResult.length() - 1]) {
			case '[':

				++iNbInit;

				//Entr�e : Il y a bien un r�sultat de la recherche regex apr�s celui courrant
				//V�rification normalement inutile car regex_match a renvoy� true
				if (++uiRegexIndex < cmMatchGlobal.size()) {

					sRegexResult = cmMatchGlobal[uiRegexIndex].str();

					int iCurrentResIndex = 0, iResValue, iTempInitValue;

					//On parcourt la zone d'initialisation
					while (std::regex_search(sRegexResult.c_str(), cmMatchNumeric, rNumericRegex)) {

						//On r�cup�re la valeur du sommet/de l'arc
						iResValue = atoi(cmMatchNumeric.str().c_str());

						//Entr�e : On est dans la partie d'initialisation des sommets
						//		=> On ajoute le sommet
						if (iNbInit == 1) {
							this->GPHAjouterSommet(iResValue);
						}
						//Entr�e : On est dans la partie d'initialisation des arcs
						else {
							//Entr�e : On est sur un idex pair (c�d on est sur un d�but)
							//		=> On stock la valeur pour la r�utiliser quand on sera sur une fin de l'arc
							if (iCurrentResIndex % 2 == 0) {
								iTempInitValue = iResValue;
							}
							else {
								//On relie les deux sommets
								this->GPHLierSommets(iTempInitValue, iResValue);
							}
						}

						//On passe � la suite de la cha�ne
						sRegexResult = cmMatchNumeric.suffix();
						++iCurrentResIndex;
					}

					//Entr�e : le nombre de sommets d�finit est diff�rent que celui trouv�
					if (iNbInit == 1 && iCurrentResIndex != iNbSommets) {
						sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpChemin) : %d sommets attendus %d sommets obtenus\n", iNbSommets, iCurrentResIndex);
						throw CException(Erreur_NbArcs, sExceptionMessage);
					}
					//Entr�e : le nombre d'arcs d�finit est diff�rent que celui trouv�
					else if (iNbInit == 2 && (iCurrentResIndex /= 2) != iNbArcs) {
						sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpChemin) : %d arcs attendus %d arcs obtenus\n", iNbArcs, iCurrentResIndex);
						throw CException(Erreur_NbArcs, sExceptionMessage);
					}
				}

				break;

			default:
				switch (uiRegexIndex) {

				case 1:
					//printf("Le nombre de sommets est de : %s\n", sRegexResult.c_str());
					iNbSommets = atoi(sRegexResult.c_str());
					break;

				case 2:
					//printf("Le nombre d'arcs est de : %s\n", sRegexResult.c_str());
					iNbArcs = atoi(sRegexResult.c_str());

					if (iNbSommets == 0 && iNbArcs != 0) {
						throw CException(Erreur_NbArcs, "CGraphe::CGraphe(const char *cpChemin) : Le nombre de sommets a �t� d�fini sur 0, le nombre d'arcs devrait l'�tre aussi.\n");
					}

					if ( iNbArcs > std::pow(iNbSommets,2) - iNbSommets) {
						sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpChemin) : Top d'arcs a initialiser, %d maximum .\n", (int)(std::pow(iNbSommets, 2) - iNbSommets));
						throw CException(Erreur_NbArcs, sExceptionMessage);
					}

					break;
				}
				break;
			}
		}
	}
	else {
		throw CException(Ouverture_Fichier_Impossible, "CGraphe::CGraphe(const char *cpChemin) : Impossible d'ouvrir le fichier\n");
	}

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
	if (GPHChercherSommet(uNumero) != -1) {
		char sExceptionMessage[] = "";
		sprintf_s(sExceptionMessage, 255, "CGraphe::GPHAjouterSommet(unsigned int uNumero) : Le sommet numero %d existe deja.\n", uNumero);
		throw CException(Sommet_Existant, sExceptionMessage);
	}

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
	char sExceptionMessage[] = "";

	if (uIdDepart != uIdArrivee) {
		int iPosDep = GPHChercherSommet(uIdDepart);
		int iPosArr = GPHChercherSommet(uIdArrivee);
		if (iPosArr != -1)
		{
			if (iPosDep != -1) {
				if (pSOMGPHListeSommet[iPosDep].SOMChercherArcSortant(uIdArrivee) != -1) {
					sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : L'arc sortant depuis %d vers %d existe deja.\n", uIdDepart, uIdArrivee);
					throw CException(Arc_Existant, sExceptionMessage);
				}

				CArc ARCNArcA(uIdArrivee);
				CArc ARCNArcD(uIdDepart);
				pSOMGPHListeSommet[iPosDep].SOMAjouterArcSortant(ARCNArcA);
				pSOMGPHListeSommet[iPosArr].SOMAjouterArcArrivant(ARCNArcD);
			}
			else {
				sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Le sommet de depart %d est inconnu.\n", uIdDepart);
				throw CException(Sommet_Inconnu, sExceptionMessage);
			}
		}
		else
		{
			sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Le sommet d'arrivee %d est inconnu.\n", uIdArrivee);
			throw CException(Sommet_Inconnu, sExceptionMessage);
		}
	}
	else {
		sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Tentative de relier le sommet %d avec lui-meme.\n", uIdArrivee);
		throw CException(Auto_Referencement, sExceptionMessage);
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

	std::cout << pSOMGPHListeSommet[iPosDep].SOMLies(pSOMGPHListeSommet[iPosArr]) << std::endl;

	char sExceptionMessage[] = "";

	if (iPosArr != -1){
		if (iPosDep != -1) {
			if (pSOMGPHListeSommet[iPosDep].SOMLies(pSOMGPHListeSommet[iPosArr]) == true) {
				CArc ARCNArcA(uIdArrivee);
				CArc ARCNArcD(uIdDepart);
				pSOMGPHListeSommet[iPosDep].SOMRetirerArcSortant(ARCNArcA);
				pSOMGPHListeSommet[iPosArr].SOMRetirerArcArrivant(ARCNArcD);
			}
		}
		else {
			sprintf_s(sExceptionMessage, 255, "CGraphe::GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Le sommet de depart %d est inconnu.\n", uIdDepart);
			throw CException(Sommet_Inconnu, sExceptionMessage);
		}
	}
	else
	{
		sprintf_s(sExceptionMessage, 255, "CGraphe::GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : Le sommet d'arrivee %d est inconnu.\n", uIdArrivee);
		throw CException(Sommet_Inconnu, sExceptionMessage);
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
		char sExceptionMessage[] = "";
		printf_s(sExceptionMessage, 255, "Le sommet %d n'est pas dans le graphe.\n", uId);
		throw CException(Sommet_Inconnu, sExceptionMessage);
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
	std::cout << "Nb sommets : " << uGPHTailleLSom << std::endl;
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++)
		pSOMGPHListeSommet[uBoucle].SOMAfficherSommet();
	std::cout << std::endl;
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
