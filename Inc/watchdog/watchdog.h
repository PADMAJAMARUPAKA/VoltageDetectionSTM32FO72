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
#ifndef __WATCHDOG_H
#define __WATCHDOG_H

#ifdef __cplusplus
extern "C" {
#endif

/**** Includes ****************************************************************/
/**** Public macros ***********************************************************/
#define IWDG_START 0X000CCCC
#define IWDG_WRITE_ACCESS 0X00005555
#define  watchdog_timer 5000
#define IWDG_REFRESH 0x0000AAAA
/**** Public types ************************************************************/

/**** Public constants ********************************************************/


/**** Public variables ********************************************************/

/**** Public function prototypes **********************************************/


/*!*****************************************************************************
 * \brief Intialiaze the independent watchdog peripheral.
 * \param 
 * \return 
 ******************************************************************************/
void watchdog_init(void) ;

/*!*****************************************************************************
 * \brief Feed the dog.
 * \param 
 * \return 
 ******************************************************************************/
void feed_watchdog(void) ;


#ifdef __cplusplus
}
#endif

#endif /*WATCHDOG_H */

