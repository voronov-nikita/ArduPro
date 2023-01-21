#include <NewPing.h>

NewPing sonar(12, 11, 200);

void setup(){
  Serial.begin(9600);
}

void loop(){
  
  Serial.println(sonar.ping_cm());

}