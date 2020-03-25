#include <SoftwareSerial.h>     //biblioteka do obslugi SerialMonitora
#include <OneWire.h>            //biblioteka do obdlugi OneWire
#include <DallasTemperature.h>  //bibilioteka dallas DS18B20
#include "LowPower.h"           //dodaj biliotekę obsługującą oszczędzenie energii
 

#define ONE_WIRE_BUS 2 // dane DS18B20 podpiete do pinu 2


OneWire oneWire(ONE_WIRE_BUS);
SoftwareSerial gprsSerial(7, 8);  //modem podlaczony do portów 7, 8 w arduino UNO.

DallasTemperature sensors(&oneWire); // Ustawienie komunikacji OneWire z DallasTemperature. 

float temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8; //zmienne temperatury z poszczegolnego czujnika.

//ustawienie adresów czujników do stałych.
byte Thermo1[8] = {0x28, 0xFF, 0x49, 0xE1, 0x6D, 0x18, 0x01, 0xE5};
byte Thermo2[8] = {0x28, 0xFF, 0x18, 0xE1, 0x6D, 0x18, 0x01, 0xBD};
byte Thermo3[8] = {0x28, 0xFF, 0x5B, 0xBD, 0x68, 0x18, 0x03, 0x59};
byte Thermo4[8] = {0x28, 0xFF, 0x77, 0xBE, 0x68, 0x18, 0x03, 0x08};
byte Thermo5[8] = {0x28, 0xFF, 0x4D, 0xF2, 0x68, 0x18, 0x03, 0xC3};
byte Thermo6[8] = {0x28, 0xFF, 0xE2, 0xC0, 0x68, 0x18, 0x03, 0xD0};
byte Thermo7[8] = {0x28, 0xFF, 0x9E, 0xDB, 0x68, 0x18, 0x03, 0x30};
byte Thermo8[8] = {0x28, 0xFF, 0x55, 0xBC, 0x68, 0x18, 0x03, 0x74};

void setup()
{
  sensors.begin(); // Uruchomienie odczytu czujników DS18B20
  
  //ustawienie rozdzielczności poszczególnego czujnika. 
  sensors.setResolution(Thermo1, 12); 
  sensors.setResolution(Thermo2, 12); 
  sensors.setResolution(Thermo3, 12);
  sensors.setResolution(Thermo4, 12);
  sensors.setResolution(Thermo5, 12);
  sensors.setResolution(Thermo6, 12);
  sensors.setResolution(Thermo7, 12);
  sensors.setResolution(Thermo8, 12);

  
  gprsSerial.begin(19200);
  Serial.begin(19200);
  Serial.println("Configuracja SIM900...");
  delay(20000);
  Serial.println("Zrobione!...");
  gprsSerial.flush();
  Serial.flush();

  // sprawdzenie podłączenia do sieci GPRS 
  gprsSerial.println("AT+CGATT?");
  delay(100);
  toSerial();


  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  gprsSerial.println(Serial.availableForWrite());
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(2000);
  gprsSerial.println(Serial.availableForWrite());
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
 
}


void loop()
{
    gprsSerial.begin(19200);
  Serial.begin(19200);
  Serial.println("Config SIM900...");
  delay(20000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

  // attach or detach from GPRS service 
  gprsSerial.println("AT+CGATT?");
  delay(100);
  toSerial();


  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  gprsSerial.println(Serial.availableForWrite());
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(2000);
  gprsSerial.println(Serial.availableForWrite());
  toSerial();

  //ustawianie sleep mode dla modemu, jeśli przez 5 sekund nie wykonywae jest zadne polecenie AT, to modem wchodzi automatycznie uspienie.
  
  gprsSerial.println("AT+CSCLK=2");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
  //koniec
  sensors.requestTemperatures();
  
  temp1 = (sensors.getTempC(Thermo1));  
  temp2 = (sensors.getTempC(Thermo2));
  temp3 = (sensors.getTempC(Thermo3));
  temp4 = (sensors.getTempC(Thermo4));
  temp5 = (sensors.getTempC(Thermo5));
  temp6 = (sensors.getTempC(Thermo6));
  temp7 = (sensors.getTempC(Thermo7));
  temp8 = (sensors.getTempC(Thermo8));
  
  String stringvar1 = String(temp1);
  String stringvar2 = String(temp2);
  String stringvar3 = String(temp3);
  String stringvar4 = String(temp4);
  String stringvar5 = String(temp5);
  String stringvar6 = String(temp6);
  String stringvar7 = String(temp7);
  String stringvar8 = String(temp8);
  
  String stringurl1 = String("AT+HTTPPARA=\"URL\",\"http://vps748546.ovh.net/1.php?data1="); //adres url
  String stringdata2 = String("&data2=");
  String stringdata3 = String("&data3=");
  String stringdata4 = String("&data4=");
  String stringdata5 = String("&data5=");
  String stringdata6 = String("&data6=");
  String stringdata7 = String("&data7=");
  String stringdata8 = String("&data8=");

  
  
  String stringurlend = String("\"");
  String urlfinal = String(String(stringurl1) + String(stringvar1) + String(stringdata2) + String(stringvar2) + String(stringdata3) + String(stringvar3) + String(stringdata4) + String(stringvar4) + String(stringdata5) + String(stringvar5) + String(stringdata6) + String(stringvar6) + String(stringdata7) + String(stringvar7) + String(stringdata8) + String(stringvar8) + String(stringurlend));
  delay(2000);
   // initialize http service
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   // set http param value
   gprsSerial.println(urlfinal); 
   delay(2000);
   toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(6000);
   toSerial();

   // read server response
   gprsSerial.println("AT+HTTPREAD"); 
   delay(1000);
   toSerial();

   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   toSerial();
   delay(300);

   gprsSerial.println("");
   
   uspij();
}

void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}

void uspij()
{
  
    for(int i =0; i<=70;i++)                                  // wykonaj pętle for 70 razy 75 x 8 sekund = 600 sekund
    
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);          //przełącz mikrokontroler w tryb Power-down na 8 sekund,
                                                             //wyłączając ADC i BoD
                                                             
    Serial.println("Wstalem po 600 sekundach");               //wyślij informację na UART o zmianie trybu pracy mikrokontrolera
    
}
