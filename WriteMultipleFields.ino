/*
  WriteMultipleFields

  Description: Writes values to fields 1,2,3,4 and status in a single ThingSpeak update every 20 seconds.

  Hardware: ESP32 based boards

  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!

  Note:
  - Requires installation of EPS32 core. See https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md for details.
  - Select the target hardware from the Tools->Board menu
  - This example is written for a network using WPA encryption. For WEP or WPA, change the WiFi.begin() call accordingly.

  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.

  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.

  For licensing information, see the accompanying license file.

  Copyright 2020, The MathWorks, Inc.
*/

#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
sensors_event_t event;

#define DHTPIN 15     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
char ssid[] = "Galaxy A711C04";
char pass[] = "12345678910";
//int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 1957077;
const char * myWriteAPIKey = "Y1Y07ATY6R13X2HX";

// Initialize our values
//int number1 = 0;
//int number2 = random(0, 100);
//int number3 = random(0, 100);
//int number4 = random(0, 100);
//String myStatus = "";
void dht11() {
  delay(delayMS);
  // Get temperature event and print its value.
  dht.temperature().getEvent(&event);
  // if (isnan(event.temperature)) {
  //   Serial.println(F("Error reading temperature!"));
  //}
  //else {
  //    Serial.print(F("Temperature: "));
  //    Serial.print(event.temperature);
  //    Serial.println(F("°C"));
  // }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  // if (isnan(event.relative_humidity)) {
  //   Serial.println(F("Error reading humidity!"));
  // }
  // else {
  //    Serial.print(F("Humidity: "));
  //    Serial.print(event.relative_humidity);
  //    Serial.println(F("%"));
  // }
}

  void loop() {

    // Connect or reconnect to WiFi


    // set the fields with the values
    ThingSpeak.setField(1, event.temperature);
    ThingSpeak.setField(2, event.relative_humidity);
    //  ThingSpeak.setField(3, number3);
    //  ThingSpeak.setField(4, number4);

    // figure out the status message
    //  if (number1 > number2) {
    //    myStatus = String("field1 is greater than field2");
    //  }
    //  else if (number1 < number2) {
    //    myStatus = String("field1 is less than field2");
    //  }
    //  else {
    //    myStatus = String("field1 equals field2");
    //  }

    // set the status
//    ThingSpeak.setStatus(myStatus);

    // write to the ThingSpeak channel
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    // if (x == 200) {
    //  Serial.println("Channel update successful.");
    // }
    // else {
    //  Serial.println("Problem updating channel. HTTP error code " + String(x));
    // }

    // change the values
    //  number1++;
    //  if (number1 > 99) {
    //    number1 = 0;
    //  }
    //  number2 = random(0, 100);
    //  number3 = random(0, 100);
    //  number4 = random(0, 100);
    delay(20000); // Wait 20 seconds to update the channel again
  }

void setup() {
//  Serial.begin(115200);  //Initialize serial
  //while (!Serial) {
  ; // wait for serial port to connect. Needed for Leonardo native USB port only
  //}

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
 // if (WiFi.status() != WL_CONNECTED) {
 //   Serial.print("Attempting to connect to SSID: ");
 //   Serial.println(SECRET_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
    //  Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
