#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include "Bridge.h"
#include "HttpClient.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

//ThingSpeak Settings 
String thingSpeakAPI = "api.thingspeak.com";
String talkBackAPIKey = "R2EIQA5ZNL2BMMRN";
String talkBackID = "YYYY";
const int checkTalkBackInterval = 15 * 1000;    // Time interval in milliseconds to check TalkBack (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0;

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  lcd.createChar(0, smiley);
  lcd.begin(16, 2);               // start the library
  lcd.setCursor(0,0);             // set the LCD cursor   position
  lcd.print("Teplota");  // print a simple message on the LCD

  // Start up the library
  sensors.begin();
  
  // Initialize Bridge
  Bridge.begin();
  
  // Initialize Serial
//  Serial.begin(9600);
//  while(!Serial);
}

void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
//  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
//  Serial.println("DONE");
  delay(1000);
//  Serial.print("Temperature for the device 1 (index 0) is: ");
  float teplota = sensors.getTempCByIndex(0);
//  Serial.println(teplota);  

  lcd.setCursor(0,1);
  lcd.print(teplota);  
  lcd.print(" ");
  lcd.write(byte(0));  
//  lcd.noDisplay();
 checkTalkBack(teplota);
//  delay(checkTalkBackInterval);
}

void checkTalkBack(float temp)
{
  lcd.setCursor(10,1);
  lcd.print("       ")'  
  HttpClient client;
  
  String talkBackCommand;
  char charIn;
  String talkBackURL =  "http://" + thingSpeakAPI + "/update?api_key=" + talkBackAPIKey + "&field1="+temp;
  
  // Make a HTTP GET request to the TalkBack API:
  int result = client.get(talkBackURL);
    
  while (client.available()) {
    charIn = client.read();
    talkBackCommand += charIn;
  }
  lcd.setCursor(10,1);
  lcd.print("D:"+talkBackCommand);  
  Serial.flush(); 
  delay(1000);
}
