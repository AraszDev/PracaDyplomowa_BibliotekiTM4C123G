/*
 * adc_config.h
 *
 *  Created on: 8 lis 2015
 *      Author: palka
 */

#ifndef ADC_ADC_TIMER_INTERRUPT_DEMO_ADC_CONFIG_H_
#define ADC_ADC_TIMER_INTERRUPT_DEMO_ADC_CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h" //includes valid INT_ values for IntEnable function parameter
#include "driverlib/adc.h" //definitions for using the ADC driverS
#include "driverlib/timer.h" //macros for Timer API


	//Sequencer 1 generates 4 samples
	/* array that will be used for storing the data read from the ADC FIFO.
	 * Array must be as large as the FIFO for the sequencer in use.
	 *
	 * Sequencer 0 : 8 samples
	 * Sequencer 1 : 4 samples
	 * Sequencer 2 : 4 samples
	 * Sequencer 3 : 1 samples
	 *
	 * This library uses sequencer 1
	 */
	uint32_t ui32ADC0Value[4]; //data buffer

	volatile uint32_t ui32ADC0ValueAvg_CH4; //average value readed from PD3
	volatile uint32_t ui32ADC0ValueAvg_CH5;	//average value readed from PD2

	volatile uint32_t ui32VoltageMotorLeft; //voltage on channel 4 (PD3)
	volatile uint32_t ui32VoltageMotorRight; //voltage on channel 5 (PD2)

	volatile uint32_t ui32CurrentMotorLeft; //current on channel 4 (PD3)
	volatile uint32_t ui32CurrentMotorRight; //current on channel 5 (PD2)


    /*
	* Calls ADC0_Init, Timer0_Init and Interrupts_Enable function
	* most general function to be called from the outside
    */
	void CSTInit(void);

    /*
	* Initialize ADC0 sequencer 1
	* sequencer 1 gets 4 samples (averaged)
	* samples 0 and 1 from PE3, samples 2, 3 from PE2
	* it calculates average voltage and store it in ui32VoltageMotorRight/Left
	* it also calculate it to get ui32CurrentMotorRight/Left
	* (results are stored in this variables)
    */
	void CSTInitADC0(void);

    /*
	* Initialize TIMER0 as ADC trigger
	* 32 bit periodic timer
	* frequency = 10Hz
    */
	void CSTInitTimer0(void);

    /*
	* Initialize processor, TIM0 and ADC0 interrupts
	* ** NOTE! **
	* to get ADC0 interrupt to work ADC0IntHandler MUST be placed in interrupt vector
	* (tm4c123gh6pm_startup_ccs.c file) and declared in this file under "extern void _c_int00(void);"
    */
	void CSTEnableInterrupts(void);

#endif /* ADC_ADC_TIMER_INTERRUPT_DEMO_ADC_CONFIG_H_ */
