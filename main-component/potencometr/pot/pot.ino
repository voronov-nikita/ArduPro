int Pin1 = 11, Pin2 = A0;
int pot;
void setup(){
  // инициализируем пины
  pinMode(Pin1, OUTPUT);
  // получаем значение
  pinMode(Pin2, INPUT);
  // подключаем монитор порта
  Serial.begin(9600); 

}

void loop(){
  pot = analogRead(Pin2); // записываем значение
  analogWrite(Pin1, pot/3); // преобразуем сигнал потенцометра в сигнал
  Serial.println(pot);  // выводим значение потенцометра
}