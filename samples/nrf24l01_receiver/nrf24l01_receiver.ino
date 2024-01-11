#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define SOFT_SPI_MISO_PIN 12
#define SOFT_SPI_MOSI_PIN 11
#define SOFT_SPI_SCK_PIN 13

#define CE_PIN 7
#define CS_PIN 8

#define LED_PIN 2
#define RADIO_AVAILABLE_PIN 3

RF24 radio(CE_PIN, CS_PIN);


const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RADIO_AVAILABLE_PIN, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if(radio.available()) {
    digitalWrite(RADIO_AVAILABLE_PIN, HIGH);
    char command[32] = "";
    radio.read(&command, sizeof(command));
    int state = atoi(command);
    digitalWrite(LED_PIN, state);
  } else {
    digitalWrite(RADIO_AVAILABLE_PIN, LOW);
  }
  delay(1000);
}
