#include "SPI.h"
#include "MFRC522.h"

// пины для Ардуино
#define RST_PIN  9
#define SS_PIN  10

// инициализируем обьект для RFID метки
MFRC522 rfid(SS_PIN, RST_PIN);


void setup() {
    Serial.begin(9600);
    SPI.begin();
    rifd.PCD_Init();
    rfid.PCD_DumpVersionToSerial();
    Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}


void loop() {
    // если не найдена новая метка
    if ( ! rfid.PICC_IsNewCardPresent()) {
        return;
    }

    // если не были получены данные о карте
    if ( ! rfid.PICC_ReadCardSerial()) {
        return;
    }

    // вывод информации о карте на монитор порта
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}

