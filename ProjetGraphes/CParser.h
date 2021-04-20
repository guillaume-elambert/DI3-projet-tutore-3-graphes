#ifndef CPARSER_H
#define CPARSER_H

#include <fstream>

#include "CString.h"


#define Ouverture_Fichier_Impossible 50
#define Fichier_Non_Ouvert 51

class CParser
{
private:
	CString STRPARChemin;

	CString STRPARNomAttribut;
	CString TYAPARTypeAttribut;
	int iPARValeurAttribut;

	char cPARCaractereActuel;
	CString STRPARContenuAttribut;
	ifstream FILPARFichier;

	/*************************************************
	*****NOM : PARConvertirLigne
	**************************************************
	*****Permet au parser de lire convertir l'attribut
	trouv� en type voir en valeur pour les cas sp�cifiques
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Mise � jour des attributs nom, type et valeur
	*************************************************/
	void PARConvertirLigne();

	/*************************************************
	*****NOM : PARIsSeparator
	**************************************************
	*****Permet au parser de savoir si un caractere
	sp�cifique d�limite une s�paration
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : boolean
	*****Entra�ne : /
	*************************************************/
	static bool PARIsSeparator(const char cCaractere);

public:

	/*************************************************
	*****NOM : CParser
	**************************************************
	*****Constructeur par d�faut
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Cr�ation d'un parser vide
	*************************************************/
	CParser();

	/*************************************************
	*****NOM : CParser
	**************************************************
	*****Constructeur de confort (CString)
	**************************************************
	*****Entr�e : Une chaine de charact�re du chemin du fichier � convertir
	*****N�cessite : Un chemin valide
	*****Sortie : n�ant
	*****Entra�ne : Cr�ation d'un parser initialis� avec le chemin,
	si non valide, d�clenche une exception indiquant la non validit� du chemin
	*************************************************/
	CParser(const CString STRChemin);

	/*************************************************
	*****NOM : ~CParser
	**************************************************
	*****Destructeur
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Destruction d'un parser
	*************************************************/
	~CParser();

	/*************************************************
	*****NOM : PARLireType
	**************************************************
	*****Acesseur en lecture de PARTYAType
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : Un parser initialis�
	*****Sortie : le type de la valeur
	*****Entra�ne : /
	*************************************************/
	CString PARLireType();

	/*************************************************
	*****NOM : PARLireNom
	**************************************************
	*****Acesseur en lecture de PARNomAttribut
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : �tre utilis� apr�s PARLireType si il renvoi entier
	*****Sortie : un CString repr�sentant la valeur
	*****Entra�ne : /
	*************************************************/
	CString PARLireNom();

	/*************************************************
	*****NOM : PARLireValeur
	**************************************************
	*****Acesseur en lecture de PARValeur
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : �tre utilis� apr�s PARLireType si il renvoi entier
	*****Sortie : iParValeurAttribut
	*****Entra�ne : Retour de la valeur
	*************************************************/
	int PARLireValeur();

	/*************************************************
	*****NOM : PARInitialiser
	**************************************************
	*****Initialisation et mise au d�but de la lecture
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : Le parser a d�j� un chemin valide
	*****Sortie : n�ant
	*****Entra�ne : Initialisation du parser,
	si chemin invalide, entraine une exception indiquant la non validit� du chemin,
	si d�j� initialis�, le r�initialise.
	*************************************************/
	void PARInitialiser(const CString STRChemin);

	/*************************************************
	*****NOM : PARFinaliser
	**************************************************
	*****Finalisation de la lecture
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : true si la finalisation s'est faite,
	false si l'initialisation ne s'�tait pas faite
	*****Entra�ne : Finalisation du parser, ferme le ifstream
	*************************************************/
	bool PARFinaliser();

	/*************************************************
	*****NOM : PARSuivant
	**************************************************
	*****Passe � l'objet syntaxique suivant
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : Le parser est initialis�
	*****Sortie : n�ant
	*****Entra�ne : Passage � l'entit� synthaxique suivante
					Si � la fin, reste � la fin et renvoi false
	*************************************************/
	bool PARSuivant();
};
#endif