#include <MFRC522.h> 
#include<Servo.h> 
#include<SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
 
int ServoPIN=8;   
int RST_PIN=9;  
int SS_PIN=10;

LiquidCrystal_I2C lcd(0x27,16,2);
Servo servoMotor;  
MFRC522 kartOkuyucu(SS_PIN,RST_PIN);  

void setup() {
  servoMotor.attach(ServoPIN); 
  Serial.begin(9600); 
  SPI.begin(); 
  kartOkuyucu.PCD_Init(); 
       
}

void loop() {
      lcd.init();                       
      lcd.init();
      lcd.setCursor(0,0);
      lcd.backlight();
      lcd.print("Kart Okutun");
      delay(2000);
      lcd.clear();
      
   if(!kartOkuyucu.PICC_IsNewCardPresent())
    return;
    
  if(!kartOkuyucu.PICC_ReadCardSerial()) //Kart okunmadığı zaman bekliyoruz.
    return;
      kartIdGoster();
  if(Serial.available())
  {
    char oku = Serial.read();
    if (oku =='1')
    {
      lcd.setCursor(0,0);
      lcd.print("Hoşgeldiniz...");
      delay(2000);
      lcd.clear();
       
      servoMotor.write(180); 
      delay(1000); 
      servoMotor.write(0); 
  
    }
    else if (oku =='0')
    {        
      lcd.setCursor(0,0);
      lcd.print("Hatalı Kart");
       delay(2000);
      lcd.clear(); 
    }
  }
  kartOkuyucu.PICC_HaltA();
}
void kartIdGoster() {

  for (int sayac = 0; sayac < 4; sayac++) {
    Serial.print(kartOkuyucu.uid.uidByte[sayac]);
    Serial.print("");
  
  }
   delay(1000);
}
