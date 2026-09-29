#include <SPI.h>

const int CS_PIN = 10;

const unsigned long BAUD = 115200;

const uint32_t FLASH_SIZE = 2UL * 1024UL * 1024UL;
uint8_t buf[512]; 

void setup() {
  Serial.begin(BAUD);

  SPI.begin();
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

  digitalWrite(CS_PIN, LOW);

  SPI.transfer(0x03);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  SPI.transfer(0x00);

  for (uint32_t i = 0; i < FLASH_SIZE; i += sizeof(buf)) {
    for (uint16_t j = 0; j < sizeof(buf); j++) {
      buf[j] = SPI.transfer(0x00);
    }
    Serial.write(buf, sizeof(buf));
  }

  digitalWrite(CS_PIN, HIGH);
  SPI.endTransaction();
}

void loop() {}
