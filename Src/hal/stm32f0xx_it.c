/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/Src/stm32f0xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
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
#include "stm32f0xx_it.h"
#include "stm32f0xx_hal_exti.h"
extern SemaphoreHandle_t xSuspendSemaphore;
extern SemaphoreHandle_t xResumeSemaphore;
extern StaticSemaphore_t xSemaphoreBuffer1;
extern StaticSemaphore_t xSemaphoreBuffer2;
//#include "FreeRTOS.h"

/** @addtogroup STM32F0xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
void EXTI0_1_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken;
	xHigherPriorityTaskWoken = pdFALSE;
	if(BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_SET)
	{
		
		if(xSemaphoreGiveFromISR( xSuspendSemaphore, &xHigherPriorityTaskWoken)== pdTRUE)
		{
		//HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
		}
		EXTI->PR=0x00000001;
	}
	//RV 
	if(BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_RESET)
	{
		//HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
			xSemaphoreGiveFromISR( xResumeSemaphore, &xHigherPriorityTaskWoken );
			EXTI->PR=0x00000001;
	}
	if(xHigherPriorityTaskWoken == pdTRUE){
//HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);	
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken );
	}
}
	


/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}


/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{
  //HAL_IncTick();
//}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
