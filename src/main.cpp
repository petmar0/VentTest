#include <Arduino.h>
#include <Wire.h>
#include "SparkFunBME280.h"
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

BME280 mySensor;

void setup()
{
  Serial.begin(9600);
  Serial.println("Reading basic values from BME280");
  Wire.begin();
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
  u8g2.begin();
}

void loop()
{
  double P=mySensor.readFloatPressure()/133;
  char press[5];
  Serial.println(P, 2);
  sprintf(press, "%.2f", P);
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(0,10,press);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(50);
}
