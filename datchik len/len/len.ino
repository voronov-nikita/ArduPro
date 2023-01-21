// Библиотека для радара
#include <NewPing.h>

// Создаем обьект радара
NewPing sonar(12, 11, 200);

void setup(){
  Serial.begin(9600);
}

void loop(){
  // выводим значение радара
  Serial.println(sonar.ping_cm());

  delay(30);

}