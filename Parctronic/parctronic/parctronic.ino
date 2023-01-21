#include <NewPing.h>

#define Pisk = 3
#define Pin_sonar1 = 12
#define Pisk_sonar2 = 11

int len_pisk = 1000;

NewPing sonar(Pin_sonar1, Pin_sonar2, 500);

void setup() {
  Serial.begin(9600);
}
void loop() {

  len = sonar.ping_cm();
  delay(10);
  if (len>=100){
    tone(Pisk, len_pisk);  // пищать на пине 3, 1 кГц
    delay(500);
    noTone(Pisk);      // не пищать
    delay(500);
  }
  else{
    noTone(Pisk);  
  }
}