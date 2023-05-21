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
#ifndef __LED_H
#define __LED_H

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
 * \brief Intialiaze the LED.
 * \param 
 * \return 
 ******************************************************************************/
void led3_init(void) ;
void led4_init(void) ;
void led5_init(void) ;
void led6_init(void) ;
void AdcPin_init(void);
void SpiPin_init(void);
void SlaveReady_pin(void);
void MasterReady_pin(void);
#ifdef __cplusplus
}
#endif

#endif /*WATCHDOG_H */

