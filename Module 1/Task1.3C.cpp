
const int SW0_PIN = 4; // Switch 0
const int SW1_PIN = 7; // Switch 1
const int SRV_PIN = 3;  // Servo
const int INT0_PIN = 3; // Interrupt 0
const int INT1_PIN = 2; // Interrupt 1
bool servoActive = false;

void setup()
{
  pinMode(SW0_PIN, INPUT);
  pinMode(SW1_PIN, INPUT);
  pinMode(INT0_PIN, INPUT);
  pinMode(INT1_PIN, INPUT);
  pinMode(SRV_PIN, OUTPUT);
  
  analogWrite(SRV_PIN, 0);
  
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(INT0_PIN), handleSwitch, CHANGE);
  attachInterrupt(digitalPinToInterrupt(INT1_PIN), handleSwitch, CHANGE);
}

void handleSwitch(){
  bool sw0On = digitalRead(SW0_PIN);
  bool sw1On = digitalRead(SW1_PIN);
  servoActive = sw0On ^ sw1On;
  
  Serial.print("Switch 0: ");
  Serial.println(sw0On);
  Serial.print("Switch 1: ");
  Serial.println(sw1On);
  
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