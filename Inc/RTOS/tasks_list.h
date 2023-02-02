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
#ifndef __TASKS_LIST_H
#define __TASKS_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/**** Includes ****************************************************************/
/**** Public macros ***********************************************************/

/**** Public types ************************************************************/

/**** Public constants ********************************************************/


/**** Public variables ********************************************************/

/**** Public function prototypes **********************************************/
void vWatchdogTask(void *pvParameters);
/*!*****************************************************************************
 * \brief watchdogTask
 * \param 
 * \return 
 ******************************************************************************/
static void vSuspensionTask(void *pvParameters);

/*!*****************************************************************************
 * \brief SuspensionTask
 * \param 
 * \return 
 ******************************************************************************/
static void vResumeTask(void *pvParameters);
/*!*****************************************************************************
 * \brief ResumeTask
 * \param 
 * \return 
 ******************************************************************************/
void vCreateAllTAsk(void);
/*!*****************************************************************************
 * \brief CreateAllTask
 * \param 
 * \return 
 ******************************************************************************/
 void vCreateSemaphore(void);
/*!*****************************************************************************
 * \brief CreateAllSemaphore
 * \param 
 * \return 
 ******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /*WATCHDOG_H */

