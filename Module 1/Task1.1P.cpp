
const int POT_PIN = A0; // Potentiometer
const int SRV_PIN = 3;  // Servo
const float THRESHOLD = 0.5f;
bool overThreshold = false;

void setup()
{
  pinMode(POT_PIN, INPUT);
  pinMode(SRV_PIN, OUTPUT);
  
  analogWrite(SRV_PIN, 0);
  
  Serial.begin(9600);
}

void loop()
{
  float reading = analogRead(POT_PIN) / 675.0f;
  // Read and normalise potentiometer value
  
  overThreshold = reading > THRESHOLD;
  
  if(overThreshold){
    analogWrite(SRV_PIN, 1000);
  } else {
    analogWrite(SRV_PIN, 0);
  }
  
  Serial.println(reading);
  // Print normalised potentiometer value
}