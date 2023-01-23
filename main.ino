#include <TM1637.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>


#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define BUTTON_PIN 7
#define SS_PIN 53
#define RST_PIN 5


int tempo = 200;
int buzzer = 11;
int melody[] = {

  
  NOTE_C5,4, //1
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
  NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
  NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
  NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,

  NOTE_F5,2, NOTE_C5,4, //8 
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
  NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,
  NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,
  NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8,
  NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
  NOTE_F5,2, NOTE_C5,4,

  NOTE_F5,4, NOTE_F5,4, NOTE_F5,4,//17
  NOTE_E5,2, NOTE_E5,4,
  NOTE_F5,4, NOTE_E5,4, NOTE_D5,4,
  NOTE_C5,2, NOTE_A5,4,
  NOTE_AS5,4, NOTE_A5,4, NOTE_G5,4,
  NOTE_C6,4, NOTE_C5,4, NOTE_C5,8, NOTE_C5,8,
  NOTE_D5,4, NOTE_G5,4, NOTE_E5,4,
  NOTE_F5,2, NOTE_C5,4, 
  NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,
};


int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;



MFRC522 mfrc522(SS_PIN, RST_PIN);   
LiquidCrystal lcd(7, 6, 8, 4, 3, 2);


String Name;//user name
long Number;//user number
int n ;//The number of card you want to detect (optional)  


void setup() 
{
  pinMode(buzzer, OUTPUT); 
  pinMode(9, OUTPUT);  
  pinMode(10, OUTPUT);  
  Serial.begin(9600);  

   
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.print("Piotr & Yorick");
  lcd.setCursor(0, 0);
  lcd.print("Project by");
  delay(2500);
  lcd.clear();  
  
   
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Put your card to the reader...");
  Serial.println();
}


void loop() 
{
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Put your card to");
  lcd.setCursor(0, 1);
  lcd.print("the reader......");
  delay(300);
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
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

 if (content.substring(1) == "71 D6 EF 1B" || content.substring(1) == "7E FB 38 3B" || content.substring(1) == "74 27 CC A4")
 {   
  digitalWrite(10, HIGH);
  tone(buzzer, 5000);
  delay(100);
  digitalWrite(10, LOW);
  noTone(buzzer); 
  delay(100);
  digitalWrite(10, HIGH);
  tone(buzzer, 5000);
  delay(100);
  noTone(buzzer); 

  
  
  lcd.setCursor(0, 0);
  lcd.print("ID : ");
  lcd.print(content.substring(1));
  lcd.setCursor(0, 1);
  lcd.println("Access granted..");
  delay(1200);
  lcd.clear();  
  lcd.setCursor(0, 0);

if (content.substring(1) == "7E FB 38 3B")
  { 
  Serial.println("Piotr");
  lcd.print("Piotr wurde");
  lcd.setCursor(0, 1);
  lcd.print("angemeldet.");
  digitalWrite(10, LOW);
  noTone(buzzer); 
  }  


if (content.substring(1) == "74 27 CC A4")
  { 
  Serial.println("EASTEREGG");
  lcd.print("EASTEREGGGGGG");
  lcd.setCursor(0, 1);
  lcd.print("DIGGAHHHHHH");
  digitalWrite(10, LOW);
  digitalWrite(9, HIGH);
  delay(200);
  digitalWrite(10, HIGH);
  
  
  noTone(buzzer); 
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }  
  delay(1000);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
}  

if (content.substring(1) == "71 D6 EF 1B")
  { 
  Serial.println("Yorick");
  lcd.print("Yorick wurde");
  lcd.setCursor(0, 1);
  lcd.print("abgemeldet.");
  digitalWrite(10, LOW);
  noTone(buzzer); 
  } 
} 
 
else   
 {
  
 tone(buzzer, 5000);
 digitalWrite(9, HIGH);   //ES WERDE LICHT
 Serial.println("Access denied...");
 lcd.setCursor(0, 0);
 lcd.print("ID : ");
 lcd.print(content.substring(1));
 lcd.setCursor(0, 1);
 lcd.println("Access denied...");
 delay(1500);

 digitalWrite(9, LOW);
 noTone(buzzer); 

 }
}
  
 
