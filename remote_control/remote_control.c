//Arduino Uno
// Clock frequency 16Mhz
// mehrmalige gleiche ausgabe!

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t Differenz = 0;
volatile uint8_t sema =0;
volatile uint16_t Stop = 0;
uint16_t befehl = 0;
uint8_t vergleich[8];
volatile uint16_t test_array[24];
uint8_t count=0;
void setup() {
TCCR1A &= ~(1<<WGM10); 
TCCR1A &= ~(1<<WGM11);
TCCR1B &= ~(1<<WGM12); 
TCCR1B &= ~(1<<WGM13); 
TCCR1B |= ((1 << ICES1)); //Input capture detecting rising flank  
TCCR1B |=  (1<<CS11)|(1<<CS10)  ;
TIMSK1 |= (1<<ICIE1);
PORTB &= ~(1<<PORTB0);
DDRB =0;


Serial.begin(9600);

              }
void loop(){

if(sema){
sema=0;
if(Differenz<=600){//geändert!
count++;

if(count<26){
test_array[count-1]=Differenz;}

else{
TIMSK1 &= ~(1<<ICIE1);  
sema=0;  
befehl=0;
for(int zuzu=16;zuzu<24;zuzu++){
if(test_array[zuzu]>400){
befehl |= (1<<(zuzu-16));
}else{befehl &= ~(1<<(zuzu-16)); } 
}


  Serial.println(befehl);
  delay(500);  

count = 0;
TIFR1 &= ~(1<<ICF1);
TIMSK1 |= (1<<ICIE1);   



}}}}
   
  
  
  
  

ISR(TIMER1_CAPT_vect){

uint16_t Start = ICR1;
Differenz = Start-Stop;
Stop = ICR1;
sema = 1;


}

     
                   
