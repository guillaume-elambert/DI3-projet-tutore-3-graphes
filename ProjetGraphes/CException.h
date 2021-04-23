#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <iostream>
#include <string>

#define Erreur_Par_Defaut 0


class CException
{
	//Attributs
private:
	unsigned int uEXCErreur;
	char * sEXCEMessage;

	//Constructeurs
public:

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
	CException();

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
	CException(unsigned int uErreur, const char * sMessage);

	//Destructeurs

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
	~CException();

	//Accesseurs

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
	unsigned int EXCGetErreur(void);

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
	void EXCSetErreur(unsigned int uErreur);

	/*************************************************
	*****NOM : EXCGetMessage
	**************************************************
	*****Accesseur en lecture du message d'erreur
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : sEXCEMessage
	*****Entraine : n�ant
	*************************************************/
	const char * EXCGetMessage(void);

	/*************************************************
	*****NOM : EXCSetMessage
	**************************************************
	*****Accesseur en �criture du message d'erreur
	**************************************************
	*****Entr�e : std::string sMessage le nouveau message d'erreur.
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entraine : n�ant
	*************************************************/
	void EXCSetMessage(const char * sMessage);
};
#endif