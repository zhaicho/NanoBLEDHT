//雙sensor溫濕度藍牙監視
//DHT library　AUTHOR: Rob Tillaart




#include <dht.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define BTX 3
#define BRX 4

SoftwareSerial BT(BTX, BRX);

dht DHT11;
dht DHT22;  //sensor name

#define DHT11_PIN     5
#define DHT22_PIN     6

float s1t,s1h,s2t,s2h;
int fromphone;

void setup()
{
  pinMode(12,OUTPUT);
  pinMode(DHT11_PIN,OUTPUT);
  pinMode(DHT22_PIN,OUTPUT);
  digitalWrite(12,LOW);  //暫時為另一sensor接地
  Serial.begin(9600); 
  BT.begin(9600);
  Serial.println("蠱惑的溫度 PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);  //DHT庫版本信息
  Serial.println();
  Serial.println("Sensor\t狀態\t濕度(%)\t溫度(C)");
}


void loop()

{
//  if (BT.available()){
//  fromphone=BT.read();
//  Serial.write(fromphone);
//  Serial.println();
//  Serial.println(fromphone);
//  if (fromphone==49){
      BT.println();
      BT.println("Dry Box(DHT11):");
      BT.print(" Temp:");
      BT.print(s1t,1);
      BT.print(" 'C.");
      BT.print(" Hum: ");
      BT.print (s1h,1);
      BT.println("%");
      BT.println("Room(DHT22):");
      BT.print(" Temp:");
      BT.print(s2t,1);
      BT.print(" 'C.");
      BT.print(" Hum: ");
      BT.print(s2h,1);
      BT.println("%");
  //}
//}
  // DHT11部分
  Serial.print("DHT11, \t");
  int chk11 = DHT11.read11(DHT11_PIN);
  switch (chk11)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Error:連接超時\t"); 
    break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Error:連接錯誤\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
    Serial.print("Error:未知錯誤\t"); 
    break;
  }
  // DHT11電腦終端機輸出
  s1h=DHT11.humidity;
  s1t=DHT11.temperature;
  Serial.print(s1h, 1);
  Serial.print("%\t");
  Serial.print(s1t, 1);
  Serial.println("'C.");



  //DHT22部分
  Serial.print("DHT22, \t");
  int chk22 = DHT22.read22(DHT22_PIN);
  switch (chk22)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
    case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
    case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  // DHT22電腦終端機輸出
  s2h=DHT22.humidity+20;
  s2t=DHT22.temperature-4;
  Serial.print(s2h, 1);
  Serial.print("%\t");
  Serial.print(s2t, 1);
  Serial.println("'C.");
  Serial.println();

  delay(5000);
}