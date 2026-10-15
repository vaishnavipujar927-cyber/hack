#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

#define SPI_SCK 12
#define SPI_MISO 13
#define SPI_MOSI 11

MFRC522 rfid(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(115200);

  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SS_PIN);

  rfid.PCD_Init();

  Serial.println("Scan Card");
}

void loop()
{
  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  Serial.print("UID : ");

  for (byte i = 0; i < rfid.uid.size; i++)
  {
    if (rfid.uid.uidByte[i] < 0x10)
      Serial.print("0");

    Serial.print(rfid.uid.uidByte[i], HEX);
  }

  Serial.println();

  rfid.PICC_HaltA();
}