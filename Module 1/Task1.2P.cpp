
const int BUT_PIN = 2; // Button
const int SRV_PIN = 3;  // Servo
bool servoActive = false;

void setup()
{
  pinMode(BUT_PIN, INPUT);
  pinMode(SRV_PIN, OUTPUT);
  
  analogWrite(SRV_PIN, 0);
  
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(BUT_PIN), handleButton, RISING);
}

void handleButton(){
  servoActive = !servoActive;
  
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
  Serial.println(digitalRead(BUT_PIN));
}