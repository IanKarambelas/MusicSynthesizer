#include "MusicSynthesizer_includes.h"
#include "timer0_driver.h"


/* *******************************************************
 * Function: Init_Timer0
 *
 * Inputs: Number of Ticks
 *
 * Outputs: None
 *
 * Date: 7/8/2013
 *
 * Description: Enables the peripherals for timer 0,
 * configures it as a single 32 bit timer, instead
 * of 2 seperate 16 bit timers, and enables the interrupts
 * for Timer 0
 * ****************************************************** */
void Init_Timer0(unsigned long time)
{
    // Enable Timer 0 peripheral.
       SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	// Configure Timer 0 as 32-bit periodic timers.
       TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	// Load starting value into Timer 0
	// Since Timer 0 is 32 bit, both block A & B will be used as a single Timer
       TimerLoadSet(TIMER0_BASE, TIMER_A, time);

    // Enable Time0 Interrupt source.
       IntEnable(INT_TIMER0A);

    // Enable Timer0 to generate interrupt when Timer A times out.
       TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Enable the timers.
       TimerEnable(TIMER0_BASE, TIMER_A);

}



