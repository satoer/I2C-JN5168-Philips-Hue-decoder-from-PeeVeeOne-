# PeeVeeOne I2C JN5168 Philips Hue decoder example code.
   Based on the PeeVeeOne Hue "Light_ColorLight_JN5168_ME_4_REGULAR" Mesh bee / JN5168 firmware
   See: https://peeveeone.com/?page_id=252|
   and https://github.com/peeveeone/ZLL_RGB

   For use with Arduino Due: Use pin 20 for data (Pin D17 on Mesh Bee) and 21 (Pin D16 on Mesh Bee) for clock
   This does not seem to work on the ESP arduino's. Probably because of a hardware I2C limitation.
   Have not test the 8 bit Arduino's (mega / uno etc) It will probably work, but make sure you use a 3.3V / 5V bidirectional level shifter.
   If you want to use it with WS2812 Leds: The Adafruit Neo pixel library seems to work best.
   The Fast led library tends to flicker when lots of lights are adjusted (probably an interrupt issue)

