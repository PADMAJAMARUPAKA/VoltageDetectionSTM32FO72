/*!*****************************************************************************
 * \file watchdog.c
 * \brief This module handles the independent watchdog functionality
 * \author padmaja
 ******************************************************************************/

/**** Includes ****************************************************************/
#include "watchdog.h"
#include "stm32f072xb.h"

/**** Private macros **********************************************************/

/**** Private types ***********************************************************/

/**** Private function prototypes *********************************************/

/**** Private constants *******************************************************/

/**** Private variables *******************************************************/

/**** Public constants ********************************************************/

/**** Public variables ********************************************************/

/**** Public function definitions *********************************************/

/******************************************************************************/
/**** Private function definitions ********************************************/
 void watchdog_init(void){
	RCC->CSR = RCC_CSR_LSION;
	IWDG->KR = IWDG_START; /* (1) */
	IWDG->KR = IWDG_WRITE_ACCESS; /* (2) */
	IWDG->PR = IWDG_PR_PR_2; /* (3) */
	IWDG->RLR = (40000 * watchdog_timer)/64;
	while (IWDG->SR) /* (5) */
	{
 /* add time out here for a robust application */
	}
	IWDG->KR = IWDG_REFRESH; 

}
void feed_watchdog(void)	{
	while (IWDG->SR) /* (5) */
	{
	}
	IWDG->KR = IWDG_REFRESH; 
}
