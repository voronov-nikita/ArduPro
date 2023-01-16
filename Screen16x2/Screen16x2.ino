// Библиотека для работы с текстовым дисплеем
#include <LiquidCrystal.h>


String ls[][4]={
    {"one", "two", "three"},
    {"goodbye", "ok", "new"}, 
    {"code", "update", "install"}
 };

constexpr uint8_t PIN_RS = 6;
constexpr uint8_t PIN_EN = 7;
constexpr uint8_t PIN_DB4 = 8;
constexpr uint8_t PIN_DB5 = 9;
constexpr uint8_t PIN_DB6 = 10;
constexpr uint8_t PIN_DB7 = 11;
 
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

int name, new_name;
int position = 0;
void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  
}
void operation(){
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.print(ls[position]);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.print(ls[position+1]);
  }
void loop() {
  lcd.setCursor(0, 0);

  if(Serial.available() > 0){
    name = Serial.parseInt();
      Serial.println(name);
  }

  while(true){
    name = Serial.parseInt();
    Serial.println(name);
    switch(name){
      case 1:
          operation();
           break;
      case 2:
        operation();
        break;
         
    }
  }
//  switch(name){
//    case 0:
//      lcd.print(ls[position]);
//      lcd.setCursor(0, 1);
//      lcd.print(ls[position+1]);
//    case 1:
//      lcd.print(ls[0]);
//      lcd.setCursor(0, 1);
//      lcd.print(ls[1]);
//      break;
//    case 2:
//      lcd.print(ls[1]);
//      lcd.setCursor(0, 1);
//      lcd.print(ls[2]);
//      break;
//    default:
//      Serial.println(ls[1]);
//      break;
//    }
}
