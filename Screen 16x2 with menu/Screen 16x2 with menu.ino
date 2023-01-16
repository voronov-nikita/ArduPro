#include <LiquidCrystal.h>

constexpr uint8_t PIN_RS = 6;
constexpr uint8_t PIN_EN = 7;
constexpr uint8_t PIN_DB4 = 8;
constexpr uint8_t PIN_DB5 = 9;
constexpr uint8_t PIN_DB6 = 10;
constexpr uint8_t PIN_DB7 = 11;

LiquidCrystal lcd();

int name;

String ls[][3]= {
  {"one", "two", "three"},
  {"new", "update", "install"},
  {"open", "close", "Play"}
};

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
