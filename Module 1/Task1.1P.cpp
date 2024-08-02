
const int POT_PIN = A0; // Potentiometer
const int SRV_PIN = 3;  // Servo

void setup()
{
  pinMode(POT_PIN, INPUT);
  pinMode(OUT_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
  float x = analogRead(POT_PIN) / 675.0f;
  // Read and normalise potentiometer value
  analogWrite(OUT_PIN, 255 - (int)(x * 255.0f));
  // Write value to servo, with 0 = no turn, 1 = max turn
  Serial.println(x);
  // Print normalised potentiometer value
}