/*!*****************************************************************************
 * \file led.c
 * \brief This module handles the led enabling.
 * \author padmaja
 ******************************************************************************/

/**** Includes ****************************************************************/
#include "led.h"
#include "stm32f072b_discovery.h"



/**** Private macros **********************************************************/

/**** Private types ***********************************************************/

/**** Private function prototypes *********************************************/

/**** Private constants *******************************************************/

/**** Private variables *******************************************************/
static GPIO_InitTypeDef  GPIO_InitStruct;
/**** Public constants ********************************************************/

/**** Public variables ********************************************************/

/**** Public function definitions *********************************************/

/******************************************************************************/
/**** Private function definitions ********************************************/
void led3_init(void) {
	/* -1- Enable each GPIO Clock (to be able to program the configuration registers) */
  LED3_GPIO_CLK_ENABLE();
	/* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = LED3_PIN;
  HAL_GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStruct);
}
void led4_init(void) {
	  LED4_GPIO_CLK_ENABLE();
	/* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = LED4_PIN;
  HAL_GPIO_Init(LED4_GPIO_PORT, &GPIO_InitStruct);
}
void led5_init(void) {
	  LED4_GPIO_CLK_ENABLE();
	/* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = LED5_PIN;
  HAL_GPIO_Init(LED5_GPIO_PORT, &GPIO_InitStruct);
}
void led6_init(void) {
	  LED4_GPIO_CLK_ENABLE();
	/* -2- Configure IOs in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = LED6_PIN;
  HAL_GPIO_Init(LED6_GPIO_PORT, &GPIO_InitStruct);
}
void AdcPin_init(void){
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	 GPIO_InitStruct.Pin = GPIO_PIN_0;
	 GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
}
void SpiPin_init(void)	{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	 GPIO_InitStruct.Pin = GPIO_PIN_12;
	 GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_13;
	 GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		GPIO_InitStruct.Pin = GPIO_PIN_15;
	 GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
			GPIO_InitStruct.Pin = GPIO_PIN_14;
	 GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
}
