#include <GyverEncoder.h> // импортируем библиотеку для работы с энкодером
#include <LiquidCrystal.h> //импортируем библиотеку для работы с экраном

// создаем пины
// энкодер
#define CLK 2
#define DT 3
#define SW 4
// экран
constexpr uint8_t PIN_RS = 6;
constexpr uint8_t PIN_EN = 7;
constexpr uint8_t PIN_DB4 = 8;
constexpr uint8_t PIN_DB5 = 9;
constexpr uint8_t PIN_DB6 = 10;
constexpr uint8_t PIN_DB7 = 11;

// создаем обьект lcd 
LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_DB4, 
PIN_DB5, PIN_DB6, PIN_DB7);

// создаем обьект enc
Encoder enc(CLK, DT, SW);

int name; //создаем переменную считывающая данные
int position_catalog = 0, position_list = 0; //начальная позиция

// создаем список основного меню
String main_menu[][5]= {"number", "download", "start", "color", ""};
int len_arr = 5;
// создаем вложенный массив команд из 4x5
String command[][5]= {
  {"one", "two", "three", "four", "back"},
  {"new", "update", "install", "uninstall", "back"},
  {"open", "close", "Play", "clear", "back"},
  {"red", "green", "blue", "white", "black"}  
};

// один раз
void setup() {
  enc.setType(TYPE2); //тип энкодера (круглый-TYPE2)
  
  lcd.begin(16, 2); // определяем экран, как 2 строки на 16 столбцов
  lcd.setCursor(0, 0); //ставим курсор на 0 столбец и первую строку
  
  Serial.begin(9600); //заставляем общаться с монитором порта

}

// вечный цикл
void loop() {
  enc.tick();  // отслеживание работы энкодера
  // если энкодер повернулся
  if (enc.isTurn()){  
    // если вправо
    if (enc.isRight()){
      if (position_list < len_arr)
        position_list++;
    }
    // если влево
    if (enc.isLeft()){
      if (position_list > len_arr)
        position_list--;    
    }
  }
  // если на энкодер нажали
  if (enc.isClick()){
    position_catalog = position_list;
    position_list = 0;        
  }    
}
