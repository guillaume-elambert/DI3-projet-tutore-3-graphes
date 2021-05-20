/*!
 * \file CFichier.h
 * \brief Fichier contenant la d�claration de la classe CFIchier.
 * \author Guillaume ELAMBERT
 * \author Cl�ment NONCHER-GILLET
 * \date 2021
 */


#ifndef CFICHIER_H
#define CFICHIER_H

#include <fstream>
#include <string>
#include "CException.h"


#define CFICHIER_Chemin_Null					30
#define CFICHIER_Ouverture_Fichier_Impossible	31


class CFichier
{

private :
	std::string cpCheminFichier;
	std::string cpContenu;

public :
	/*!
	 * Constructeur par d�faut.
	 * 
	 */
	CFichier();

	/*!
	 * Constructeur de confort.
	 * 
	 * \param cpCheminFichier Le chemin vers le fichier.
	 * \return 
	 */
	CFichier(char * cpCheminFichier);

	/*!
	 * Destructeur par d�faut.
	 * 
	 */
	~CFichier();

	/*!
	 * M�thode qui retourne le contenu du fichier.
	 * 
	 * \return 
	 */
	char * getContenu();
};

#endif