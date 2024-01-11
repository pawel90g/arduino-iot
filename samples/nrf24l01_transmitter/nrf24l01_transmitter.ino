#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SOFT_SPI_MISO_PIN 12
#define SOFT_SPI_MOSI_PIN 11
#define SOFT_SPI_SCK_PIN 13

#define CE_PIN 7
#define CS_PIN 8

#define LED_PIN 2

RF24 radio(CE_PIN, CS_PIN);

const byte address[6] = "00001";
bool ledOn = false;

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  char command[1] = "";
  command[0] = ledOn ? '0' : '1';

  radio.write(&command, sizeof(command));
  ledOn = !ledOn;
  digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
  delay(1000);
}
