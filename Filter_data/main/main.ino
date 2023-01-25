// Датчик расстояния без бибилиотек
int trigPin = 12; 
  int echoPin = 13;
void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, OUTPUT);
  }

int dist(int trigPin, int echoPin){
  int duration, distance;
  // для большей точности установим значение LOW на пине Trig
  digitalWrite(trigPin, 0); 
  delayMicroseconds(2); 
  // Теперь установим высокий уровень на пине Trig
  digitalWrite(trigPin, 1);
  // Подождем 10 μs 
  delayMicroseconds(10); 
  digitalWrite(trigPin, 0); 
  // Узнаем длительность высокого сигнала на пине Echo
  duration = pulseIn(echoPin, 1); 
  // Рассчитаем расстояние
  distance = duration / 58;
  // Выведем значение в Serial Monitor
  return distance;
  }
  
void loop(){
  Serial.print(dist(trigPin, echoPin));
  Serial.print(" cm");
  delay(100);
  }
