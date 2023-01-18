// Библиотека для работы с текстовым дисплеем
#include <LiquidCrystal.h>
#include <GyverEncoder.h>

String main_menu[][4]={
  {"hello", "goodbye", "ok", "new"},
  {"play", "stop", "cancel"},
  {"start", "file", "cancel"},
  {"lib", "None", "cancel"},
  {"e", "not", "ll"}
};



int position_list = 0, position_catalog = 0;

#define CLK 2
#define DT 3
#define SW 4

constexpr uint8_t PIN_RS = 6;
constexpr uint8_t PIN_EN = 7;
constexpr uint8_t PIN_DB4 = 8;
constexpr uint8_t PIN_DB5 = 9;
constexpr uint8_t PIN_DB6 = 10;
constexpr uint8_t PIN_DB7 = 11;


Encoder enc(CLK, DT, SW, TYPE2);
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);

String clearing = "                 ";
void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);

  enc.setType(TYPE2);
  
}
void loop() {
  enc.tick();
  if (enc.isRight()){
        position_catalog--;
        lcd.setCursor(0, 0);
        lcd.print(clearing);
        lcd.setCursor(0, 1);
        lcd.print(clearing);
        }
  if (enc.isLeft()){
        position_catalog++;
        lcd.setCursor(0, 0);
        lcd.print(clearing);
        lcd.setCursor(0, 1);
        lcd.print(clearing);
      }
  if (enc.isClick()){
          if (main_menu[position_list][position_catalog] == "cancel"){
            position_list = 0;
            position_catalog = 0;
            }
          else{
          position_list = position_catalog+1;
          position_catalog = 0;
          }
        }
        
  if (position_catalog > 2){
        position_catalog = 2;
        }
  else if (position_catalog < 0){
        position_catalog = 0;
        }

      
      lcd.setCursor(0, 0);
      lcd.print(main_menu[position_list][position_catalog]);
      lcd.setCursor(0, 1);
      lcd.print(main_menu[position_list][position_catalog+1]);

    
}
