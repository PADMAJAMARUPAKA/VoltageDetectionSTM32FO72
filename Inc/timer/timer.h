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
#ifndef __TIMER_H
#define __TIMER_H

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
 * \brief intialiaze the clock for port c
 * \param 
 * \return 
 ******************************************************************************/
void TimerGpio_Init(void) ;
/*!*****************************************************************************
 * \brief intialiaze the Timer3
 * \param 
 * \return 
 ******************************************************************************/
void Timer3_Init(void) ;


#ifdef __cplusplus
}
#endif

#endif /*TIMER_H */




