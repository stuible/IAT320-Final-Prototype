#include "Display.h"


// Constructor
Display::Display() {
  lcd = new LiquidCrystal_I2C(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
}

// Init code for lcd class
void Display::begin() {
  // Set display type as 16 char, 2 rows
  lcd->begin(16, 2);
}
void Display::update() {

}

// Print text on display
void Display::print(String text) {
  lcd->print(text);
}

// Turn off display
void Display::off() {
  lcd->noBacklight();
}

// Turn on display
void Display::on() {
  lcd->backlight();
}

// Set first row of screen song title
void Display::setSong(String song) {
  lcd->setCursor(0, 0);
  lcd->print("                      ");
  lcd->setCursor(0, 0);
  print(song);
}

// Set second row of screen to volume
void Display::setVolume(int volume) {
  lcd->setCursor(0, 1);
  print("Volume: " + (String) volume + "db");
}
