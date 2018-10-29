#define P_PIN A0
#define INTER 2

// ================================================================

void ReadAnalog()
{
  Serial.print("Analog: ");
  int a = analogRead(P_PIN);
  Serial.print(a); // From 0 - 1023
  Serial.print("\tBrightness: ");
  //int mapped = map(a, 0, 1023, 0, 255);
  int mapped = a / 4;
  Serial.print(mapped);
  Serial.print("\n");
}

volatile boolean a = false;
boolean b = !a;

void Interruption()
{
  a = digitalRead(INTER);
}
  

// ================================================================

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(INTER, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTER), Interruption, CHANGE);
  a = digitalRead(INTER);
  b = !a;

}

void loop() 
{
  // put your main code here, to run repeatedly:
  ReadAnalog();

}
