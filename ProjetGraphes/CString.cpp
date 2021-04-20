#include "CString.h"

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
CString::CString()
{
	uSTRTaille = 0;
	uSTRTailleMemoire = 8;
	sSTRChaine = new char[uSTRTailleMemoire];
	sSTRChaine[0] = '\0';
}

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
CString::CString(const CString & STRString)
{
	uSTRTailleMemoire = STRString.uSTRTailleMemoire;
	uSTRTaille = STRString.uSTRTaille;
	sSTRChaine = new char[uSTRTailleMemoire];
	for (unsigned int uIndex = 0; uIndex <= uSTRTaille; uIndex++)
	{
		sSTRChaine[uIndex] = STRString.sSTRChaine[uIndex];
	}
}

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
CString::CString(const char * sChaine)
{
	uSTRTailleMemoire = 8;
	uSTRTaille = 0;
	if (sChaine == NULL)
	{
		sSTRChaine = new char[uSTRTailleMemoire];
		sSTRChaine[0] = '\0';
	}
	else
	{
		while (sChaine[uSTRTaille] != '\0')
		{
			uSTRTaille++;
			if (uSTRTaille == uSTRTailleMemoire)
				uSTRTailleMemoire += 8;
		}
		sSTRChaine = new char[uSTRTailleMemoire];
		for (unsigned int uIndex = 0; uIndex < uSTRTaille; uIndex++)
		{
			sSTRChaine[uIndex] = sChaine[uIndex];
		}
		sSTRChaine[uSTRTaille] = '\0';
	}
}

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
CString::CString(int iEntier)
{
	uSTRTailleMemoire = 8;
	uSTRTaille = 0;
	sSTRChaine = new char[uSTRTailleMemoire];
	char * sNombreInv = new char[uSTRTailleMemoire]; //stock le nombre avec les divisions par 10, et donc dans un ordre invers�
	unsigned int uIndex = 0;

	if (iEntier < 0)
	{
		sSTRChaine[0] = '-';
		uSTRTaille = 1;
		iEntier = -iEntier;
	}
	if (iEntier == 0)
	{
		sSTRChaine[0] = '0';
		uSTRTaille = 1;
	}
	else
	{
		while (iEntier != 0)
		{
			sNombreInv[uIndex] = (iEntier % 10) + '0';
			iEntier /= 10;
			uIndex++;
		}
		sNombreInv[uIndex] = '\0';
		if (sSTRChaine[0] == '-') {
			for (uSTRTaille; uSTRTaille <= uIndex; uSTRTaille++)
			{
				sSTRChaine[uSTRTaille] = sNombreInv[uIndex - uSTRTaille];
			}
		}
		else
		{
			for (uSTRTaille; uSTRTaille < uIndex; uSTRTaille++)
			{
				sSTRChaine[uSTRTaille] = sNombreInv[uIndex - uSTRTaille - 1];
			}
		}
	}
	sSTRChaine[uSTRTaille] = '\0';
}

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
CString::CString(unsigned int uEntier)
{
	uSTRTailleMemoire = 8;
	uSTRTaille = 0;
	sSTRChaine = new char[8];
	char * sNombreInv = new char[8];
	if (uEntier == 0)
	{
		sSTRChaine[0] = '0';
		uSTRTaille = 1;
	}
	else
	{
		unsigned int uIndex = 0;
		while (uEntier != 0)
		{
			sNombreInv[uIndex] = (uEntier % 10) + '0';
			uEntier /= 10;
			uIndex++;
		}
		sNombreInv[uIndex] = '\0';
		if (sSTRChaine[0] == '-') {
			for (uSTRTaille; uSTRTaille <= uIndex; uSTRTaille++)
			{
				sSTRChaine[uSTRTaille] = sNombreInv[uIndex - uSTRTaille];
			}
		}
		else
		{
			for (uSTRTaille; uSTRTaille < uIndex; uSTRTaille++)
			{
				sSTRChaine[uSTRTaille] = sNombreInv[uIndex - uSTRTaille - 1];
			}
		}
	}
	sSTRChaine[uSTRTaille] = '\0';
}

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
CString::~CString()
{
	delete[] sSTRChaine;
}

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
const char * CString::STRGetChaine()
{
	unsigned int uIndexBoucle = 0;
	char * sNouvelleChaine = new char[uSTRTaille + 1];
	for (uIndexBoucle = 0; uIndexBoucle <= uSTRTaille; uIndexBoucle++)
		sNouvelleChaine[uIndexBoucle] = sSTRChaine[uIndexBoucle];
	return sNouvelleChaine;
}

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
unsigned int CString::STRGetLongueur()
{
	return uSTRTaille;
}

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
char CString::STRGetCaractere(unsigned int uIndex)
{
	if (uIndex > uSTRTaille)
		throw(CException(Index_Incompatible));
	return sSTRChaine[uIndex];
}

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
CString & CString::STRStringSansCaracteres(const CString & STRListeCaractere)
{
	unsigned int uIndexBoucleWhile = 0;
	unsigned int uIndexBoucleFor = 0;
	bool bCaractereTrouve;
	CString * STRNouveauString = new CString();
	if (STRListeCaractere.uSTRTaille != 0)
	{
		while (uIndexBoucleWhile < uSTRTaille)
		{
			bCaractereTrouve = false;
			for (uIndexBoucleFor = 0; uIndexBoucleFor < STRListeCaractere.uSTRTaille; uIndexBoucleFor++)
			{
				if (sSTRChaine[uIndexBoucleWhile] == STRListeCaractere.sSTRChaine[uIndexBoucleFor])
					bCaractereTrouve = true;
			}
			if (!bCaractereTrouve)
				*STRNouveauString += sSTRChaine[uIndexBoucleWhile];
		}
	}
	return *STRNouveauString;
}

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
CString & CString::STRDupliquerString(unsigned int uIndexDepart, unsigned int uIndexArrivee)
{
	unsigned int uIndexBoucle = 0;

	if (uIndexArrivee >= uSTRTaille || uIndexArrivee == 0)
		uIndexArrivee = uSTRTaille - 1;

	if (uIndexArrivee < uIndexDepart)
		throw(CException(Index_Incompatible));

	CString * STRNouveauString = new CString();

	for (uIndexBoucle = uIndexDepart; uIndexBoucle <= uIndexArrivee; uIndexBoucle++)
	{
		STRNouveauString->operator+=(sSTRChaine[uIndexBoucle]);
	}

	sSTRChaine[uIndexBoucle] = '\0';

	return *STRNouveauString;
}

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
unsigned int CString::STRFindNextIndexSeparators(unsigned int uIndexDepart, const CString & STRString)
{
	unsigned int uIndexBoucle = 0;
	if (uIndexDepart > uSTRTaille)
	{
		throw CException(Index_Incompatible);
	}

	while (sSTRChaine[uIndexDepart] != '\0')
	{
		for (uIndexBoucle = 0; uIndexBoucle < STRString.uSTRTaille; uIndexBoucle++)
		{
			if (sSTRChaine[uIndexDepart] == STRString.sSTRChaine[uIndexBoucle])
			{
				return uIndexDepart;
			}
		}
		uIndexDepart++;
	}
	return uIndexDepart;
}

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
bool CString::operator==(const CString & STRString)
{
	unsigned int uIndexBoucle;
	if (uSTRTaille != STRString.uSTRTaille)
		return false;
	for (uIndexBoucle = 0; uIndexBoucle < uSTRTaille; uIndexBoucle++)
	{
		if (sSTRChaine[uIndexBoucle] != STRString.sSTRChaine[uIndexBoucle])
			return false;
	}
	return true;
}

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
bool CString::operator!=(const CString & STRString)
{
	return !(operator==(STRString));
}

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
CString & CString::operator=(const CString & STRString)
{

	delete[] sSTRChaine;
	uSTRTailleMemoire = STRString.uSTRTailleMemoire;
	uSTRTaille = STRString.uSTRTaille;
	sSTRChaine = new char[uSTRTailleMemoire];
	for (unsigned int uIndex = 0; uIndex <= uSTRTaille; uIndex++)
	{
		sSTRChaine[uIndex] = STRString.sSTRChaine[uIndex];
	}
	return *this;
}

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
CString & CString::operator+(const CString & STRString)
{
	CString * pSTRNouveauString = new CString(*this);
	*pSTRNouveauString += STRString;

	return *pSTRNouveauString;
}

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
CString & CString::operator+=(const CString & STRString)
{
	unsigned int uIndexBoucle = 0;

	if (uSTRTailleMemoire + STRString.uSTRTailleMemoire >= uSTRTaille + STRString.uSTRTaille + 8)
		uSTRTailleMemoire += STRString.uSTRTailleMemoire - 8;
	else
		uSTRTailleMemoire += STRString.uSTRTailleMemoire;

	char * sNouvelleChaine = new char[uSTRTailleMemoire];

	for (uIndexBoucle = 0; uIndexBoucle < uSTRTaille; uIndexBoucle++)
	{
		sNouvelleChaine[uIndexBoucle] = sSTRChaine[uIndexBoucle];
	}
	for (uIndexBoucle = 0, uSTRTaille; uIndexBoucle < STRString.uSTRTaille; uIndexBoucle++, uSTRTaille++)
	{
		sNouvelleChaine[uSTRTaille] = STRString.sSTRChaine[uIndexBoucle];
	}
	sNouvelleChaine[uSTRTaille] = '\0';
	delete[] sSTRChaine;
	sSTRChaine = sNouvelleChaine;

	return *this;
}

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
CString & CString::operator+(const char & cChar)
{
	CString * pSTRNouveauString = new CString(*this);
	*pSTRNouveauString += cChar;

	return *pSTRNouveauString;
}

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
CString & CString::operator+=(const char & cChar)
{
	if (cChar == '\0')
		throw CException(0);
	unsigned int uIndex = 0;

	if (uSTRTaille == uSTRTailleMemoire - 1)
	{
		uSTRTailleMemoire += 8;
		char * sNouvelleChaine = new char[uSTRTailleMemoire];
		for (uIndex = 0; uIndex < uSTRTaille; uIndex++)
		{
			sNouvelleChaine[uIndex] = sSTRChaine[uIndex];
		}
		delete[] sSTRChaine;
		sSTRChaine = sNouvelleChaine;
	}
	sSTRChaine[uSTRTaille] = cChar;
	uSTRTaille++;
	sSTRChaine[uSTRTaille] = '\0';
}

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
char CString::operator[](const unsigned int uIndex)
{
	if (uIndex > uSTRTaille)
		throw CException(0);
	return sSTRChaine[uIndex];
}