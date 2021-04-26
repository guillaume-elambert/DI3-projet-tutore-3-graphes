#include "CArc.h"

/*!
 * Constructeur par d�faut
 *
 */
CArc::CArc(void)
{
	uARCDestination = 0;
}


/*!
 * Constructeur de confort
 * 
 * \param uARCDestination Le num�ro du sommet de destination de l'arc
 */
CArc::CArc(unsigned int uARCDestinationParam)
{
	uARCDestination = uARCDestinationParam;
}

/*!
 * Constructeur de recopie
 *
 * \param ARCParam L'arc � copier
 */
CArc::CArc(CArc & ARCParam)
{
	uARCDestination = ARCParam.uARCDestination;
}


/*!
 * Destructeur par d�faut
 *
 */
CArc::~CArc(void)
{
	//Ne fait rien
}


/*!
 * Accesseur en lecture de SOMDestination
 *
 * \return uARCDestination la destination de l'arc.
 */
unsigned int CArc::ARCGetDestination(void)
{
	return uARCDestination;
}
