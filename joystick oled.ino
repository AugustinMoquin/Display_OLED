/*********************************************************************
  This is an example for our Monochrome OLEDs based on SH110X drivers

  This example is for a 128x64 size display using SPi to communicate
  5 pins are required to interface 

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution

  SPi SH1106 modified by Rupert Hirst  12/09/21
*********************************************************************/



#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


#define OLED_MOSI     10
#define OLED_CLK      8
#define OLED_DC       7
#define OLED_CS       5
#define OLED_RST      9
#define JOYSTICK_X A0
#define JOYSTICK_Y A1


int point_x = 64;  // position x initiale
int point_y = 32;  // position y initiale


// Create the OLED display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

void setup()   {
  Serial.begin(9600);
  // Start OLED
  display.begin(0, true); // we dont use the i2c address but we will reset!
  display.clearDisplay();
  display.drawPixel(10, 10, SH110X_WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
  
}


void loop() {

  int joystick_x = analogRead(JOYSTICK_X);
  int joystick_y = analogRead(JOYSTICK_Y);

  // déplacer le point en fonction des entrées joystick
  if (joystick_x > 700) { point_x++; }
  if (joystick_x < 300) { point_x--; }
  if (joystick_y > 700) { point_y--; }
  if (joystick_y < 300) { point_y++; }

  // ajuster la position du point pour rester dans les limites de l'écran
  point_x = max(0, min(display.width() - 1, point_x));
  point_y = max(0, min(display.height() - 1, point_y));

  Serial.print("x = ");
  Serial.println(joystick_x);
  Serial.print("y = ");
  Serial.println(joystick_y);  

  // dessiner le point
  display.clearDisplay();
  display.drawPixel(point_x, point_y, SH110X_WHITE);
  display.display();

  // ajouter un délai pour éviter les mouvements trop rapides du point
  delay(50);
  
   
  /*display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("hello world!");
  display.setTextColor(SH110X_BLACK, SH110X_WHITE); // 'inverted' text
  //display.println(3.141592);
  //display.setTextSize(2);
  //display.setTextColor(SH110X_WHITE);
  //display.print("0x"); display.println(0xDEADBEEF, HEX);
  display.display();
  delay(2000);
  display.clearDisplay();*/
}
