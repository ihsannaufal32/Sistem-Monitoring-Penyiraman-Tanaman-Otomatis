#include "DHTStable.h"
#include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x27,16,2);
DHTStable DHT;

#define DHT11_PIN 13
int kelembaban = A2;
int sensorValue = 0; 
const int Relaypin = 11;
//motor
// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

//LDR
unsigned int AnalogValue;


void setup()
{
  Serial.begin(9600);
  Serial.println(_FILE_);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTSTABLE_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C), \tSoil");
  lcd.init();
  lcd.backlight();
  pinMode(kelembaban, INPUT);
  pinMode(Relaypin, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void loop()
{
  analogWrite(enA, 120);
  analogWrite(enB, 120);


  
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  int pp = (DHT.getTemperature(),1);
  AnalogValue = analogRead(A1);
  switch (chk)
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
    default: 
      Serial.print("Unknown error,\t"); 
      break;
   delay(2000);
  
  }
  sensorValue = analogRead(kelembaban);
  if (AnalogValue < 900){
    digitalWrite(Relaypin, LOW);
    }
  if (AnalogValue > 900){
    digitalWrite(Relaypin, HIGH);
    };
  if(sensorValue > 700){    
        digitalWrite(in3, HIGH); // PUMP SEBELAH KANAN
        digitalWrite(in4, LOW);
    };
  if(sensorValue < 700){    
        digitalWrite(in3, LOW); // PUMP SEBELAH KANAN
        digitalWrite(in4, LOW);
    };    
  if((DHT.getTemperature()) > 38.00){
        digitalWrite(in1, HIGH); //FAN SEBELAH KIRI
        digitalWrite(in2, LOW);
    }  
  if((DHT.getTemperature()) < 38.00){
        digitalWrite(in1, LOW); //FAN SEBELAH KIRI
      digitalWrite(in2, LOW);
    }  

// digitalWrite(in1, HIGH); //FAN SEBELAH KIRI
 // digitalWrite(in2, LOW);
  // DISPLAY DATA
  lcd.setCursor(0, 0);
  Serial.print(DHT.getHumidity(), 1);
  lcd.print("Hum:");
  lcd.print(DHT.getHumidity(), 1);
  Serial.print(",\t");
  lcd.setCursor(0, 1);
  Serial.println(DHT.getTemperature(), 1);
  lcd.print("Temp:");
  lcd.println(DHT.getTemperature(), 1);
  lcd.print("(C)");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Meka Kel 4B");
  lcd.setCursor(0, 1);
  Serial.println(sensorValue);
  lcd.print("Moist:");
  lcd.print(sensorValue);
  delay(3000);
  lcd.clear();
  Serial.println(AnalogValue);
  lcd.setCursor(0, 0);
  lcd.print("Cahaya");
  lcd.setCursor(0, 1);
  lcd.print(AnalogValue);
  delay(3000);
  lcd.clear();
  }