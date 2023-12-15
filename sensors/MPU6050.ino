#include "Wire.h"
#include "Kalman.h"

Kalman kalmanX;
Kalman kalmanY;

const uint8_t IMUAddress = 0x68;
const uint8_t targetAngle = 160;
// калибровочные значения гироскопа
const int STARTXANGLE = 180;
const int STARTYANGLE =  -180;

int16_t accX, accY, accZ;
int16_t gyroX, gyroY, gyroZ;
// углы, которые будут вычисляться через акселерометр и гироскоп соответственно
float accXangle, accYangle;
float gyroXangle, gyroYangle;

float compAngleX = 0;
float compAngleY = 0;
float angleX, angleY;
uint32_t timer;

// функция будет формировать углы отклонения 
void getAngles() {
    Wire.beginTransmission(IMUAddress);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(IMUAddress, 14, true);
    accX = Wire.read() << 8 | Wire.read();
    accY = Wire.read() << 8 | Wire.read();
    accZ = Wire.read() << 8 | Wire.read();
    float tempRaw = Wire.read() << 8 | Wire.read();
    gyroX = Wire.read() << 8 | Wire.read();
    gyroY = Wire.read() << 8 | Wire.read();
    gyroZ = Wire.read() << 8 | Wire.read();
}

// функция вычисляет конечный угол по данным от акселерометра и гироскопа. 
// Данные при этом проходят через фильтр и мы получаем итоговые показатели
void calculateAngles() {
    accYangle = (atan2(accX, accZ) + PI) * RAD_TO_DEG;
    accXangle = (atan2(accY, accZ) + PI) * RAD_TO_DEG;
    float gyroXrate = (float)gyroX / 131.0;
    float gyroYrate = -((float)gyroY / 131.0);
    gyroXangle += gyroXrate * ((float)(micros() - timer) / 1000000);
    gyroYangle += gyroYrate * ((float)(micros() - timer) / 1000000);
    angleX = kalmanX.getAngle(accXangle, gyroXrate, (float)(micros() - timer) / 1000000);
    angleY = kalmanY.getAngle(accYangle, gyroYrate, (float)(micros() - timer) / 1000000);
    timer = micros();
}


void setup(){
    // соединение битов данных со сдвиговым регистром гироскопа
    Wire.begin();
    Wire.beginTransmission(IMUAddress);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);

    // задать начало отсчета для фильтра
    kalmanX.setAngle(STARTXANGLE);
    kalmanY.setAngle(STARTYANGLE);
    timer = micros();
}

void loop(){
    getAngles();
    calculateAngles();
}