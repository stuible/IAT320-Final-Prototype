#include <Arduino.h>

// Include NewLiquidCrystal Library for I2C
#include <LiquidCrystal_I2C.h>

// Include Wire Library for I2C
#include <Wire.h>

// References
/*
  LCD Display with I2C Interface Demo
  lcd-i2c-demo.ino
  Use NewLiquidCrystal Library
  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/
//


class Display {

  private:
    // Define LCD pinout
    const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;

    const int i2c_addr = 0x27;
    
    // Create pointer that will eventually be instantiated with LiquidCrystal_I2C contructor
    LiquidCrystal_I2C *lcd;

  public:
    Display();

    void begin();
    void update();

    void print(String text);
    void setSong(String song);
    void setVolume(int volume);
    void off();
    void on();
};
