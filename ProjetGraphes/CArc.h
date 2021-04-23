#ifndef CARC_H
#define CARC_H

#include <string>

class CArc
{
private:

	unsigned int uARCDestination;

public:

	/*************************************************
	*****NOM : CArc
	**************************************************
	*****Constructeur par d�faut
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : Ne pas utiliser.
	*****Sortie : n�ant
	*****Entra�ne : L�ve une exception.
	*************************************************/
	CArc(void);
	/*************************************************
	*****NOM : CArc
	**************************************************
	*****Constructeur de confort.
	**************************************************
	*****Entr�e : unsigned int uARCDestination
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Cr�ation d'un arc ayant pour destination unsigned int uARCDestination.
	*************************************************/
	CArc(unsigned int uARCDestination);
	/*************************************************
	*****NOM : CArc
	**************************************************
	*****Constructeur de recopie.
	**************************************************
	*****Entr�e : CArc & ARCParam
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : Cr�ation d'un arc copie de ARCParam.
	*************************************************/
	CArc(CArc & ARCParam);
	/*************************************************
	*****NOM : ~CArc
	**************************************************
	*****Destructeur par d�faut.
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : n�ant
	*****Entra�ne : L'objet est pr�t � �tre d�sallou�.
	*************************************************/
	~CArc(void);

	//Accesseur :

	/*************************************************
	*****NOM : ARCGetDestination
	**************************************************
	*****Accesseur en lecture de SOMDestination
	**************************************************
	*****Entr�e : n�ant
	*****N�cessite : n�ant
	*****Sortie : uARCDestination la destination de l'arc.
	*****Entra�ne : /
	*************************************************/
	unsigned int ARCGetDestination(void);
};
#endif
