#include "CGraphe.h"


/*!
 * Constructeur par d�faut
 *
 */
CGraphe::CGraphe(void)
{
	pSOMGPHListeSommet = new CSommet[0];
	uGPHTailleLSom = 0;
}


/*!
 * Constructeur de recopie
 *
 * \param GPHParam L'objet CGraphe � copier
 */
CGraphe::CGraphe(CGraphe & GPHParam) {

	uGPHTailleLSom = GPHParam.uGPHTailleLSom;
	pSOMGPHListeSommet = new CSommet[GPHParam.uGPHTailleLSom];
	unsigned int uBoucle;
	
	//On copie la liste des sommets de GPHParam
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		pSOMGPHListeSommet[uBoucle] = GPHParam.pSOMGPHListeSommet[uBoucle];
	}
}


/*!
 * Constructeur de confort
 * Cr�ation d'un graphe correctement initialis� � partir d'une ch�ane de caract�re.
 * OU Une erreur si contenu est mal formatt� ou qu'il contient des incoh�rences ou des erreurs.
 *
 * \param cpContenu La cha�ne de caract�re utilis�e pour initialiser l'objet CGraphe
 */
CGraphe::CGraphe(const char *cpContenu)
{

	//Initialisation par d�faut
	pSOMGPHListeSommet = new CSommet[0];
	uGPHTailleLSom = 0;

	char sExceptionMessage[] = "";
	
	std::string sRegexResult;
	std::regex rRegex("NBSommets[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\nNBArcs[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\nSommets[ \\t]*=[ \\t]*(\\[)[ \\t]*\\n((?:Numero[ \\t]*=[ \\t]*[0-9]+\\n)*)\\][ \\t]*\\nArcs[ \\t]*=[ \\t]*(\\[)[ \\t]*\\n((?:Debut[ \\t]*=[ \\t]*[0-9]+[ \\t]*,[ \\t]*Fin[ \\t]*=[ \\t]*([0-9]+)[ \\t]*\\n)*)\\]\\s*");
	//std::regex rRegex("NBSommets=([0-9]+)\\nNBArcs=([0-9]+)\\nSommets=(\\[)\\n((?:Numero=[0-9]+\\n)*)\\]\\nArcs=(\\[)\\n((?:Debut=[0-9]+, Fin=([0-9]+)\\n)*)\\]");
	std::cmatch cmMatchGlobal, cmMatchNumeric;

	int iNbSommets, iNbArcs;
	int iNbInit = 0;

	std::regex rNumericRegex("[0-9]+");

	//Entr�e : Le fichier correspond � l'expression r�guli�re
	//Sinon  : On renvoie une erreur
	if (std::regex_match(cpContenu, cmMatchGlobal, rRegex)) {

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
						sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpContenu) : %d sommets attendus %d sommets obtenus\n", iNbSommets, iCurrentResIndex);
						throw CException(Erreur_NbArcs, sExceptionMessage);
					}
					//Entr�e : le nombre d'arcs d�finit est diff�rent que celui trouv�
					else if (iNbInit == 2 && (iCurrentResIndex /= 2) != iNbArcs) {
						sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpContenu) : %d arcs attendus %d arcs obtenus\n", iNbArcs, iCurrentResIndex);
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

					//Entr�e : On a d�fini un nombre de sommets � 0 pourtant on � defini des arcs
					//		=> On renvoie une erreur
					if (iNbSommets == 0 && iNbArcs != 0) {
						throw CException(Erreur_NbArcs, "CGraphe::CGraphe(const char *cpContenu) : Le nombre de sommets a �t� d�fini sur 0, le nombre d'arcs devrait l'�tre aussi.\n");
					}


					//Entr�e : On a d�passer le nombre de possibilit� totale de laision entre les sommets
					//		=> On renvoie une erreur
					if ( iNbArcs > std::pow(iNbSommets,2) - iNbSommets) {
						sprintf_s(sExceptionMessage, 255, "CGraphe::CGraphe(const char *cpContenu) : Top d'arcs a initialiser, %d maximum .\n", (int)(std::pow(iNbSommets, 2) - iNbSommets));
						throw CException(Erreur_NbArcs, sExceptionMessage);
					}

					break;
				}
				break;
			}
		}
	}
	else {
		throw CException(Erreur_Syntaxe, "CGraphe::CGraphe(const char *cpContenu) : La cha�ne de caract�res ne correspond pas au format attendu\n");
	}

}


