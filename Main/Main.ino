// RedLed - Digital output pin number
// Data   - Int that stores serial data
int RedLed = 2;
int data;

void setup() {
  
  Serial.begin(9600);
  pinMode(RedLed, OUTPUT);
  digitalWrite(RedLed, LOW);
}

// the loop function runs over and over again forever
void loop() {
  while (Serial.available())
  {
    data = Serial.read();
  }

  if (data == '1')
  {
    digitalWrite(RedLed, HIGH);
    Serial.println("LED turned on!");
  }

  else if (data == '0')
  {
    digitalWrite(RedLed, LOW);
    Serial.println("LED turned off!");
  }

}

/*Test*/