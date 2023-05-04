/*!*****************************************************************************
 * \file watchdog.c
 * \brief This module handles the independent watchdog functionality
 * \author padmaja
 ******************************************************************************/

/**** Includes ****************************************************************/
#include "spi.h"
#include "stm32f072b_discovery.h"
#include "stm32f072xb.h"
extern uint16_t adc_measured;

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
 void spi_init(void){
	//intialize clock for spi peripheral.
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	 //
	 SPI2->CR1 |= SPI_CR1_BR;
	 SPI2->CR1	|= SPI_CR1_LSBFIRST;
	 //SPI2->CR1 |= SPI_CR1_SSM;
	 SPI2->CR1 |= SPI_CR1_MSTR;
	 SPI2->CR2 |= SPI_CR2_DS_0 | SPI_CR2_DS_3;
	 SPI2->CR2 |= SPI_CR2_SSOE;
	 //SPI2->CR2 |= SPI_CR2_NSSP;
	 SPI2->CR2 |= SPI_CR2_TXEIE;
	NVIC_EnableIRQ(SPI2_IRQn); /* (7) */
	NVIC_SetPriority(SPI2_IRQn,1);
	 
	 
	 
}

void spi_start(void){

	SPI2->CR1 |= SPI_CR1_SPE;
}
