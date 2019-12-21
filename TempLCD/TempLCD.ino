#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include "Bridge.h"
#include "HttpClient.h"
#include <Process.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//ThingSpeak Settings 
String thingSpeakAPI = "api.thingspeak.com";
String talkBackAPIKey = "R2EIQA5ZNL2BMMRN";
String talkBackID = "YYYY";
const int checkTalkBackInterval = 3 * 1000;    // Time interval in milliseconds to check TalkBack (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0;

void setup(void)
{ 
  lcd.begin(16, 2);               // start the library
  lcd.setCursor(0,0);             // set the LCD cursor   position
  lcd.print("Init ...");  // print a simple message on the LCD
  
  // Start up the library
  sensors.begin();
  
  // Initialize Bridge
  Bridge.begin();
  
  // Initialize Serial
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();  // make contact with the linux processor
  digitalWrite(13, HIGH);  // Led on pin 13 turns on when the bridge is ready
  delay(2000);  // wait 2 seconds
  lcd.setCursor(0,0);             // set the LCD cursor   position
  lcd.print("Temp ...");
}

void loop(void)
{ 
  float temp = getTemp();

  lcd.setCursor(5,0);
  lcd.print("    ");
  lcd.setCursor(5,0);
  lcd.print(temp);  

  lcd.setCursor(0,1);
  lcd.print("Wifi...");
  String wifi = checkWifi();
  lcd.setCursor(0,1);
  lcd.print(wifi);

  lcd.setCursor(12,1);
  lcd.print("->...");
  post(temp);
  lcd.setCursor(12,1);
  lcd.print("->Ok");
  delay(checkTalkBackInterval); 
  delay(3600000);  // wait 1 hour
} 

float getTemp() 
{
// call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  // Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  delay(1000);
  Serial.print("Temperature for the device 1 (index 0) is: ");
  float temp = sensors.getTempCByIndex(0);
  Serial.println(temp);  
  return temp;
}

String checkWifi() 
{
  Process wifiCheck;  // initialize a new process
  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua | grep Signal");  // command you want to run

  String label = "";
  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    SerialUSB.print(c);
    label += c;
  }
  label.trim();
  Serial.println(label);
  return label;

}
void post(float temp)
{
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
}
