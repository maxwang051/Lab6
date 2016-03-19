// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Max Wang, Connor Widder
// Date Created: 1/24/2015 
// Last Modified: 3/6/2015 
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "dac.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts


int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init(0);
	
  // other initialization
	int previous = 0;
	
  while(1){ 
		int button = Piano_In();
		
		if (button == 0x01 && (previous == 0)) {
			EnableInterrupts();
			Sound_Play(19157);
		}
		
		else if (button == 0x02 && (previous == 0)) {
			EnableInterrupts();
			Sound_Play(15197);
		}
		
		else if (button == 0x04 && (previous == 0)) {
			EnableInterrupts();
			Sound_Play(12755);
		}
		
		if (button == 0 && previous) {
			DisableInterrupts();
		}
		
		previous = button;

  }         
}


