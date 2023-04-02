// https://youtu.be/2KWZqm1U9uM - доделать!
#include "stDHT.h"

#define dw digitalWrite
#define ar analogRead

int rate = 327;
int stoped = 60;

int list_pin_read[6] = {A0, A1, A2, A3, A4, A5};
int list_soil_values[6];
int list_air_values[4][2];

DHT sensor(DHT11);

void setup() {
  Serial.begin(9600);
  
  // определение пинов для почвы
  for (int i=7; i<=12; i++) pinMode(i, OUTPUT);   
  
  // определение пинов для воздуха
  for (int i=1; i<1+4; i++){
    pinMode(i, INPUT);
    dw(i, 1);
  }    
}

void loop() {
  // формирование списка со значениями датчика почвы
  for (int i=7; i<7+6; i++) list_soil_values[i-7] = new_data_sensor(i, list_pin_read[i-7]);
  // формирование списка со значениями температуры и влажности воздуха
  for (int pin=1; pin < 1+4; pin++){
    // считываем значения
    int temperature = sensor.readTemperature(pin);
    int humidity = sensor.readHumidity(pin);

    // аполняем список
    list_air_values[pin-1][0] = temperature;
    list_air_values[pin-1][1] = humidity;
  }
  // задержка при опрашивании датчика в <часах>
  delay(stoped*1000*60*60);                                                        
}

// опрашивание датчика почвы используя пин питания и пин чтения
int new_data_sensor(int sensorwrite, int sensorread){
  dw(8, 1);
  delay(10);
    
  int sensor_value = ar(sensorread);
  dw(sensorwrite, 0);
  return map(sensor_value, rate, 1023, 100, 0);
}
