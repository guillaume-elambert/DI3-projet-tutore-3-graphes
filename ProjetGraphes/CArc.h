#ifndef CARC_H
#define CARC_H

#include <string>

class CArc
{
private:

	unsigned int uARCDestination;

public:

	/*!
	 * Constructeur par d�faut
	 * 
	 */
	CArc(void);

	
	/*!
	 * Constructeur de confort
	 * 
	 * \param uARCDestination Le num�ro du sommet de destination de l'arc
	 */
	CArc(unsigned int uARCDestination);
	

	/*!
	 * Constructeur de recopie
	 * 
	 * \param ARCParam L'arc � copier
	 */
	CArc(CArc & ARCParam);
	
	/*!
	 * Destructeur par d�faut
	 * 
	 */
	~CArc(void);

	
	/*!
	 * Accesseur en lecture de SOMDestination
	 * 
	 * \return uARCDestination la destination de l'arc.
	 */
	unsigned int ARCGetDestination(void);
};
#endif
