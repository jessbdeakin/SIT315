#include <avr/interrupt.h>

const int SW_PIN_N = 3;
const int SW_PINS[SW_PIN_N] = {
  5, 6, 7
};
volatile bool swReading[3];

const int SRV_PIN = 3;  // Servo
const int LED_PIN = 2; // LED
volatile bool servoActive = false;
volatile bool ledActive = false;

void setup()
{
  for(int i = 0; i < SW_PIN_N; i++)
    pinMode(SW_PINS[i], INPUT);
  
  pinMode(SRV_PIN, OUTPUT);
  
  analogWrite(SRV_PIN, 0);
  
  Serial.begin(9600);
  
  noInterrupts();
  
  // PC Interrupt
  // We are using Port D pins
  PCICR |= 0b00000100;
  
  for(int i = 0; i < SW_PIN_N; i++)
    PCMSK2 |= 0b1 << SW_PINS[i];
  
  // Timer interrupt
  TCCR1A = 0;
  TCCR1B = (TCCR1B & 0b11111000) | 0b00000101; 
    // 16 MHz / 1024 = 15625 Hz
  TIMSK1 |= 0b00000010; // enable compare against comparand A
  OCR1A = 15625 * 1; // set comparand A
    // 2 Hz
  TCNT1 = 0; // reset counter
  
  interrupts();
}

ISR(TIMER1_COMPA_vect){
  TCNT1 = 0; // reset counter
  ledActive = !ledActive;
  digitalWrite(LED_PIN, ledActive);
}

ISR(PCINT2_vect){
  bool singleOn = false;
  bool anyOn = false;
  for(int i = 0; i < SW_PIN_N; i++){
    bool swOn = digitalRead(SW_PINS[i]);
    Serial.print("Switch ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(swOn);
    if(swOn){
      if(!anyOn){
        anyOn = true;
        singleOn = true;
      } else {
        singleOn = false; 
      }
    }
  }
  
  servoActive = singleOn;
  
  if(servoActive){
    Serial.println("Servo is active!");
    analogWrite(SRV_PIN, 1000);
  } else {
    Serial.println("Servo is inactive!");
    analogWrite(SRV_PIN, 0);
  }
}

void loop()
{
}