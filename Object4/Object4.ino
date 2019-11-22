// References
/*
JSON Parser: https://arduinojson.org/v6/example/parser/
Random(): https://forum.arduino.cc/index.php?topic=244664.0
Accerometer: https://learn.adafruit.com/lsm303-accelerometer-slash-compass-breakout/coding
*/

#include "Display.h" // Custom Display class

String serialBuffer = ""; //For Serial
#include <SoftwareSerial.h>
// SoftwareSerial BTserial(0, 1); // RX | TX
#include <ArduinoJson.h>

// Acc Libraries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

StaticJsonDocument<200> jsonBuffer;

Display display;

// Global Acc X and Y Variables
float prevX = 0;
float prevY = 0;
bool active = true;

// Songs that user can switch between
int songIndex = 0;
String songs[] = {
    "blink182 - I Miss U",
    "Oasis - Wonderwall",
    "Lil Pump - Gucci Gang"};

void setup()
{
  // Init Serial and display
  Serial.begin(38400);
  // BTserial.begin(38400);
  display.begin();

  // Set display to initial song (first song)
  display.setSong(songs[songIndex]);

  // Initialise the acc sensor
  if (!accel.begin())
  {
    Serial.println("Acc Error");
    while (1)
      ;
  }
}

void loop()
{
  display.update();

  while (Serial.available())
  {                                     // if data available at serial port
    serialBuffer = Serial.readString(); // assign incoming data to variable state
    //    Serial.print(serialBuffer);

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(jsonBuffer, serialBuffer);

    // Test if parsing succeeds.
    if (error)
    {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
    }
    else
    {
      // check to see if the platform thinks this object should be active
      active = jsonBuffer["active"];
      Serial.println(active);
    }
  }

  // If active turn display on, if not, turn off
  if (active)
    display.on();
  else
    display.off();

  // Get a new acc sensor event
  sensors_event_t event;
  accel.getEvent(&event);

  float currX = event.acceleration.x;
  float currY = event.acceleration.y;

  // If current Y acceleration has crossed "5" for the first time, change the song
  if (currY >= 5 && prevY < 5)
  {
    songIndex = random(0, 3);
    display.setSong(songs[songIndex]);
    //    Serial.println("{object: 4, song: " + (String) songIndex +"}");
  }

  // If the force in X has cahnged by more than 0.2, update the volume
  if (abs(abs(prevX) - abs(currX)) > 0.2)
  {

    // Map X Axis of Acc to "Volume", multiple and then divide by 100 for more refined map
    float volume = map(currX * 100, -8 * 100, 2 * 100, 0 * 100, 100 * 100) / 100;

    // Set volume based on mapped values
    display.setVolume(volume);
    //    Serial.println("{object: 4, volume: " + (String) volume +"}");
  }
  //    delay(100);

  prevX = currX;
  prevY = currY;
}
