/*file watchdog.h
 * \brief This module handles the Watchdog Timer.It will intialize the timer
					and service the watchdog frequency.
 * \author Padmaja
 *
 * \copyright Copyright (c) 2021,Padmaja.
 *            All rights reserved.
 *****************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/**** Includes ****************************************************************/
/**** Public macros ***********************************************************/

/**** Public types ************************************************************/

/**** Public constants ********************************************************/


/**** Public variables ********************************************************/

/**** Public function prototypes **********************************************/


/*!*****************************************************************************
 * \brief Intialiaze the spi communication
 * \param 
 * \return 
 ******************************************************************************/
void spi_init(void) ;
/*!*****************************************************************************
 * \brief Start the spi transfer.
 * \param 
 * \return 
 ******************************************************************************/
void spi_start(void);




#ifdef __cplusplus
}
#endif

#endif /*WATCHDOG_H */

