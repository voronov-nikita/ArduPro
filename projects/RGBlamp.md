# RGB лампа (бра) собственного производства

> [!NOTE]
> Иногда твоих знаний недостаточно, чтобы просто решить проблему.
>
> А бывает такое, что твои знания только создают проблемы.

<br>

## Содержание

1. [Введение](./RGBlamp.md#введение)
2. [Схема и используемые датчики](./RGBlamp.md#схема-и-используемые-датчики)
3. [Прошивка](./RGBlamp.md#прошивка)
4. [Полезные ссылки](./RGBlamp.md#полезные-ссылки)

---

<br>


## Введение

<br>


## Схема и используемые датчики

<br>

## Прошивка

### Версия №1

```ino

```

### Версия №2

```ino

```

### Версия №3

```ino

```

<br>

## **Готовая реализация**

```ino

#include <IRremote.hpp>           // Подключаем библиотеку IRremote
#include <Adafruit_NeoPixel.h>    // Подключаем библиотеку для светодиодной ленты

#define IR_RECEIVE_PIN D1         // Сигнальный вывод ИК-приемника
#define LED_STRIP_PIN D5          // Пин подключения светодиодной ленты
#define NUM_LEDS 36               // Количество светодиодов в ленте

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_STRIP_PIN, NEO_GRB + NEO_KHZ800);

uint8_t brightness = 128;         // Текущая яркость (по умолчанию 50%)
uint8_t brightnessStep = 25;      // Шаг изменения яркости
uint32_t pink = strip.Color(255, 20, 147); // Розовый цвет
uint32_t blue = strip.Color(0, 0, 255);   // Синий цвет
uint32_t white = strip.Color(255, 255, 255); // Белый цвет
uint32_t black = strip.Color(0, 0, 0);

bool isEnabled = false;           // Лента включена/выключена
bool isAnimating = false;         // Выполняется ли анимация
bool isPulsating = false;         // Выполняется ли пульсация
long animationTimer = 0;          // Таймер для анимаций
int animationStep = 0;            // Шаг текущей анимации
int pulsateDirection = 1;         // Направление изменения яркости (-1 уменьшение, 1 увеличение)

void setup() {
  Serial.begin(9600); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Инициализация ИК-приемника
  strip.begin();         // Инициализация ленты
  strip.show();          // Гасим все светодиоды
}

void loop() {
  // Проверяем наличие новых команд с ИК-пульта
  if (IrReceiver.decode()) {
    uint32_t command = IrReceiver.decodedIRData.decodedRawData; // Получаем код команды
    Serial.println(command, HEX);  // Выводим код в Serial Monitor
    handleCommand(command);        // Обрабатываем полученную команду
    IrReceiver.resume();           // Включаем прием следующего значения
  }

  // Обновляем состояние анимации, если она запущена
  if (isAnimating) {
    updateAnimation();
  }

  // Обновляем состояние пульсации, если она запущена
  if (isPulsating) {
    updatePulsation();
  }
}

// Обработка команды с ИК-пульта
void handleCommand(uint32_t command) {
  isAnimating = false;  // Останавливаем текущую анимацию при новой команде
  isPulsating = false;  // Останавливаем пульсацию при новой команде

  switch (command) {
    case 0xB946FF00: // Включить/выключить ленту
      isEnabled = !isEnabled;
      setStripColor(white);
      break;
    case 0xE31CFF00: // Яркость 20%
      setBrightness(51); // 20% от 255
      break;
    case 0xAC53FF00: // Яркость 50%
      setBrightness(128); // 50% от 255
      break;
    case 0xAD52FF00: // Яркость 100%
      setBrightness(255); // 100% от 255
      break;
    case 0xF30CFF00: // Розовый (пурпурный)
      setStripColor(pink);
      break;
    case 0xA15EFF00: // Синий
      setStripColor(blue);
      break;
    case 0xE718FF00: // Белый
      setStripColor(white);
      break;
    case 0xBA45FF00: // Радужное переливание
      if (isEnabled) startRainbowCycle();
      break;
    case 0xE619FF00: // Уменьшить яркость
      decreaseBrightness();
      break;
    case 0xBF40FF00: // Увеличить яркость
      increaseBrightness();
      break;
    case 0xB847FF00: // Пульсация
      if (isEnabled) startPulsation();
      break;
    default:
      Serial.println("Неизвестная команда");
      break;
  }
}

// Увеличение яркости
void increaseBrightness() {
  if (brightness + brightnessStep <= 255) {
    setBrightness(brightness + brightnessStep);
  } else {
    setBrightness(255); // Ограничиваем максимальной яркостью
  }
}

// Уменьшение яркости
void decreaseBrightness() {
  if (brightness >= brightnessStep) {
    setBrightness(brightness - brightnessStep);
  } else {
    setBrightness(0); // Ограничиваем минимальной яркостью
  }
}

// Установка яркости
void setBrightness(uint8_t newBrightness) {
  brightness = newBrightness;
  strip.setBrightness(brightness);
  strip.show();
}

// Установка цвета ленты
void setStripColor(uint32_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (isEnabled) {
      strip.setPixelColor(i, color);
    } else {
      strip.setPixelColor(i, black);
    }
  }
  strip.show();
}

// Начало радужной анимации
void startRainbowCycle() {
  isAnimating = true;       // Запускаем анимацию
  animationTimer = millis(); // Инициализируем таймер
  animationStep = 0;        // Сбрасываем шаг
}

// Обновление состояния радужной анимации
void updateAnimation() {
  if (millis() - animationTimer > 10) { // Обновляем анимацию каждые 10 мс
    animationTimer = millis();         // Сбрасываем таймер

    long firstPixelHue = animationStep * 256; // Позиция градиента
    for (int i = 0; i < strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();

    animationStep++; // Увеличиваем шаг
    if (animationStep >= 5 * 256) { // Завершаем анимацию после полного цикла
      animationStep = 0;
    }
  }
}

// Начало эффекта пульсации
void startPulsation() {
  isPulsating = true;       // Запускаем пульсацию
  animationTimer = millis(); // Инициализируем таймер
  pulsateDirection = 1;      // Устанавливаем направление (увеличение яркости)
}

// Обновление состояния пульсации
void updatePulsation() {
  if (millis() - animationTimer > 20) { // Обновляем каждые 20 мс
    animationTimer = millis();         // Сбрасываем таймер

    // Изменяем яркость
    brightness += pulsateDirection * 5; // Меняем яркость на 5
    if (brightness >= 255) {            // Достигли максимума
      brightness = 255;
      pulsateDirection = -1;            // Меняем направление на уменьшение
    } else if (brightness <= 0) {       // Достигли минимума
      brightness = 0;
      pulsateDirection = 1;             // Меняем направление на увеличение
    }

    strip.setBrightness(brightness);
    strip.show();
  }
}


```

## **Полезные ссылки**

<br><br>
<br><br>

###### 10.12.2024