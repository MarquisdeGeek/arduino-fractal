#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPFD5408_TouchScreen.h>

#include "mandelbrot.h"

// Circuit
#define YP A3 
#define XM A2 
#define YM 9  
#define XP 8 

// Calibrate values
const short TS_MINX=116;
const short TS_MINY=113;
const short TS_MAXX=849;
const short TS_MAXY=872;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

extern const uint8_t baseMandelbrot[] ;

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
Mandelbrot mandel;

void setup(void) {

  Serial.begin(9600);
  
  tft.reset();
  tft.begin(tft.readID());  // Use 0x9341 for the SDFP5408 if readID fails
  tft.setRotation(0);       // Needed for the Mega, please changed for your choice or rotation initial
  tft.fillScreen(0);
 
  pinMode(13, OUTPUT);
    
  mandel.setParameters(-2.2, -1.2, 0.6, 1.2);
  mandel.drawPGMData(baseMandelbrot, 76800L);  
  mandel.draw();
}
   
#define MINPRESSURE 10
#define MAXPRESSURE 1000

void loop()
{
  mandel.update();


  TSPoint pt = ts.getPoint(); 

  pinMode(XM, OUTPUT); //Pins configures again for TFT control
  pinMode(YP, OUTPUT);

  if (pt.z >= MINPRESSURE && pt.z < MAXPRESSURE) {
    pt.x = map(pt.x, TS_MINX, TS_MAXX, 0, tft.width());
    pt.y = map(pt.y, TS_MINY, TS_MAXY, 0, tft.height());;
    
    tft.fillCircle(5, 5, 10, tft.color565(0,0,0));
    mandel.zoomIntoPoint(pt.x, pt.y, 10);
    mandel.draw();
  }
 
}


