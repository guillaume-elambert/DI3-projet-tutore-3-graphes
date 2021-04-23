#include "CException.h"

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
*****Entr�e : unsiged int uErreur le code d'erreur et char * sMessage le message d'erreur
*****N�cessite : n�ant
*****Sortie : n�ant
*****Entraine : n�ant
*************************************************/
CException::CException(unsigned int uErreur, const char * sMessage)
{
	uEXCErreur = uErreur;
	sEXCEMessage = _strdup(sMessage);
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
	delete[] sEXCEMessage;
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

const char * CException::EXCGetMessage(void)
{
	return sEXCEMessage;
}

void CException::EXCSetMessage(const char * sMessage)
{
	sEXCEMessage = _strdup(sMessage);
}

