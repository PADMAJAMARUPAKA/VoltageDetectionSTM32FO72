/*!*****************************************************************************
 * \file timer.c
 * \brief This module handles the timer 3 functionality
 * \author padmaja
 ******************************************************************************/

/**** Includes ****************************************************************/
#include "timer.h"
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
void TimerGpio_Init(void){
	//CLOCK ENABLE FOR PORT C
	RCC->AHBENR |=RCC_AHBENR_GPIOCEN;
	//GPIO PC8 AS TIMER (ALTERNATE FUNCTION 0)
	GPIOC->MODER|=GPIO_MODER_MODER6_1;
}
void Timer3_Init(void) {
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

}


