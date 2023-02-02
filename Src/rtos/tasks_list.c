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

/**** Private types ***********************************************************/


/**** Private function prototypes *********************************************/

/**** Private constants *******************************************************/

/**** Private variables *******************************************************/

/**** Public constants ********************************************************/

/**** Public variables ********************************************************/
SemaphoreHandle_t xSuspendSemaphore;
SemaphoreHandle_t xResumeSemaphore;
StaticSemaphore_t xSemaphoreBuffer1;
StaticSemaphore_t xSemaphoreBuffer2;
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
	//if(watchdog_handle!=NULL){
		//HAL_GPIO_TogglePin(LED4_GPIO_PORT,LED4_PIN);
	//}
	//Create a StaticTask to suspend watchdogservicing task.
	StaticTask_t xTaskBuffer2;
	StackType_t xStack2[ 90 ];
	xTaskCreateStatic( vSuspensionTask,"suspensionTask",90,NULL,4,xStack2,&xTaskBuffer2);
	//Create a StaticTask to resume watchdogservicing task.
	StaticTask_t xTaskBuffer3;
	StackType_t xStack3[ 70 ];
	xTaskCreateStatic( vResumeTask,"resumeTask",70,NULL,4,xStack3,&xTaskBuffer3); 
	vTaskStartScheduler();
}
void vCreateSemaphore(void) {
	xSuspendSemaphore = xSemaphoreCreateBinaryStatic(&xSemaphoreBuffer1);
	xResumeSemaphore = xSemaphoreCreateBinaryStatic(&xSemaphoreBuffer2);
}

void vWatchdogTask(void *pvParameters){
	for(;;){
	feed_watchdog();
	HAL_GPIO_TogglePin(LED5_GPIO_PORT, LED5_PIN);
	vTaskDelay(pdMS_TO_TICKS(2000));
	}
}

	static void vSuspensionTask(void *pvParameters){
	for(;;){
		xSemaphoreTake( xSuspendSemaphore,portMAX_DELAY);
		HAL_GPIO_TogglePin(LED6_GPIO_PORT, LED6_PIN);
		//vTaskSuspend(watchdog_handle);
	}
}
	
void vResumeTask(void *pvParameters){
	for(;;){
	xSemaphoreTake( xResumeSemaphore, portMAX_DELAY );
	HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
	//vTaskResume(watchdog_handle);
	}
}