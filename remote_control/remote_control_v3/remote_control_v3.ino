// Atmega 32
// Clock frequency 1Mhz
//remote control processing - code

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 


uint16_t Start=0;
volatile uint16_t Stop = 0;
uint16_t time_diff = 0;
volatile uint16_t difference_storage[24];
uint8_t capture_count=0;
volatile uint16_t rem_instr = 0;



// Set Time Counter Mode to Normal
TCCR1A &= ~(1<<WGM10); 
TCCR1A &= ~(1<<WGM11);
TCCR1B &= ~(1<<WGM12); 
TCCR1B &= ~(1<<WGM13); 

//Input Capture detecting the rising edge
TCCR1B |= (1 << ICES1);

// Setting the prescaler to 8
TCCR1B |=  (1<<CS11);

// Disable Input Capture Interrupt
TIMSK |= (1<<TICIE1);

// Setting PORTD as Input
DDRD = 0;

// Disable internal PULLUP of the Input Capture Pin
PORTD &= ~(1<<PORTD6);




int main(void){
while(1){}


  return 0;
}


ISR(TIMER1_CAPT_vect){
//Calculating the time between two rising edges
Start = ICR1; 	//Timestamp of the first rising edge
time_diff = Start-Stop; // Time between two rising edges
Stop = ICR1; // Storing the timestamp of the first rising edge

if(time_diff<=300){ //filtering only important times

capture_count++; //Counting the input captures

	if(capture_count<26){ //getting the first 25 important numbers
		difference_storage[capture_count-1]=time_diff; 
	}
	else{ //processing the difference_storage array
		rem_instr=0; // setting the instruction to zero
			for(uint8_t help_count=16; help_count<24;help_count++){ // deciding if it is a zero or one
				if(difference_storage[help_count]>200){
					rem_instr |= (1<<(help_count-16));
				}				
				else{
					rem_instr &= ~(1<<(help_count-16)); 
				} 
			}

_delay_ms(1000); //ugly but useful.. safetyinstruction that the receiving ended

capture_count = 0;

	}
	}
}




     
                   

