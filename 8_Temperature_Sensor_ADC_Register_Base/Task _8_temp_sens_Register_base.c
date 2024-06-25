/*
 * Maaz khan
 * 19jzele0320
 *
 ********************************************************************************
                     Temperature Sensor ADC Register Base
 ********************************************************************************
 */

//header files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "F2837xD_device.h"
#include "F28x_Project.h"
#include "F2837xD_Examples.h"

#include "driverlib.h"
#include "device.h"

//12 Bit ADC
#define     EX_ADC_RESOLUTION       12
#define ADCA_BASE                 0x00007400U

// Function prototype
void ConfigADC();
void initADC_SOC(void);

/////// MAAZ KHAN   ////////////////
uint16_t Adc_Result_1;
float ADCINA0_1A, Temperature;

void main(void)
{
    /////// MAAZ KHAN   ////////////////

    // Initialize all particular clock
    Device_init();
    // Initialize Gpio's
    Device_initGPIO();

    Interrupt_initModule();
    // Initialize Pie Vector Table
    Interrupt_initVectorTable();

    /////// MAAZ KHAN   ////////////////

    // Calling functions in main
    ConfigADC();
    initADC_SOC();
    EINT;
    ERTM;

    while (1)
    {
        /////// MAAZ KHAN   ////////////////

        // Convert, wait for completion, and store results
        AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1;


        while (AdcaRegs.ADCINTFLG.bit.ADCINT1 == false)
        {

        }
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;

        // Store results
        Adc_Result_1 = AdcaResultRegs.ADCRESULT0;


        // Convert into voltage
        ADCINA0_1A = Adc_Result_1 * (3.3/ 4096);
        // Show Temperature
        Temperature = ADCINA0_1A*(100/10);


    }
}

/////// MAAZ KHAN   ////////////////

void ConfigADC()
{
    /////// MAAZ KHAN   ////////////////
    EALLOW;
    // Configure ADC clock divider
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6;

    // Configure ADC resolution in 12 bit mode which is single ended
#if(EX_ADC_RESOLUTION == 12)
    {
        // 12-bit resolution
        AdcaRegs.ADCCTL2.bit.RESOLUTION = 0; // 12-bit resolution
    }
    // Differential mode 16 bit
#elif(EX_ADC_RESOLUTION == 16)
    {
        // 16-bit resolution
        AdcaRegs.ADCCTL2.bit.RESOLUTION = 1;
    }
#endif
    //AdcaRegs.ADCCTL2.bit.PRESCALE = 6; // Clock divider for ADCCLK is 4

    // Configure ADC interrupt pulse generation
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1; // End of conversion pulse

    // Enable ADC module
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ= 1;

    // Delay for 1 ms
    DELAY_US(1000);
    EDIS;
}

/////// MAAZ KHAN   ////////////////

void initADC_SOC(void)
{
    // Configure SOC0 for ADCINA0
    EALLOW;
    // Trigger SOC0 using software delay
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 0;
    // Channel selection for SOC0
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 0;
    // Sample window is 14 SYSCLK cycles , in Acquisition Phase
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 14;
    // Enable Force1 Register for SOC0
    AdcaRegs.ADCSOCFRC1.all = 0x155;

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;
    // Enable interrupt
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;
    // Clear interrupt flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    EDIS;
}

