#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>


SoftwareSerial GSM(13,12);

int count=0;
String c;

#define SS_PIN 53
#define RST_PIN 49
MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  GSM.begin(9600);
  Serial.begin(9600);
  mfrc522.PCD_Init();
  Serial.println("Put your card to reader");
  Serial.println();

  GSM.println("AT+CMGF=1");
  delay(1000);
 
  
}

void loop() {
  while(GSM.available()){
    Serial.write(GSM.read());
    }
  RfidScan();
  if(Serial.available()>0)
  {
    c=Serial.readString();
    sendSMS();
    }

    Serial.print("UID tag:");
    String content="";
    byte letter;
    for (byte i=0; i<mfrc522.uid.size; i++)
    {
      Serial.print(mfrc522.uid.uidByte[i] <0x10 ? " 0":" ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] <0x10 ? " 0":""));
      content.concat(String(mfrc522.uid.uidByte[1], HEX));
    }

    Serial.println();
    Serial.print("Message: ");
    content.toUpperCase();
    Serial.println("Card detected once");
    sendSMS();
if(content.substring(1) == "41 D8 85 20")
    {
      Serial.println("correct");
        Serial.println();
        delay(500);
        sendSMS();
        delay(1000);
        Serial.println("messsage sent");
    }
if(content.substring(1)== "39 5B 54 63")
  {
    Serial.println("correct");
    Serial.println();
    delay(500);
    sendSMS();
    delay(1000);
    Serial.println("message sent");
    
    }
}
void dump_byte_array(byte *buffer, byte bufferSize){
  for(byte i=0;i<bufferSize;i++){
    Serial.print(buffer[i]<0x10?"0":"");
    Serial.print(buffer[i], DEC);
    }

    Serial.println();
    delay(1000);
}
void RfidScan(){
  
  if(! mfrc522.PICC_IsNewCardPresent()){
    return;
    }

   if(! mfrc522.PICC_ReadCardSerial()){
    return;
    }

    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
}
void sendSMS(){
    GSM.println("AT");
    delay(500);
    GSM.println("AT+CMGF=1");
    delay(500);
    GSM.println("AT+CMGS=\"+254713521006\"");
    delay(500);
    GSM.println("BOARDED THE BUS");//sms text to be sent
    delay(500);
    GSM.println((char)26);
    delay(500);
  
  }
