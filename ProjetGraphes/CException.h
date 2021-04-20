#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <iostream>

#define Erreur_Par_Defaut 0

using namespace std;

class CException
{
	//Attributs
private:
	unsigned int uEXCErreur;

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
	CException(unsigned int uErreur);

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
	*****Sortie : IdErreur
	*****Entraine : n�ant
	*************************************************/
	void EXCSetErreur(unsigned int uErreur);

	/*************************************************
	*****NOM : EXCAfficherMessageErreur
	**************************************************
	*****Affiche dans la sortie standard un message d'erreur appropri�.
	**************************************************
	*****Entr�e : idErreur
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entraine : n�ant
	*************************************************/
	void EXCAfficherMessageErreur(void);
};
#endif