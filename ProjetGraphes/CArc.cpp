#include "CArc.h"

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
CArc::CArc(void)
{
	uARCDestination = 0;
}

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
CArc::CArc(unsigned int uARCDestinationParam)
{
	uARCDestination = uARCDestinationParam;
}

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
CArc::CArc(CArc & ARCParam)
{
	uARCDestination = ARCParam.uARCDestination;
}

/*************************************************
*****NOM : ~CArc
**************************************************
*****Destructeur par d�faut.
**************************************************
*****Entr�e : n�ant
*****N�cessite : n�ant
*****Sortie : n�ant
*****Entra�ne : L'obket est pr�t � �tre d�truite.
*************************************************/
CArc::~CArc(void)
{
	//Ne fait rien
}

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
unsigned int CArc::ARCGetDestination(void)
{
	return uARCDestination;
}
