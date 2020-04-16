/*==========================================================
   PeeVeeOne I2C JN5168 Philips Hue decoder example code.
   Based on the PeeVeeOne Hue "Light_ColorLight_JN5168_ME_4_REGULAR" Mesh bee / JN5168 firmware
   See: https://peeveeone.com/?page_id=252|
   and https://github.com/peeveeone/ZLL_RGB

   For use with Arduino Due: Use pin 20 for data (Pin D17 on Mesh Bee) and 21 (Pin D16 on Mesh Bee) for clock
   This does not seem to work on the ESP arduino's. Probably because of a hardware I2C limitation.
   Have not test the 8 bit Arduino's (mega / uno etc) It will probably work, but make sure you use a 3.3V / 5V bidirectional level shifter.
   If you want to use it with WS2812 Leds: The Adafruit Neo pixel library seems to work best.
   The Fast led library tends to flicker when lots of lights are adjusted (probably an interrupt issue)

  =========================================================*/

#include <Wire.h>

#define RED 0
#define GREEN 1
#define BLUE 2

bool newData = false;
byte Lights[4][3] = {
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0},
  {0, 0, 0}
};

void setup()
{
  Wire.begin(0x40);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);    // register event

  Serial.begin(115200);           // start serial for output
  Serial.println();
  Serial.println("==================");
  Serial.println("Start I2c reciever");
  Serial.println("==================");
}

void loop()
{
  if (newData) {
    //Debug:
    String DebugLine = "";
    for (int i = 0; i < 4; i++) {
      DebugLine = DebugLine + " L" + String(i) + "-RGB:" + String(Lights[i][RED]) + ", " + String(Lights[i][GREEN]) + ", " + String(Lights[i][BLUE]);
    }
    Serial.println (DebugLine);
    newData = false;
  }
}


void receiveEvent(int howMany)
{
  if (howMany == 13) { //It's always 13, just a precaution in case of a reading error
    int Address = 0;
    for (int i = 0; i < howMany; i++) {
      int Data = Wire.read();
      switch (i) {
        case 0:
          Address = ((Data + 6) / 12) - 1; //convert 6, 18, 30 and 42 to 1,2,3,4
          break;
        case 3:
          Lights[Address][RED] = Data;
          break;
        case 4:
          Lights[Address][RED] = (Lights[Address][RED] + (256 * Data)) / 16; //convert 12 bit number to 8 bit (4096 => 256)
          break;
        case 7:
          Lights[Address][GREEN] = Data;
          break;
        case 8:
          Lights[Address][GREEN] = (Lights[Address][GREEN] + (256 * Data)) / 16; //convert 12 bit number to 8 bit (4096 => 256)
          break;
        case 11:
          Lights[Address][BLUE] = Data;
          break;
        case 12:
          Lights[Address][BLUE] = (Lights[Address][BLUE] + (256 * Data)) / 16 ; //convert 12 bit number to 8 bit (4096 => 256)
          break;
      }
    }
    newData = true;
  }
}
