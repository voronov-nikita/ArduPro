#include "Servo.h"

// инициализируем объект сервомашинки
Servo ser;


void setup(){
    // пример того, как можно назначить пин для сервомашинки
    ser.attach(8);
}

void loop(){
    // считываем данные с сервомашинки. 
    // Получаем число, приблизительно равное углу поворота привода.
    int angle = ser.read();

    if (angle==0){
        // переводим сервопривод в положение 180 градусов
        ser.write(180);
        // ставим delay, чтобы компенсировать время поворота.
        delay(400);
    } else if (angle == 180){
        ser.write(0);
    }

}