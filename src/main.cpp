#include <Arduino.h>

const int trig=2;  // make it constant
#define trig 2 // same as line 3
#define echo 3
// unsigned no sign, positive
// long: an int with twice memory
unsigned long t0=0;
unsigned long t1=0;
unsigned long t2=micros ();
bool available=false;

// it gets called when the echo changes
void interrupt_function(){
   if(digitalRead(echo)==HIGH){
       Serial.println("The voltage is high, it's rising");
       t1= micros();
   }
   else if(digitalRead(echo)==LOW){
       Serial.println("the voltage is low, it's decreasing");
       t2=micros();
       Serial.println("distance"+ String(343*(t2-t1)/2*pow(10,-4))+" cm"); // 343 is speed of sound in m/s
   }
// print if it is rising, otherwise print it's falling

   Serial.println("Hello Im an interrupt");
}

void setup(){
//set up serial and pins
Serial.begin(9600);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);

// Timer1.initialize(100000)
// Timer1.attachInterrupt(trigger);

//Interrupt function to runs when the echo changes:
attachInterrupt(digitalPinToInterrupt(echo),interrupt_function,CHANGE);

}

void loop(){

if(millis()-t0>500){ // If 0.5 second has passed
   digitalWrite(trig,HIGH);
   // delay(0.01);
   delayMicroseconds(10);
   digitalWrite(trig,LOW);
   t0=millis();
}

if(available){
   noInterrupts(); // turns off all interrupts
   unsigned long t1a=t1;
   unsigned long t2a=t2;
   Serial.print(0.0343*(t2-t1)/2.0);
   available=false;

}

   // delay(100);   
}


// step 1: take the time using millis, store it in t0
// step 2:take the time later, and if t-t0 is more than 100, 100ms have passed)



