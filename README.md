Arduino YUN with temp sensor and LCD pushing local temperature to cloud. Great for swimming pool temperature checks.

HW used:
- Arduino YUN - an arduino computer with Wifi - http://arduino.cc/en/Main/ArduinoBoardYun?from=Products.ArduinoYUN
- LCD panel with keys - http://www.dfrobot.com/wiki/index.php?title=Arduino_LCD_KeyPad_Shield_%28SKU:_DFR0009%29
- Connetors board between Arduino and LCD panel - https://www.sparkfun.com/products/7914
- Digital temperature sensor Maxim DS18B20 - http://www.hobbytronics.co.uk/ds18b20-arduino

SW Used:
- OneWire and Dallas temperature libraries to connect to temperature sensor http://www.milesburton.com/?title=Dallas_Temperature_Control_Library
- LiquidCrystal library for displaying temperature to LCD panel http://arduino.cc/en/Reference/LiquidCrystal?from=Tutorial.LCDLibrary
- Arduino bridge library and HttpClient to send data to cloud http://arduino.cc/en/Reference/YunBridgeLibrary
- ThinkSpeak cloud to predent temperature https://thingspeak.com/

ThinkSpeak temperature results https://thingspeak.com/channels/12699

Final prototype images:
(/images/IMG_20141122_150217.jpg)
(/images/IMG_20141122_150231.jpg)
(/images/IMG_20141122_150239.jpg)
(/images/IMG_20141122_150247.jpg)