/*!
 * Destructeur par d�faut
 *
 */
CGraphe::~CGraphe(void)
{
	delete[] pSOMGPHListeSommet;
}



/*!
 * Cherche si le sommet existe
 *
 * \param uId Un numero de sommet
 * \return L'index du sommet cherch�
 */
int CGraphe::GPHChercherSommet(unsigned int uId)
{
	unsigned int uBoucle;
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		if (pSOMGPHListeSommet[uBoucle].SOMGetId() == uId) {
			return(uBoucle);
		}
	}
	return -1;
}


/*!
 * Ajoute un nouveau sommet dans le graphe.
 * OU renvoie une erreur si le sommet existe d�j�
 *
 * \param uNumero Le num�ro du nouveau sommet charch�.
 * \return L'index du sommet cr��
 */
unsigned int CGraphe::GPHAjouterSommet(unsigned int uNumero)
{

	//Entr�e : Le sommet existe d�j� dans le graphe
	//		=> On renvoie une erreurs
	if (GPHChercherSommet(uNumero) != -1) {
		char sExceptionMessage[] = "";
		sprintf_s(sExceptionMessage, 255, "CGraphe::GPHAjouterSommet(unsigned int uNumero) : Le sommet numero %d existe deja.\n", uNumero);
		throw CException(Sommet_Existant, sExceptionMessage);
	}

	CSommet SOMNouveauSommet(uNumero);

	//Nouveau tableau � assigner � pSOMGPHListeSommet
	CSommet * pSOMNouvelleListe = new CSommet[uGPHTailleLSom + 1];
	unsigned int uBoucle;

	//On copier la valeur de tous les sommets existants
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		pSOMNouvelleListe[uBoucle] = pSOMGPHListeSommet[uBoucle];
	}

	//On ajoute le nouveau sommet
	pSOMNouvelleListe[uGPHTailleLSom] = SOMNouveauSommet;

	delete[] pSOMGPHListeSommet;
	pSOMGPHListeSommet = pSOMNouvelleListe;

	uGPHTailleLSom++;
	return uGPHTailleLSom - 1;
}


/*!
 * Supprime un sommet dans le graphe.
 * Supprime le sommet de numero uId du graphe ainsi que tout ses liens avec les autres sommets.
 * OU renvoie une erreur si le sommet n'existe pas
 *
 * \param uId Num�ro du sommet � supprimer
 */
void CGraphe::GPHSupprimerSommet(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);

	//Entr�e : le sommet cherch� existe
	if (iPos != -1) {

		//On supprime tous les arcs (arrivants et partant) du sommet
		for (unsigned uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
			GPHDelierSommets(uId, uBoucle);
			GPHDelierSommets(uBoucle, uId);
		}

		CSommet * pSOMNouvelleListe = new CSommet[uGPHTailleLSom - 1];

		//On copie tous les autres sommets dans un nouveau tableau
		for (unsigned uBoucle = 0, uCounter = 0; uBoucle < uGPHTailleLSom; uBoucle++) {

			//Ajoute le sommet dans la nouvelle liste s'il ce n'est pas celui � supprimer
			if (pSOMGPHListeSommet[uBoucle].SOMGetId() != uId) {
				pSOMNouvelleListe[uCounter] = pSOMGPHListeSommet[uBoucle];
				uCounter++;
			}
		}

		delete[] pSOMGPHListeSommet;
		pSOMGPHListeSommet = pSOMNouvelleListe;
		
		uGPHTailleLSom--;
	}
}


/*!
 * V�rifie si deux sommets sont li�s dans le sens sommet n� uSommetDep vers sommet n� uSommetArr
 *
 * \param uSommetDep Le sommet de d�part
 * \param uSommetArr Le sommet d'arriv�
 * \return true si les deux sommets sons li�s dans le sens sommet n� uSommetDep vers sommet n� uSommetArr false sinon
 */
bool CGraphe::GPHLiees(unsigned int uSommetDep, unsigned int uSommetArr)
{
	//Entr�e : les deux sommets existent dans le graphe
	if (GPHChercherSommet(uSommetDep) != -1 && GPHChercherSommet(uSommetArr) != -1) {
		//On renvoie true s'ils sont li�s, false sinon
		return(pSOMGPHListeSommet[GPHChercherSommet(uSommetDep)].SOMLies(pSOMGPHListeSommet[GPHChercherSommet(uSommetArr)]));
	}

	return false;
}


