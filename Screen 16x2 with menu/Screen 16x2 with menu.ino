#include <LiquidCrystal.h> //импортируем библиотеку для работы с экраном

// создаем пины
constexpr uint8_t PIN_RS = 6;
constexpr uint8_t PIN_EN = 7;
constexpr uint8_t PIN_DB4 = 8;
constexpr uint8_t PIN_DB5 = 9;
constexpr uint8_t PIN_DB6 = 10;
constexpr uint8_t PIN_DB7 = 11;

// создаем обьект lcd 
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, 
PIN_DB5, PIN_DB6, PIN_DB7);

int name; //создаем переменную считывающая данные
int position = 0; //начальная позиция

// создаем список основного меню
String main-menu[][4]= {"number", "download", "start", "color"}
// создаем вложенный массив команд из 4x5
String command[][5]= {
  {"one", "two", "three", "four", "back"},
  {"new", "update", "install", "uninstall", "back"},
  {"open", "close", "Play", "clear", "back"},
  {"red", "green", "blue", "white", "black"}  
};

// один раз
void setup() {
  lcd.begin(16, 2); // определяем экран, как 2 строки на 16 столбцов
  lcd.setCursor(0, 0); //ставим курсор на 0 столбец и первую строку
  Serial.begin(9600); //заставляем общаться с монитором порта

}

// вечный цикл
void loop() {
  
}
