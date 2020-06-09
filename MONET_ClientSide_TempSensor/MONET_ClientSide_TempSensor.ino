#include <SPI.h>
#include <RH_RF95.h>
#include "dht.h"
#define dht_apin A0 


RH_RF95 rf95;


//static void smartdelay(unsigned long ms);

int LED=A0;

char DeviceID[10]="a8727"; //DeviceID or Device identifier in GPSWOX.com
dht DHT;
 double aaa ;
  double bbb ;
   double ccc ;
   char temp[20];
   char humidity[20];
   char tem[20];
String datastring1="";
String datastring2="";
String datastring3="";
uint8_t datasend[50];    //Storage  longtitude,latitude and altitude


void setup()
{
  // initialize digital pin  as an output.
  pinMode(LED, OUTPUT);
  
  // initialize both serial ports:
  Serial.begin(9600);  // Serial to print out GPS info in Arduino IDE
  delay(2000);
  while (!Serial);

  
 if (!rf95.init()) {  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  
  /* Set frequency is 868MHz,SF is 7,SB is 125KHz,CR is 4/5 and Tx power is 20dBm */
  rf95.setFrequency(868);
  rf95.setSpreadingFactor(7);
  rf95.setSignalBandwidth(125E3);
  rf95.setCodingRate4(5);
  rf95.setTxPower(20,false);
  
  Serial.println("Ready to send!");
}

void loop()
{
   DHT.read11(dht_apin);
    
   // Serial.print("Current humidity = ");
  //  Serial.print(DHT.humidity);
    aaa= DHT.humidity;
  //  Serial.print("%  ");
  //  Serial.print("temperature = ");
  //  Serial.print(DHT.temperature); 
    bbb= DHT.temperature;
   // Serial.println("C  ");
  //  Serial.println("C cccccc ");
  //  Serial.println(aaa);
    ccc=0.00;
  
  datastring1 +=dtostrf(bbb, 0, 6, temp); 
  datastring2 +=dtostrf(aaa, 0, 6, humidity);
  datastring3 +=dtostrf(ccc, 0, 2, tem);
 
  strcat(temp,",");
  strcat(temp,humidity); 
  strcat(temp,","); 
  strcat(temp,tem);
  strcat(temp,","); 
  strcat(temp,DeviceID);
  strcat(temp,",");
  strcpy((char *)datasend,temp);//the format of datasend is temp,humidity,raw,DeviceID,
  Serial.println((char *)datasend);
  delay(5000);
  
   // send data
  rf95.send(datasend, sizeof(datasend));  
  rf95.waitPacketSent();

  delay(30000);
  }
//  smartdelay(1000);


//If the packet arrive LG01, LG01 will send a ACK and here will receive it and turn on the led.  
