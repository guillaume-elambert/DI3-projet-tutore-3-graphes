#include "CFichier.h"

CFichier::CFichier()
{
	cpCheminFichier = nullptr;
	cpContenu = nullptr;
}

CFichier::CFichier(char * cpCheminFichier)
{
	if (cpCheminFichier == nullptr) {
		throw CException(CFICHIER_Chemin_Null, "CFichier::CFichier(char * cpCheminFichier) : La cha�ne de caract�res correspondant au chemin vers le fichier est nulle.\n");
	}

	std::string sFileContent(""), sBuffer;
	std::fstream FILfichier(cpCheminFichier);
	char sExceptionMessage[255];

	//Entr�e : Le fichier n'a pas pu �tre ouvert
	if (!FILfichier.is_open())
	{
		sprintf_s(sExceptionMessage, 255, "CFichier::CFichier(char * cpCheminFichier) : Impossible d'ouvrir le fichier \"%s\".\n", cpCheminFichier);
		throw CException(CFICHIER_Ouverture_Fichier_Impossible, sExceptionMessage);
	}


	while (std::getline(FILfichier, sBuffer)) {
		//On concat�ne la ligne courrante avec les lignes pr�c�dentes
		//On ajoute on retour � la ligne si la ligne courrante n'est pas la derni�re du fichier
		cpContenu += sBuffer + (!FILfichier.eof() ? "\n" : "");
	}

	FILfichier.close();

}

CFichier::~CFichier()
{
}

char * CFichier::getContenu()
{
	return _strdup(cpContenu.c_str());;
}