/*!
 * Lie deux sommets du graphe (cr�� l'arc Sommet de n� uIdDepart vers Sommet de n� uIdArrivee).
 * OU renvoie une erreur s'il existe d�j� un arc dirig� entre les deux sommets (c�d de Sommet de n� uIdDepart vers Sommet de n� uIdArrivee)
 *
 * \param uIdDepart Le num�ro du sommet de d�part
 * \param uIdArrivee Le num�ro du sommet d'arriv�
 */
void CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee)
{
	char sExceptionMessage[] = "";

	//Entr�e : Pas de tentative de relier un sommet avec lui-m�me
	//Sinon  : On renvoie une erreur
	if (uIdDepart != uIdArrivee) {
		int iPosDep;
		int iPosArr = GPHChercherSommet(uIdArrivee);

		//Entr�e : Le sommet d'arriv�e existe dans le graphe
		//Sinon  : On renvoie une erreur
		if (iPosArr != -1)
		{
			iPosDep = GPHChercherSommet(uIdDepart);

			//Le sommet de d�part existe dans le graphe
			//Sinon  : On renvoie une erreur
			if (iPosDep != -1) {

				//Entr�e : Il existe d�j� un arc dans le sens Sommet de n� uIdDepart vers Sommet de n� uIdArrivee
				//		=> On renvoie une erreur
				if (pSOMGPHListeSommet[iPosDep].SOMChercherArcSortant(uIdArrivee) != -1) {
					sprintf_s(sExceptionMessage, 255, "CGraphe::GPHLierSommets(unsigned int uIdDepart, unsigned int uIdArrivee) : L'arc sortant depuis %d vers %d existe deja.\n", uIdDepart, uIdArrivee);
					throw CException(Arc_Existant, sExceptionMessage);
				}

				//On cr�� on arc de d�part dans le sommet de d�part et un d'arriv� dans le sommet d'arriv�
				pSOMGPHListeSommet[iPosDep].SOMAjouterArcSortant(uIdArrivee);
				pSOMGPHListeSommet[iPosArr].SOMAjouterArcArrivant(uIdDepart);
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


/*!
 * D�lie deux sommets du graphe (supprime l'arc Sommet de n� uIdDepart vers Sommet de n� uIdArrivee).
 * OU renvoie une erreur si l'arc n'existe pas
 *
 * \param uIdDepart Le num�ro du sommet de d�part
 * \param uIdArrivee Le num�ro du sommet d'arriv�
 */
void CGraphe::GPHDelierSommets(unsigned int uIdDepart, unsigned int uIdArrivee)
{
	int iPosDep;
	int iPosArr = GPHChercherSommet(uIdArrivee);


	char sExceptionMessage[] = "";

	//Entr�e : le sommet d'arriv� existe dans le graphe
	//Sinon  : On renvoie une erreur
	if (iPosArr != -1){

		iPosDep = GPHChercherSommet(uIdDepart);

		//Entr�e : le sommet de d�part existe dans le graphe
		//Sinon  : On renvoie une erreur
		if (iPosDep != -1) {

			//Entr�e : Les sommets sont bien li�s par un arc dans le sens Sommet de n� uIdDepart vers Sommet de n� uIdArrivee
			if (pSOMGPHListeSommet[iPosDep].SOMLies(pSOMGPHListeSommet[iPosArr]) == true) {
				
				//On cr�� on arc de d�part dans le sommet de d�part et un d'arriv� dans le sommet d'arriv�
				pSOMGPHListeSommet[iPosDep].SOMRetirerArcSortant(uIdArrivee);
				pSOMGPHListeSommet[iPosArr].SOMRetirerArcArrivant(uIdDepart);
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


/*!
 * Renvoie les num�ros des arcs sortants d'un sommet.
 *
 * \param uId Le numero du sommet dont on veut les arcs sortants
 * \return Un tableau d'entiers contenant les arcs sortant et en premi�re position le nombre d'�l�ments scann�s.
 */
unsigned int * CGraphe::GPHLireArcsS(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);

	//Entr�e : Le sommet n'existe pas dans le graphe
	if (iPos == -1) {
		return nullptr;
	}

	//Entr�e : Le sommet n'a pas d'arcs sortants
	if (pSOMGPHListeSommet[iPos].SOMGetTailleS() == 0) {
		return nullptr;
	}

	unsigned int uBoucle;
	unsigned int * puTableau = new unsigned int[pSOMGPHListeSommet[iPos].SOMGetTailleS() + 1];
	
	//On parcourt tous les arcs sortants du sommet et on les met dans le tableau � retourner
	for (uBoucle = 1; uBoucle < pSOMGPHListeSommet[iPos].SOMGetTailleS() + 1; uBoucle++) {
		puTableau[uBoucle] = pSOMGPHListeSommet[iPos].SOMLireListeS(uBoucle).ARCGetDestination();
	}

	//On stock � l'indice 0 le nombre d'arcs dans le tableau � retourner
	puTableau[0] = pSOMGPHListeSommet[iPos].SOMGetTailleS();
	return puTableau;
}


/*!
 * Renvoie les num�ros des arcs arrivants d'un sommet.
 *
 * \param uId Le numero du sommet dont on veut les arcs arrivants
 * \return Un tableau d'entiers contenant les arcs arrivants et en premi�re position le nombre d'�l�ments scann�s.
 */
unsigned int * CGraphe::GPHLireArcsA(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);

	//Entr�e : Le sommet n'existe pas dans le graphe
	if (iPos == -1) {
		return nullptr;
	}

	//Entr�e : Le sommet n'a pas d'arcs arrivants
	if (pSOMGPHListeSommet[iPos].SOMGetTailleA() == 0) {
		return nullptr;
	}

	unsigned int uBoucle;
	unsigned int * puTableau = new unsigned int[pSOMGPHListeSommet[iPos].SOMGetTailleA() + 1];

	//On parcourt tous les arcs arrivants du sommet et on les met dans le tableau � retourner
	for (uBoucle = 1; uBoucle < pSOMGPHListeSommet[iPos].SOMGetTailleA() + 1; uBoucle++) {
		puTableau[uBoucle] = pSOMGPHListeSommet[iPos].SOMLireListeA(uBoucle).ARCGetDestination();
	}

	//On stock � l'indice 0 le nombre d'arcs dans le tableau � retourner
	puTableau[0] = pSOMGPHListeSommet[iPos].SOMGetTailleA();
	return puTableau;
}


/*!
 * Affiche le sommet de num�ro uId
 *
 * \param uId Le num�ro du sommet � afficher
 */
void CGraphe::GPHAfficherSommet(unsigned int uId)
{
	int iPos = GPHChercherSommet(uId);

	//Entr�e : Le sommet existe dans le graphe
	//Sinon  : On renvoie une erreur
	if (iPos != -1) {
		pSOMGPHListeSommet[iPos].SOMAfficherSommet();
	}
	else {
		char sExceptionMessage[] = "";
		printf_s(sExceptionMessage, 255, "Le sommet %d n'est pas dans le graphe.\n", uId);
		throw CException(Sommet_Inconnu, sExceptionMessage);
	}
}


/*!
 * Affiche le graphe
 *
 */
void CGraphe::GPHAfficherGraphe()
{
	std::cout << "Nb sommets : " << uGPHTailleLSom << std::endl;
	unsigned int uBoucle;

	//On affiche tous les sommets
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		pSOMGPHListeSommet[uBoucle].SOMAfficherSommet();
	}
	std::cout << std::endl;
}


/*!
 * Inverse les arcs du graphe : les arcs sortants deviennent arrivants et vice-versa
 *
 * \return Un nouvel objet CGraphe, invers� par rapport � 'objet appelant
 */
CGraphe & CGraphe::GPHRenverserGraphe() {
	CGraphe * GPHGrapheRenv = new CGraphe(*this);
	unsigned int uBoucle;

	//On inverse les arcs pour chaque sommet
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		GPHGrapheRenv->pSOMGPHListeSommet[uBoucle].SOMInverser();
	}
	return *GPHGrapheRenv;
}


/*!
 * Surcharge de l'op�rateur =
 * Copie le contenu de GPHParam dans l'objet appelant
 *
 * \param GPHParam
 * \return Un pointeur sur l'objet appelant, copie de GPHParam
 */
CGraphe & CGraphe::operator=(CGraphe & GPHParam)
{
	delete[] pSOMGPHListeSommet;
	uGPHTailleLSom = GPHParam.uGPHTailleLSom;
	pSOMGPHListeSommet = new CSommet[GPHParam.uGPHTailleLSom];
	unsigned int uBoucle;

	//On copie la liste des sommets de GPHParam
	for (uBoucle = 0; uBoucle < uGPHTailleLSom; uBoucle++) {
		pSOMGPHListeSommet[uBoucle] = GPHParam.pSOMGPHListeSommet[uBoucle];
	}

	return *this;
}
