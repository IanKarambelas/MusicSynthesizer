#include "MusicSynthesizer_includes.h"
#include "pwm_driver.h"

/* *************************************************
 *		Global Definitions
 ************************************************* */



/* *************************************************
 *		Global Variables
 ************************************************* */
unsigned long freq;


/* *************************************************
 * Function: PWM_Init
 *
 * Inputs: None
 *
 * Outputs: None
 *
 * Date: 7/11/2013
 *
 * Description: This function initializes the PWM
 * peripherals.
 * ********************************************** */
void PWM_Init(void)
{

    // Set PWM Clock Divider to divide by 1
       SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    // Initialize GPIO Port corresponding to PWM output PWM1
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Enable the PWM0 peripheral.
       SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    // Set GPIO pin as PWM output
       GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_1);

}



/* *************************************************
 * Function: PWM_SetFreq
 *
 * Inputs: PWM Generator, Frequency
 *
 * Outputs: None
 *
 * Date: 7/11/2013
 *
 * Description: This function takes in a pwm
 * generator 0 and a user frequency and
 * sets the PWM frequency of the corrseponding
 * PWM generator.
 * ********************************************** */
void PWM_SetFreq(unsigned long frequency)
{

    unsigned long ulPeriod;

    // Set global frequency variable to the frequency of pwm generator
       freq = frequency;

    // Compute the PWM period based on the system clock.
       ulPeriod = SysCtlClockGet() / frequency;

    // Configure the PWM generator 0 for UP/DOWN and NO SYNC mode
       PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    // Set the PWM period to 'frequency' (A) Hz.
       PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, ulPeriod);

}


/* *************************************************
 * Function: PWM_SetPW
 *
 * Inputs: PWM Channel, Channel Pulse Width
 *
 * Outputs: None
 *
 * Date: 7/11/2013
 *
 * Description: This function takes in a duty-cycle
 * value. The function calculates pulse-width and sets
 * the PWM output pin PWM1 to a new pulse width.
 * ********************************************** */
void PWM_SetPW(unsigned int PW)
{
    unsigned long duty;
    unsigned long ulPeriod;

    // Calculate period for user frequency
       ulPeriod = SysCtlClockGet() / freq;

    // Calculate pulsewidth knowing the period and duty cycle
       duty = (ulPeriod * PW) / 100;

    // Set PWM pulse width for PWM output PW1
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, duty);

}





