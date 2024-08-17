
 
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Place Card On Reader");
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
  
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1) == "62 54 6D 51" || content.substring(1) == "67 1B 03 68") //change here the UID of the card/cards that you want to give access
  {

    Serial.println("Authorized access");
    Serial.println();
    lcd.setCursor(1, 0);
    lcd.print("Authorized access");
    
    lcd.setCursor(1, 2);
    lcd.print("Welcome Jamayne ");
    delay(2000);
    lcd.clear();
  }
 
 else   {
    Serial.println(" Access denied");
    lcd.setCursor(1, 0);
    lcd.print("Access Denied");
    delay(2000);
    lcd.clear();
  }
} 