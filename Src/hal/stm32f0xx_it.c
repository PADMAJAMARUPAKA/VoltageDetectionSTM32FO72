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
#include "event_groups.h"
#include "tasks_list.h"
#include	"spi.h"


extern SemaphoreHandle_t xSuspendSemaphore;
extern SemaphoreHandle_t xResumeSemaphore;
extern StaticSemaphore_t xSemaphoreBuffer1;
extern StaticSemaphore_t xSemaphoreBuffer2;
extern EventGroupHandle_t xEventGroup;
extern uint16_t adc_measured;
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

}
void EXTI4_15_IRQHandler(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
	spi_start();
	HAL_GPIO_TogglePin(LED6_GPIO_PORT, LED6_PIN);
	EXTI->PR |= EXTI_PR_PIF4;
}
void SPI2_IRQHandler(void){
	//SPI2->DR = adc_measured;
	SPI2->DR = adc_measured;
	//HAL_GPIO_TogglePin(LED6_GPIO_PORT, LED6_PIN);
	while(((SPI2->SR & SPI_SR_FTLVL_0)!=SPI_SR_FTLVL_0)&&((SPI2->SR & SPI_SR_FTLVL_1)!=SPI_SR_FTLVL_1)){
		}
	while(((SPI2->SR & SPI_SR_BSY)!=SPI_SR_BSY)){
	}
	SPI2->CR1 &=~ SPI_CR1_SPE;
	
	//HAL_GPIO_TogglePin(LED6_GPIO_PORT, LED6_PIN);
}

void ADC1_COMP_IRQHandler (void)
{
		HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
	adc_measured =	ADC1->DR;	

	ADC1->ISR |= ADC_ISR_AWD;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	BaseType_t rt;
	//HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN,GPIO_PIN_SET);
		//HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN,GPIO_PIN_SET);
	rt=xEventGroupSetBitsFromISR(xEventGroup,eventg,&xHigherPriorityTaskWoken);
	//HAL_GPIO_WritePin(LED5_GPIO_PORT, LED5_PIN,GPIO_PIN_SET);
	if(rt==pdFALSE)	{
	
	}
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	
	
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
