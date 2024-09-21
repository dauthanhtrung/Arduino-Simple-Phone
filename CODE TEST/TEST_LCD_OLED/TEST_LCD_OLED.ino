#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

void setup(void) {
   u8g2.begin();
   u8g2.
}

void loop(void) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_te ); 
  u8g2.drawStr(32,32,"1");
  u8g2.sendBuffer();
  delay(3000);

  // u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_te ); 
  u8g2.drawStr(64,24,"2");
  u8g2.sendBuffer();
  delay(3000);

  // u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_te ); 
  u8g2.drawStr(96,16,"3");
  u8g2.sendBuffer();
  delay(3000);

  // u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_te ); 
  u8g2.drawStr(120,8,"4");
  u8g2.sendBuffer();
  delay(3000);
}
