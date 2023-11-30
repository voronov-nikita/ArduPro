
#define PIN_TRIG 12
#define PIN_ECHO 11

void setup(){
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

// функция высчитывавает показание для датчика Расстояния
// не забываем ставить delay()
float dist(){
    digitalWrite(PIN_TRIG, 0);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG, 1);

    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, 0);
    duration = pulseIn(PIN_ECHO, 1);

    return (duration / 2) / 29.1;

}