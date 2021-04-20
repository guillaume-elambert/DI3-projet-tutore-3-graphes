#ifndef CEXCEPTION_H
#include "CException.h"
#endif
/*************************************************
*****NOM : CException
**************************************************
*****Constructeur par d�faut
**************************************************
*****Entr�e : n�ant
*****N�cessite : n�ant
*****Sortie : n�ant
*****Entraine : n�ant
*************************************************/
CException::CException()
{
	uEXCErreur = Erreur_Par_Defaut;
}

/*************************************************
*****NOM : CException
**************************************************
*****Constructeur de confort
**************************************************
*****Entr�e : unsiged int uErreur le code d'erreur.
*****N�cessite : n�ant
*****Sortie : n�ant
*****Entraine : n�ant
*************************************************/
CException::CException(unsigned int uErreur)
{
	uEXCErreur = uErreur;
}

/*************************************************
*****NOM : ~CException
**************************************************
*****Destructeur par d�faut
**************************************************
*****Entr�e : n�ant
*****N�cessite : n�ant
*****Sortie : n�ant
*****Entraine : n�ant
*************************************************/
CException::~CException()
{

}

/*************************************************
*****NOM : EXCGetErreur
**************************************************
*****Accesseur en lecture du code d'erreur
**************************************************
*****Entr�e : n�ant
*****N�cessite : n�ant
*****Sortie : uErreur
*****Entraine : n�ant
*************************************************/
unsigned int CException::EXCGetErreur(void)
{
	return uEXCErreur;
}

/*************************************************
*****NOM : EXCSetErreur
**************************************************
*****Accesseur en �criture du code d'erreur
**************************************************
*****Entr�e : unsigned int uErreur le nouveau code d'erreur.
*****N�cessite : n�ant
*****Sortie : n�ant
*****Entraine : n�ant
*************************************************/
void CException::EXCSetErreur(unsigned int uErreur)
{
	uEXCErreur = uErreur;
}

/*************************************************
*****NOM : EXCAfficherMessageErreur
**************************************************
*****Affiche dans la sortie standard un message d'erreur appropri�.
**************************************************
*****Entr�e : n�ant
*****N�cessite : n�ant
*****Sortie : n�ant
*****Entraine : n�ant
*************************************************/
void CException::EXCAfficherMessageErreur(void)
{
	cerr << "Exception : ";
	switch (uEXCErreur) {
		/*Erreur par defaut*/
	case Erreur_Par_Defaut:
		cerr << "Exception par defaut";
		break;

		/*Main*/
	case 1:
		cerr << "Le nombre de param�tres que vous avez pass� est illogique" << endl;
		break;

		/*CSommet*/
	case 2:
		cerr << "L'index de votre sommet n'est pas correct" << endl;
		break;

		/*CGraphe*/
	case 3:
		cerr << "L'arc sp�cifi� existe d�j�" << endl;
		break;
	case 4:
		cerr << "L'arc sp�cifi� n'est pas valable" << endl;
		break;
	case 5:
		cerr << "Le sommet sp�cifi� existe d�j�" << endl;
		break;
	case 6:
		cerr << "Le sommet sp�cifi� n'est pas valable" << endl;
		break;
	case 7:
		cerr << "La grammaire du fichier n'est pas bonne" << endl;
		break;
	case 8:
		cerr << "Erreur par d�faut : CGraphe :" << endl;
		break;

		/*CParser*/
	case 9:
		cerr << "Le parser n'est pas initialis�" << endl;
		break;
	case 10:
		cerr << "Impossible d'ouvrir le fichier" << endl;
		break;

		cerr << endl;
	}
}

