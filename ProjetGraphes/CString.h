#ifndef CSTRING_H
#define CSTRING_H

#include <iostream>

#include "CException.h"

#define Erreur_String_Base 60
#define Index_Incompatible 61

using namespace std;

class CString
{
private:
	char * sSTRChaine;
	unsigned int uSTRTaille;
	unsigned int uSTRTailleMemoire;
public:

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur par defaut
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Creation d'un CString vide ""
	*************************************************/
	CString();

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur de recopie
	**************************************************
	*****Entr�e : STRString
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Creation d'un CString � partir de STRString
	*************************************************/
	CString(const CString & STRString);

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entr�e : sChaine
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Creation d'un CString � partir de sChaine
	*************************************************/
	CString(const char * sChaine);

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entr�e : iEntier
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Creation d'un CString � partir de iEntier
	*************************************************/
	CString(const int iEntier);

	/*************************************************
	*****NOM : CString
	**************************************************
	*****Constructeur de confort
	**************************************************
	*****Entr�e : uEntier
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Creation d'un CString � partir de uEntier
	*************************************************/
	CString(const unsigned int uEntier);

	/*************************************************
	*****NOM : ~CString
	**************************************************
	***** Destructeur
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Destruction de sSTRChaine
	*************************************************/
	~CString();

	/*************************************************
	*****NOM :STRGetChaine
	**************************************************
	***** Accesseur en lecture de sSTRChaine
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : const char *
	*****Entra�ne : Une copie du char * contenu dans CString
	*************************************************/
	const char * STRGetChaine();

	/*************************************************
	*****NOM : STRGetLongueur
	**************************************************
	***** Accesseur en lecture de uSTRTaille
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : unsigned int
	*****Entra�ne : Une copie de uSTRTaille
	*************************************************/
	unsigned int STRGetLongueur();

	/*************************************************
	*****NOM : STRGetCaractere
	**************************************************
	***** Accesseur en lecture d'un char
	**************************************************
	*****Entr�e : unsigned int uIndex
	*****N�cessite : uIndex valable
	*****Sortie : char
	*****Entra�ne : Renvoi du uIndex i�me caractere de sSTRChaine
	*************************************************/
	char STRGetCaractere(unsigned int uIndex);

	/*************************************************
	*****NOM : STRStringSansCaracteres
	**************************************************
	***** Renvoi un CString sans tout les caracteres pr�sents dans STRListeCaractere
	**************************************************
	*****Entr�e : const CString & STRListeCaractere
	*****N�cessite : n�ant
	*****Sortie : CString &
	*****Entra�ne : Cr�ation d'un CString & sans les caract�res de STRListeCaractere
	*************************************************/
	CString & STRStringSansCaracteres(const CString & STRListeCaractere);

	/*************************************************
	*****NOM : STRDupliquerString
	**************************************************
	***** Duplique le CString courant entre les bornes indiqu�es
	**************************************************
	*****Entr�e : unsigned int uIndexDepart = 0, unsigned int uIndexArrivee = UINT_MAX
	*****N�cessite : uIndexDepart et uIndexArrivee >= 0
	ET uIndexArrivee >= uIndexDepart
	*****Sortie : CString &
	*****Entra�ne : Duplique le CString courant entre les bornes indiqu�es
	OU une exception
	*************************************************/
	CString & STRDupliquerString(unsigned int uIndexDepart = 0, unsigned int uIndexArrivee = UINT_MAX);

	/*************************************************
	*****NOM : STRFindNextIndexSeparators
	**************************************************
	*****M�thode de recherche de separateur
	**************************************************
	*****Entr�e : unsigned int uIndexDepart, const CString & STRString
	*****N�cessite : uIndexDepart < uSTRTaille
	*****Sortie : unsigned int
	*****Entra�ne : le renvoi de l'index coreespondant � la prochaine it�ration
	d'un des caract�res de STRString dans l'objet, si non trouv�, ce sera celui de '\0'
	OU une exception
	*************************************************/
	unsigned int STRFindNextIndexSeparators(unsigned int uIndexDepart, const CString & STRString);

	/*************************************************
	*****NOM : operator==
	**************************************************
	***** Test l'�galit� de 2 CString
	**************************************************
	*****Entr�e : const CString & STRString, le CString avec qui comparer
	*****N�cessite : n�ant
	*****Sortie : bool
	*****Entra�ne : true si egal, false sinon
	*************************************************/
	bool operator==(const CString & STRString);

	/*************************************************
	*****NOM : operator!=
	**************************************************
	***** Test l'in�galit� de 2 CString
	**************************************************
	*****Entr�e : const CString & STRString, le CString avec qui comparer
	*****N�cessite : n�ant
	*****Sortie : bool
	*****Entra�ne : false si egal, true sinon
	*************************************************/
	bool operator!=(const CString & STRString);

	/*************************************************
	*****NOM : operator=
	**************************************************
	***** Op�rateur d'affection
	**************************************************
	*****Entr�e : const CString & STRString
	*****N�cessite : n�ant
	*****Sortie : CString &
	*****Entra�ne : *this == STRString
	*************************************************/
	CString & operator=(const CString & STRString);

	/*************************************************
	*****NOM : operator+
	**************************************************
	*****Op�rateur + char
	**************************************************
	*****Entr�e : const CString & STRString
	*****N�cessite : n�ant
	*****Sortie : CString &
	*****Entra�ne : concat�nation de 2 CString en un troisi�me retourn�
	*************************************************/
	CString & operator+(const CString & STRString);

	/*************************************************
	*****NOM : operator+=
	**************************************************
	*****Op�rateur += CString
	**************************************************
	*****Entr�e : const CString & STRString
	*****N�cessite : n�ant
	*****Sortie : CString &
	*****Entra�ne : concat�nation de 2 CString dans l'appelant
	*************************************************/
	CString & operator+=(const CString & STRString);

	/*************************************************
	*****NOM : operator+
	**************************************************
	*****Op�rateur + char
	**************************************************
	*****Entr�e : const char & STRString
	*****N�cessite : n�ant
	*****Sortie : CString &
	*****Entra�ne : concat�nation d'un CString et d'un char en un troisi�me retourn�
	*************************************************/
	CString & operator+(const char & cChar);

	/*************************************************
	*****NOM : operator+=
	**************************************************
	*****Op�rateur += char
	**************************************************
	*****Entr�e : const char & STRString
	*****N�cessite : n�ant
	*****Sortie : CString &
	*****Entra�ne : ajout de cChar � la fin de l'objet courant
	*************************************************/
	CString & operator+=(const char & cChar);

	/*************************************************
	*****NOM : operator[]
	**************************************************
	***** Accesseur du uIndex�me caract�re de sSTRString
	**************************************************
	*****Entr�e : const unsigned int uIndex
	*****N�cessite : uIndex valable
	*****Sortie : char
	*****Entra�ne : le renvoie d'une copie du uIndex�me caract�re
	*************************************************/
	char operator[](const unsigned int uIndex);
};

#endif