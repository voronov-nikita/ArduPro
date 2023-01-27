// НЕЗАКОНЧЕНО!

const int switchPin = 8;
const int pinX = A0;
const int pinY = A1;
const int ledPin = 13;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(pinX, Input);
  pinMode(pinY, Input);
  pinMode(switchPin, OUTPUT);
  digitalWrite(switchPin, 1);
  Serial.begin(9600);
}

void loop(){
  int ledState = digitalRead(switchPin);
  digitalWrite(ledPin, ledState);
  
}