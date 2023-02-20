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
#include "event_groups.h"
#include "stm32f072b_discovery.h"
#include "adc.h"


/**** Private macros **********************************************************/
//#define watchdog_peiodicity	100 

/**** Private types ***********************************************************/


/**** Private function prototypes *********************************************/

/**** Private constants *******************************************************/

/**** Private variables *******************************************************/

/**** Public constants ********************************************************/

/**** Public variables ********************************************************/

TaskHandle_t watchdog_handle;
StaticEventGroup_t xCreatedEventGroup;
EventGroupHandle_t xEventGroup;

void vWatchdogTask(void *pvParameters);
/**** Public function definitions *********************************************/

/******************************************************************************/
/**** Private function definitions ********************************************/

void vCreateAllTAsk(void){

	//Create a periodic watchdog task
	xEventGroup = xEventGroupCreateStatic(&xCreatedEventGroup);
	StaticTask_t xTaskBuffer;
	StackType_t xStack[ 70 ];
	StaticTask_t xTaskBuffer2;
	StackType_t xStack2[ 70 ];
	StaticTask_t xTaskBuffer3;
	StackType_t xStack3[ 70 ];
	watchdog_handle=xTaskCreateStatic( vWatchdogTask,"watchdog",70,NULL,1,xStack,&xTaskBuffer);
	xTaskCreateStatic( vAdcTask,"adc",70,NULL,3,xStack2,&xTaskBuffer2);
	xTaskCreateStatic( vAdcMeasurementTask,"adcMeasurementTask",70,NULL,2,xStack3,&xTaskBuffer3);
	//if(watchdog_handle!=NULL){
		//HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN,GPIO_PIN_SET);
	//}
	vTaskStartScheduler();
}


void vWatchdogTask(void *pvParameters){
	for(;;){
		
	if(BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_RESET)	{
	feed_watchdog();
	}
	HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
	//xEventGroupSetBits( xEventGroup,eventg);
	//ADC1->CR |= ADC_CR_ADSTART;
	//adc_start();
	//vTaskSuspend(watchdog_handle);
	vTaskDelay(pdMS_TO_TICKS(watchdog_peiodicity));
	}
}
void vAdcTask(void *pvParameters)	{
		for(;;){
		xEventGroupWaitBits(xEventGroup,eventg,pdTRUE,pdFALSE,portMAX_DELAY);
		HAL_GPIO_TogglePin(LED6_GPIO_PORT, LED6_PIN);
		}
}


void vAdcMeasurementTask(void *pvParameters)	{
	
		for(;;){
		adc_start();
		HAL_GPIO_TogglePin(LED5_GPIO_PORT, LED5_PIN);
		vTaskDelay(pdMS_TO_TICKS(1000));
		}
}