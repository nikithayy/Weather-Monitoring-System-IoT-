#include <LiquidCrystal.h>
#include "DHT.h"

#include "ThingSpeak.h"
#include "secrets.h"
#include <ESP8266WiFi.h>
#define DHTPIN D1   
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = D2, en = D3, d4 = D4, d5 = D5, d6 = D6, d7 = D7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

boolean flag=LOW;
uint32_t delayMS;
// Initialize our values
int number1 ;
int number2 ;
String myStatus = "";
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(3,0); lcd.print("Air Quality");lcd.setCursor(0,1);lcd.print("monitoring systm");
  dht.begin();pinMode(A0,INPUT);
  Serial.begin(9600);WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  delay(5000);
}
unsigned long tim=0,tim1=0;;float h,t;int val;
void loop() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  
if(millis()-tim>5000){
  tim=millis();
flag=!flag;
}

if(flag==LOW){
// READ THE GAS SENSOR
 val = analogRead(A0);
if ((val >350) &&(val<600)){lcdclear();
lcd.setCursor(0,1);lcd.print("AQI: ");lcd.setCursor(5,1);
lcd.print(val);lcd.setCursor(0,0);lcd.print("                    ");
lcd.setCursor(0,0);lcd.print("poor Q. air");
delay(1000);
}
  if (val <350){
    lcdclear();
lcd.setCursor(0,1);lcd.print("AQI:");lcd.setCursor(5,1);
lcd.print(val);lcd.setCursor(0,0);lcd.print("                    ");
lcd.setCursor(0,0);lcd.print("Air Q. is good");delay(1000);
} 
if (val >600){
lcdclear();
lcd.setCursor(0,1);lcd.print("AQI: ");lcd.setCursor(5,1);lcd.print("       ");lcd.setCursor(5,1);

lcd.setCursor(0,0);lcd.print("Dangerous Air");delay(1000);
} 
}

if(flag==HIGH){  
h = dht.readHumidity();
//  // Read temperature as Celsius (the default)
t = dht.readTemperature();
if (isnan(h) || isnan(t)) {
  lcdclear();
  lcd.setCursor(0,0);lcd.print("DHT 11failed");
  delay(1000);
}
else{lcdclear();
lcd.setCursor(0,0);lcd.print("hum=");lcd.setCursor(5,0);
lcd.print(h);lcd.setCursor(10,0);lcd.print("%");
lcd.setCursor(0,1);lcd.print("temp=");lcd.setCursor(5,1);
lcd.print(t);lcd.setCursor(10,1);lcd.print("C");
delay(1000);
}
}
if(millis()-tim1>20000){
  ThingSpeak.setField(1, h);
  ThingSpeak.setField(2, t);
  ThingSpeak.setField(3, val);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  tim1=millis();
}
}
void lcdclear(){
  lcd.setCursor(0,0);lcd.print("                ");
  lcd.setCursor(0,1);lcd.print("                ");
}
/////////////////////***************************************
