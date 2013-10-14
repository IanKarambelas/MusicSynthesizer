//*****************************************************************************
//
// MusicSynthesizer.c
// Plays "Mary had a little lamb" tune on the on-board speaker
// Uses Timer0 and PWM peripherals
//
//*****************************************************************************

#include "MusicSynthesizer_includes.h"      // Has all the required header files
#include "pwm_driver.h"                     // PWM peripheral functions
#include "timer0_driver.h"                  // Timer0 peripheral functions
#include "scale.h"                          // Contains frequency definitions for the musical notes

/* *************************************************
 *		Global Definitions
 * ************************************************ */




/* *************************************************
 *		Global Variables
 * ************************************************ */

volatile unsigned int gHandle = 0;

unsigned int songMary[60] = { SILENCE, E4, SILENCE, D4, SILENCE, C4,
							  SILENCE, D4, SILENCE, E4, SILENCE, E4,
							  SILENCE, E4, E4, SILENCE, D4, SILENCE,
							  D4, SILENCE, D4, D4, SILENCE, E4,
							  SILENCE, G4, SILENCE, G4, G4, SILENCE,
							  E4, SILENCE, D4, SILENCE, C4, SILENCE,
							  D4, SILENCE, E4, SILENCE, E4, SILENCE,
							  E4, SILENCE, E4, SILENCE, D4, SILENCE,
                              D4, SILENCE, E4, SILENCE, D4, SILENCE,
							  C4, C4, C4, C4, SILENCE, SILENCE };


//*****************************************************************************
//
// The Timer 0 interrupt handler.
//
// Increments a counter to point to the next correct note of the song
//
//*****************************************************************************
void Timer0IntHandler(void)
{
    // Clear the timer interrupt.
       TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Increment a counter till it reaches the end of the array
    // After that counter rolls over
       if(++gHandle > 58)
		    gHandle = 0;

}



//*****************************************************************************
//
// MAIN function
//
//*****************************************************************************
int main(void){

    // Set the clocking to run directly from the crystal.
       SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                      SYSCTL_XTAL_8MHZ);

    // Initialize the OLED display and write status.
       RIT128x96x4Init(1000000);
       RIT128x96x4StringDraw("MUSIC SYNTHESIZER", 20, 0, 15);

    // Initialize the PWM Peripheral
	   PWM_Init();  // Custom function defined in pwm_driver.c

	// Set frequency of PWM Generator 0
	   PWM_SetFreq(songMary[0]);    // Custom function defined in pwm_driver.c

    // Set Pulse Width of PWM output PW1 to 25%
       PWM_SetPW(25);	// Custom function defined in pwm_driver.c

	// Enable the PWM1 output signals.
       PWMOutputState(PWM0_BASE, PWM_OUT_1_BIT, true);

	// Enable the timer/counter for PWM Generator 0 block.
       PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    // Set Timer 0 Interrupt to trigger every 1/4 second
	   Init_Timer0(2000000); // Custom function defined in timer0_driver.c

    // Enable processor interrupts.
       IntMasterEnable();

	   while(1)
	    {
		   // Play the note on the on-board speaker

           // Set the frequency of the next note
              PWM_SetFreq(songMary[gHandle]);

		}

    return(0);
}



