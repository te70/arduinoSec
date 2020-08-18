#include <SPI.h>
#include <SD.h>
#include <TroykaDHT.h>

DHT dht(4, DHT22);
//cs sd card port
const int chipSelect = 53;
//soil moisture values
const int AirValue = 520;
const int WaterValue = 260;
int intervals = (AirValue-WaterValue)/3;
int soilMoistureValue = 0;

File myFile;

void setup() {
  // initilizing the DHT sensor
  dht.begin();

  Serial.begin(9600);

  //setup for SD card
  Serial.print("initializing SD card...");
  if(!SD.begin(chipSelect)){
    Serial.print("Initialization Failed");
    return;
  }
  Serial.println("Initialization done");

  //open file
  myFile=SD.open("DATA.txt, FILE_WRITE");

  //if file opened write to it:
  if(myFile){
    Serial.println("File opened ok");
    //print data headings
    myFile.println("Date,Time,TemperatureC");
  }
  myFile.close();
}

void loggingTemperature(){
  dht.read();
  float t = dht.getTemperatureC();
  float u = dht.getHumidity();
  float v = analogRead(A10);
  float w = analogRead(A8);

  if(isnan(t)){
    Serial.println("Failed to read from DHT sensor");
    return;
    }

    Serial.print("Temperature:");
    Serial.print(t);
    Serial.println("*C");
     Serial.print("Humidity:");
     Serial.println(u);
    
     Serial.print("Soil moisture:");
     Serial.println(v);
     Serial.print("Soil Moisture:");
     Serial.println(w);
     Serial.println("\n");
     

    myFile = SD.open("DATA.txt", FILE_WRITE);
    if(myFile){
      Serial.println("open wih succcess");
      myFile.print(t);   
      myFile.println(",");
      myFile.println(u);
      myFile.println(",");
      myFile.println(v);
      myFile.println(",");
      }
      myFile.close();
  }

  //void loggingMoisture(){
   
   //soilMoistureValue = analogRead(A10);  //put Sensor insert into soil
    //if(soilMoistureValue > WaterValue && soilMoistureValue < (WaterValue + intervals))
//{
  //Serial.println("Very Wet");
  
//}
//else if(soilMoistureValue > (WaterValue + intervals) && soilMoistureValue < (AirValue - intervals))
//{
  // Serial.println("Wet");
//}
//else if(soilMoistureValue < AirValue && soilMoistureValue > (AirValue - intervals))
//{
  // Serial.println("Dry");
//}
 //myFile = SD.open("DATA.TXT", FILE_WRITE);
 //if(myFile){
  //Serial.println("continuation....");
  //Serial.println(soilMoistureValue);
  //myFile.println(soilMoistureValue);
  //myFile.println(",");
  //}
 
    //myFile.close();
    //}
void loop() {
  // put your main code here, to run repeatedly:
  //loggingMoisture();
  loggingTemperature();
  delay(300000);
}
