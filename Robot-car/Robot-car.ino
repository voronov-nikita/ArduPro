// инициализируем переменные
#define trigPin = 12
#define echoPin = 13

#define motor1 = 7
#define motor2 = 8

// Датчик растояния
int dist(int trigPin, int echoPin){
  int duration, distance;

  digitalWrite(trigPin, 0); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, 1);
  delayMicroseconds(10); 
  digitalWrite(trigPin, 0); 
  
  duration = pulseIn(echoPin, 1); 
  distance = duration / 58;
  
  return distance;
}

void setup() {
  Serial.begin(9600);

}

void loop() {
  

}
