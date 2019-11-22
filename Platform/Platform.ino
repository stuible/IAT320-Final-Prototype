// Reference
/* Use a photoresistor (or photocell) to turn on an LED in the dark
   More info and circuit schematic: http://www.ardumotive.com/how-to-use-a-photoresistor-en.html
   Dev: Michalis Vasilakis // Date: 8/6/2015 // www.ardumotive.com */

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
//SoftwareSerial BTserial(0, 1); // RX | TX

//Constants
const int pResistor = A5; // Photoresistor at Arduino analog pin A0

//Variables
int value; // Store value from photoresistor (0-1023)
bool active = false;

void setup()
{
  Serial.begin(38400); // Default communication rate of the Bluetooth module

  pinMode(pResistor, INPUT);
}

void loop()
{

  //Read state of photo resistor
  value = analogRead(pResistor);

  // If photoresistor value is < 300, the object is covering it and it is not active
  if (value < 300)
  {
    if (active)
      // Send JSON to computer to let it know the object is not active
      Serial.println("{object: 4, active: false}");
    active = false;
  }
  // If photoresistor value is > 300, the object is picked up and active
  else
  {
    if (!active)
      // Send JSON to computer to let it know the object IS active
      Serial.println("{object: 4, active: true}");
    active = true;
  }

  //  Serial.println("TEST"); // Sends '1' to serialout

  delay(100); //Small delay
}
