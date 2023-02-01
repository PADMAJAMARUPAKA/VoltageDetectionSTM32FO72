/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to configure and use GPIOs through
  *          the STM32F0xx HAL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "watchdog.h"
#include "event_groups.h"
#include "semphr.h"

SemaphoreHandle_t xSuspendSemaphore;
SemaphoreHandle_t xResumeSemaphore;
StaticSemaphore_t xSemaphoreBuffer1;
StaticSemaphore_t xSemaphoreBuffer2;


/** @addtogroup STM32F0xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

TaskHandle_t watchdog_handle;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static GPIO_InitTypeDef  GPIO_InitStruct;
/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
static void Error_Handler(void);
void vWatchdogTask(void *pvParameters);
static void vSuspensionTask(void *pvParameters);
static void vResumeTask(void *pvParameters);

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* This sample code shows how to use GPIO HAL API to toggle LED3, LED4, LED5 and LED6 IOs
    in an infinite loop. */

  /* STM32F0xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Low Level Initialization
     */

  HAL_Init();

  /* Configure the system clock to 48 MHz */
  SystemClock_Config();
  //HAL_NVIC_EnableIRQ(PendSV_IRQn);
	//HAL_NVIC_SetPriority(PendSV_IRQn,3,0);
  /* -1- Enable each GPIO Clock (to be able to program the configuration registers) */
  LED3_GPIO_CLK_ENABLE();
	/* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = LED3_PIN;
  HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);
	//LED4 INTIALIZATION
	  LED4_GPIO_CLK_ENABLE();
	/* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = LED4_PIN;
  HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);
	/* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = LED5_PIN;
  HAL_GPIO_Init(LED5_GPIO_PORT, &GPIO_InitStruct);
	 GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = LED6_PIN;
  HAL_GPIO_Init(LED6_GPIO_PORT, &GPIO_InitStruct);
	//WATCHDOG INTIALIZATION
	if((RCC->CSR & RCC_CSR_IWDGRSTF) == 0X20000000)
	{
		HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED3_PIN);
		RCC->CSR |= RCC_CSR_RMVF;

	}
	
	watchdog_init();
	//Button intialization
	BSP_PB_Init(BUTTON_USER,BUTTON_MODE_EXTI);
	
	xSuspendSemaphore = xSemaphoreCreateBinaryStatic(&xSemaphoreBuffer1);
	xResumeSemaphore = xSemaphoreCreateBinaryStatic(&xSemaphoreBuffer2);
	//if(xSuspendSemaphore!=NULL){
		//HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
	//}
	

//Create a StaticTask of highest priority to Toggle the LED every 1 second.
	StaticTask_t xTaskBuffer;
	StackType_t xStack[ 70 ];
	watchdog_handle=xTaskCreateStatic( vWatchdogTask,"watchdog",70,NULL,4,xStack,&xTaskBuffer); 
	//Create a StaticTask to suspend watchdogservicing task.
	StaticTask_t xTaskBuffer2;
	StackType_t xStack2[ 90 ];
	xTaskCreateStatic( vSuspensionTask,"suspensionTask",90,NULL,4,xStack2,&xTaskBuffer2);
	StaticTask_t xTaskBuffer3;
	StackType_t xStack3[ 70 ];
	//xTaskCreateStatic( vResumeTask,"resumeTask",70,NULL,4,xStack3,&xTaskBuffer3); 
	//Start the scheduler.
	vTaskStartScheduler();
	while (1)
  {

  }
}
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI48)
  *            SYSCLK(Hz)                     = 48000000
  *            HCLK(Hz)                       = 48000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 48000000
  *            PREDIV                         = 2
  *            PLLMUL                         = 2
  *            Flash Latency(WS)              = 1
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* Select HSI48 Oscillator as PLL source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI48;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK and PCLK1 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1)!= HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
/**
  * @brief  Task to feed the watchdog 
	
  * @param  None
  * @retval None
  */

void vWatchdogTask(void *pvParameters){
	for(;;){
		feed_watchdog();
		HAL_GPIO_TogglePin(LED5_GPIO_PORT, LED5_PIN);
	
		vTaskDelay(pdMS_TO_TICKS(2000));
					
	}
}

 static void vSuspensionTask(void *pvParameters){
	for(;;){
		//HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED3_PIN);
		//vTaskDelay(pdMS_TO_TICKS(1000));
		xSemaphoreTake( xSuspendSemaphore,portMAX_DELAY);
		HAL_GPIO_TogglePin(LED6_GPIO_PORT, LED6_PIN);
		//vTaskSuspend(watchdog_handle);
		//}
		//else {
			//	HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
				//vTaskDelay(pdMS_TO_TICKS(1000));
		//}
	}
}
void vResumeTask(void *pvParameters){
	for(;;){
		
		//vTaskDelay(pdMS_TO_TICKS(1000));
	xSemaphoreTake( xResumeSemaphore, portMAX_DELAY );
	HAL_GPIO_TogglePin(LED6_GPIO_PORT, LED6_PIN);
	vTaskResume(watchdog_handle);
	}
}

