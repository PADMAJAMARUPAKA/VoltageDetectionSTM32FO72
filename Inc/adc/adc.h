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
#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/**** Includes ****************************************************************/
/**** Public macros ***********************************************************/
#define adc_lowerlimit 310
#define adc_higherlimit 0X60E
/**** Public types ************************************************************/

/**** Public constants ********************************************************/


/**** Public variables ********************************************************/

/**** Public function prototypes **********************************************/


/*!*****************************************************************************
 * \brief Intialiaze the adc peripheral and analog watchdog.
 * \param 
 * \return 
 ******************************************************************************/
void adc_init(void) ;
/*!*****************************************************************************
 * \brief Start the adc conversion.
 * \param 
 * \return 
 ******************************************************************************/
void adc_start(void);




#ifdef __cplusplus
}
#endif

#endif /*WATCHDOG_H */

