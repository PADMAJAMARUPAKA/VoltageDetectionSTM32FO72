/*!*****************************************************************************
 * \file watchdog.c
 * \brief This module handles the independent watchdog functionality
 * \author padmaja
 ******************************************************************************/

/**** Includes ****************************************************************/
#include "adc.h"
#include "stm32f072b_discovery.h"
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
 void adc_init(void){
	 //CLOCK SELECTION
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; /* (1) */
	RCC->CR2 |= RCC_CR2_HSI14ON; /* (2) */
	while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) /* (3) */
	{
	/* For robust implementation, add here time-out management */
	}
	 //CALIBRATION	
	
	if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
	{
	ADC1->CR |= ADC_CR_ADDIS; /* (2) */
	}
	while ((ADC1->CR & ADC_CR_ADEN) != 0)
	{
/* For robust implementation, add here time-out management */
	}
	HAL_GPIO_TogglePin(LED5_GPIO_PORT, LED5_PIN);
	ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN; /* (3) */
	ADC1->CR |= ADC_CR_ADCAL; /* (4) */
	while ((ADC1->CR & ADC_CR_ADCAL) != 0) /* (5) */
	{
	/* For robust implementation, add here time-out management */
	}
	//ADC ENABLE
	if ((ADC1->ISR & ADC_ISR_ADRDY) != 0) /* (1) */
	{
	ADC1->ISR |= ADC_ISR_ADRDY; /* (2) */
	}
	ADC1->CR |= ADC_CR_ADEN; /* (3) */
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) /* (4) */
	{
	/* For robust implementation, add here time-out management */
	}
	ADC1->CFGR2 &= (~ADC_CFGR2_CKMODE);
	//Select continuous mode and analog watchdog
	ADC1->CFGR1 |= ADC_CFGR1_CONT|ADC_CFGR1_AWDEN;
	//Select overwrite the data
	ADC1->CFGR1 |= ADC_CFGR1_OVRMOD; 
	//Select 10 bit Resolution.
	ADC1->CFGR1	|= ADC_CFGR1_RES_0;
	//select channel0
	ADC1->CHSELR |= ADC_CHSELR_CHSEL10;
	//select sampling time
	ADC1->SMPR |= ADC_SMPR_SMP_0;
	ADC1->TR	=(adc_higherlimit<<16)+adc_lowerlimit;
	//enable analog watchdog interrupt
	ADC1->IER = ADC_IER_AWDIE;
	NVIC_EnableIRQ(ADC1_COMP_IRQn); /* (7) */
	NVIC_SetPriority(ADC1_COMP_IRQn,0);
}
void adc_start(void){
	ADC1->CR |= ADC_CR_ADSTART;
}
