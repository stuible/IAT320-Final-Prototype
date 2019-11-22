/* 
Inspired by https://processing.org/reference/libraries/sound/SoundFile.html
*/

import processing.serial.*;
import processing.sound.*;

SoundFile file;

Serial serial;
String serialBuffer;

void setup() {
  size(640, 360);
  background(255);

  try {
    //Open USB Serial Port
    println(Serial.list()); 
    serial = new Serial(this, Serial.list()[6], 38400);
    println("OPENING PORT");
  }
  catch(Exception e) {
    println("PORT NOT AVAILABLE");
  }
  
  // Instantiate serial buffer string
  serialBuffer = "";

  // Load a soundfile from the /data folder of the sketch and play it back
  file = new SoundFile(this, "imissyou.mp3");
  file.play();
}      

void draw() {
  
  // Pulls serial JSON data into buffer if available.
  if (serial != null) {
    while (serial.available() > 0) {
      String inBuffer = serial.readString();   
      if (inBuffer != null) {

        serialBuffer += inBuffer;

        //Recived completed json object and can now process it
        if (serialBuffer.endsWith("\n")) {

          // Confirm we started listening in time to recieve the beginning of the JSON object
          JSONObject json = serialBuffer.startsWith("{") ? parseJSONObject(serialBuffer) : null;
          if (json == null) {
            println("JSONObject could not be parsed");
          } else {
            println(serialBuffer);

            // Process Active state if it exists in json object
            if (json.hasKey("active")) {
              boolean active = json.getBoolean("active");
              
              // If object is active, play song
              if(active){
                if(!file.isPlaying()) file.play();
              }
              // If not, stop the song
              else file.stop();

            }
          }

          //Reset buffer
          serialBuffer = "";
        } else {
          //println("Buffer not ready:");
        }
      }
    }
  }
}
