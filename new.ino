// Библиотека для работы с текстовым дисплеем
#include <LiquidCrystal.h>
 
constexpr uint8_t PIN_RS = 6;
constexpr uint8_t PIN_EN = 7;
constexpr uint8_t PIN_DB4 = 8;
constexpr uint8_t PIN_DB5 = 9;
constexpr uint8_t PIN_DB6 = 10;
constexpr uint8_t PIN_DB7 = 11;
 
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);
String name ="";
void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  
}
 
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("My name:");

  if(Serial.available() > 0){
    name = Serial.readString();
  }
  lcd.print(name);
  lcd.print("         ");
}
