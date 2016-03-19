// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "tm4c123gh6pm.h"

int Index;
const int SineWave[16] = {32,44,55,62,63,62,55,44,32,20,9,2,0,2,9,20};

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Called once, with sound initially off
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
// Output: none
void Sound_Init(uint32_t period){
	DAC_Init();
	Index = 0;
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000;
	NVIC_ST_CTRL_R = 0x07;
	
	SYSCTL_RCGCGPIO_R |= 0x20;
	int delay = SYSCTL_RCGCGPIO_R;
	
	// initialize port f
	GPIO_PORTF_DIR_R |= 0x08;
	GPIO_PORTF_AFSEL_R &= ~0x08;
	GPIO_PORTF_DEN_R |= 0x08;
}


// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Input: interrupt period
//           Units to be determined by YOU
//           Maximum to be determined by YOU
//           Minimum to be determined by YOU
//         input of zero disable sound output
// Output: none
void Sound_Play(uint32_t period){
	NVIC_ST_RELOAD_R = period - 1;
}

void SysTick_Handler(void) {
	GPIO_PORTF_DATA_R ^= 0x08;
	Index = (Index+1) & 0x0F;
	DAC_Out(SineWave[Index]);
}