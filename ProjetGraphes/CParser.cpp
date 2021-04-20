#include "CParser.h"

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
CParser::CParser()
{
	CString STRTypeAttribut = "fin";
	iPARValeurAttribut = 0;
	STRPARChemin = CString();
	STRPARContenuAttribut = CString();
	cPARCaractereActuel = '\0';
}

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
CParser::CParser(const CString STRChemin)
{
	CString STRTypeAttribut = "fin";
	iPARValeurAttribut = 0;
	STRPARContenuAttribut = CString();
	cPARCaractereActuel = '\0';
	PARInitialiser(STRChemin);
}

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
CParser::~CParser()
{
	PARFinaliser();
}

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
CString CParser::PARLireType()
{
	return TYAPARTypeAttribut;
}

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
CString CParser::PARLireNom()
{
	return STRPARNomAttribut;
}

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
int CParser::PARLireValeur()
{
	return iPARValeurAttribut;
}

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
void CParser::PARInitialiser(const CString STRChemin)
{
	STRPARChemin = STRChemin;
	if (STRPARChemin.STRGetLongueur() == 0)
	{
		throw(CException(Ouverture_Fichier_Impossible));
	}
	if (FILPARFichier.is_open())
	{
		FILPARFichier.close();
	}
	FILPARFichier = ifstream(STRPARChemin.STRGetChaine(), ios::in);
	if (FILPARFichier.fail())
	{
		FILPARFichier.close();
		throw(CException(Ouverture_Fichier_Impossible));
	}
	PARSuivant();
}

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
bool CParser::PARFinaliser()
{
	if (FILPARFichier.is_open())
	{
		FILPARFichier.close();
		CString STRTypeAttribut = "fin";
		iPARValeurAttribut = 0;
		STRPARChemin = "";
		STRPARContenuAttribut = "";
		cPARCaractereActuel = '\0';
		return true;
	}
	return false;
}

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
bool CParser::PARSuivant()
{
	if (FILPARFichier.is_open())
	{
		/* On vide le contenu pr�c�dent*/
		STRPARContenuAttribut = "";

		/*Si ce n'est pas le premier appel*/
		if (cPARCaractereActuel != '\0')
		{
			/*A chaque appel le dernier caractere reste en suspens, il faut donc l'ajouter sauf cas espace et regarder si c'est un separateur*/
			if (cPARCaractereActuel != ' ')
			{
				STRPARContenuAttribut += cPARCaractereActuel;
			}
		}

		while (FILPARFichier.get(cPARCaractereActuel))
		{
			if (PARIsSeparator(cPARCaractereActuel) || (STRPARContenuAttribut.STRGetLongueur() == 1 && PARIsSeparator(STRPARContenuAttribut[0])))
			{
				PARConvertirLigne();
				return true;
			}
			if (cPARCaractereActuel != ' ')
				STRPARContenuAttribut += cPARCaractereActuel;
		}

		/*Si on arrive ici, c'est que le FILPARFichier est arriv� � la fin sans separateur*/

		if (STRPARContenuAttribut.STRGetLongueur() == 0)
		{
			CString STRTypeAttribut = "fin";
			cPARCaractereActuel = '\0';
			return false;
		}
		else
		{
			cPARCaractereActuel = '\0';
			PARConvertirLigne();
		}

	}
	else
	{
		throw(CException(Fichier_Non_Ouvert));
	}
	return true;
}

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
void CParser::PARConvertirLigne()
{
	unsigned int uIndexBoucle = 0;
	unsigned int uIndexEgal = 0;

	STRPARNomAttribut = "";
	iPARValeurAttribut = 0;
	CString STRTypeAttribut = "non reconnu";

	/*Tout les �l�ments synthaxique de 1 de longueur*/
	if (STRPARContenuAttribut.STRGetLongueur() == 1)
	{
		switch (STRPARContenuAttribut[0])
		{
		case ']':
			STRTypeAttribut = "fin de tableau";
			break;
		case ',':
			STRTypeAttribut = "virgule";
			break;
		case '\n':
			STRTypeAttribut = "saut";
			break;
		default:
			break;
		}
	}
	/*Tout les �l�ments synthaxique de plus de 1 de longueur*/
	else
	{
		/*Ils ont tous le format nomAttribut=valeur donc on cherche le premier �gal*/
		uIndexEgal = STRPARContenuAttribut.STRFindNextIndexSeparators(0, "=");

		/*Le �gal ne doit ni �tre au d�but ni � la fin sinon on a pas de valeur ou de nom d'attribut*/
		if (uIndexEgal > 0 && uIndexEgal < STRPARContenuAttribut.STRGetLongueur() - 1)
		{
			/*Debut de tableau*/
			if (STRPARContenuAttribut[uIndexEgal + 1] == '[' && STRPARContenuAttribut.STRGetLongueur() == uIndexEgal + 2)
			{
				CString STRTypeAttribut = "debutTableau";
			}
			/*Valeur enti�re positive*/
			else if (STRPARContenuAttribut[uIndexEgal + 1] >= '0' && STRPARContenuAttribut[uIndexEgal + 1] <= '9')
			{
				CString STRTypeAttribut = "entier";
				/*Conversion de chaine en entier positif*/
				for (uIndexBoucle = uIndexEgal + 1; uIndexBoucle < STRPARContenuAttribut.STRGetLongueur(); uIndexBoucle++)
				{
					if (STRPARContenuAttribut[uIndexBoucle] >= '0' && STRPARContenuAttribut[uIndexBoucle] <= '9')
					{
						iPARValeurAttribut = iPARValeurAttribut * 10 + (STRPARContenuAttribut[uIndexBoucle] - '0');
					}
					/*Si il n'y a pas que des chiffres, c'est pas reconnu*/
					else
					{
						CString STRTypeAttribut = "nonReconnu";
						break;
					}
				}
			}
		}
		if (STRTypeAttribut != "nonReconnu")
			STRPARNomAttribut = STRPARContenuAttribut.STRDupliquerString(0, uIndexEgal - 1);
	}
}

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
bool CParser::PARIsSeparator(const char cCaractere)
{
	if (cCaractere == ',' || cCaractere == '\n')
		return true;
	else
		return false;
}
