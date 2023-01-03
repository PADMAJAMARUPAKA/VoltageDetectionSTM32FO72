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
	IWDG->RLR = 0XC35;
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
/*void Timer3_Init(void) {
	//CLOCK ENABLE FOR TIMER3
	RCC->APB1ENR |=RCC_APB1ENR_TIM3EN;
	//Counter in upcounting mode
	TIM3->CR1 |= TIM_CR1_ARPE;
	TIM3->CR1 |=TIM_CR1_DIR;
	//Enable the update interrupt
	TIM3->DIER|=TIM_DIER_UIE;
	//Configure timer for 1sec interrupt and clock input to timer as 1khz.
	TIM3->PSC =47999;
	TIM3->ARR =1000-1;
	TIM3->CR1 |=TIM_CR1_CEN;
	//Enable the interrupt as high priority.
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_SetPriority(TIM3_IRQn,0);
}*/