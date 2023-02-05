/*!*****************************************************************************
 * \file led.c
 * \brief This module handles the led enabling.
 * \author padmaja
 ******************************************************************************/

/**** Includes ****************************************************************/
#include "tasks_list.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "watchdog.h"
#include "stm32f072b_discovery.h"


/**** Private macros **********************************************************/
#define watchdog_peiodicity	100 

/**** Private types ***********************************************************/


/**** Private function prototypes *********************************************/

/**** Private constants *******************************************************/

/**** Private variables *******************************************************/

/**** Public constants ********************************************************/

/**** Public variables ********************************************************/

TaskHandle_t watchdog_handle;
void vWatchdogTask(void *pvParameters);
/**** Public function definitions *********************************************/

/******************************************************************************/
/**** Private function definitions ********************************************/

void vCreateAllTAsk(void){

	//Create a periodic watchdog task
	StaticTask_t xTaskBuffer;
	StackType_t xStack[ 70 ];
	watchdog_handle=xTaskCreateStatic( vWatchdogTask,"watchdog",70,NULL,3,xStack,&xTaskBuffer); 
}


void vWatchdogTask(void *pvParameters){
	for(;;){
		
	if(BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_RESET)
	feed_watchdog();
	vTaskDelay(pdMS_TO_TICKS(watchdog_peiodicity));
	}
}

