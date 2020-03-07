#include <SPI.h>
#include <MFRC522.h>

#define SDA 10
#define RST 9

MFRC522 rfid(SDA, RST);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  while(!Serial);

  SPI.begin();
  rfid.PCD_Init();
  Serial.println("TAP the RFID tag to the reader.");
  Serial.println();

}

void loop() 
{
  // put your main code here, to run repeatedly:
  if (!rfid.PICC_IsNewCardPresent())
  {
    return;
  }

  // read the card
  if (!rfid.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print("UID Tag: ");
  String ID = "";

  for (byte i = 0; i < rfid.uid.size; i++)
  {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? "0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  ID.toUpperCase();

  if (ID.substring(1) == "92 5F A2 A2")
  {
    Serial.println("Access Granted!");
    Serial.println();
    delay(3000);
  }
  else
  {
    Serial.println("Access Denied!");
    Serial.println();
    delay(3000);
  }
}
