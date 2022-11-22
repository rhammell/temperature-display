/*
  Measure and display 24 hours of air temperature measurments

  This sketch programs a Trinket M0 to measure the air temperature 
  every 15 minutes using a TMP36 temperature sensor.

  A 128x32 OLED displays the current temperature along with a graph
  of the previous 24 hours of measurements. 

  Hardware: 
  * Adafruit Trinket M0
  * TMP temperature sensor
  * Monochrome OLED 128x32 display

  Circuit:
  * TMP36 VIN to Trinket M0 3V
  * TMP36 center pin to Trinket M0 pin 4 (A4)
  * TMP GND to Trinket M0 GND
  * OLED SDA to Trinket M0 pin 0 (SDA) 
  * OLED SLC to Trinket M0 pin 2 (SLC) 
  * OLED VIN to Trinket M0 3V
  * OLED GND to Trinket M0 GND
*/


#include <TMP36.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_DotStar.h>

// Onboard Dotstar object
Adafruit_DotStar strip = Adafruit_DotStar(1, INTERNAL_DS_DATA, INTERNAL_DS_CLK, DOTSTAR_BGR);

// Adafruit OLED object
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// OLED character params
#define CHAR_WIDTH 6
#define CHAR_HEIGHT 8

// TMP36 object
#define tempPin A4
TMP36 myTMP36(tempPin, 3.3); 

// Define temperature array
const int nPoints = 96;
int tempArr[nPoints];

void setup()
{
  Serial.begin(9600);

  // Turn off dotstar
  strip.setPixelColor(0, 0, 0, 0);
  strip.show();

  // Initialize display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.setTextColor(SSD1306_WHITE);

}
 
void loop()
{
  // Read current temperature value
  int temp = myTMP36.getTempF();
  Serial.print(temp); Serial.println(" degrees F");

  // Update teperature array
  for (int i=0; i<nPoints-1; i++) {
    tempArr[i] = tempArr[i+1];
  }
  tempArr[nPoints-1] = temp;

  // Find min and max temps
  int minTemp = 1000;   
  int maxTemp = -1000;
  for (int i=0; i<nPoints; i++) {
    maxTemp = max(maxTemp, tempArr[i]);
    minTemp = min(minTemp, tempArr[i]);
  }

  // Reset display
  display.clearDisplay();

  // Display current temp
  int textSize = 2;
  int textX = 0;
  int textY = SCREEN_HEIGHT / 2 - textSize * CHAR_HEIGHT / 2;
  int nChars = String(temp).length();
  int circleX = textX + textSize * nChars * CHAR_WIDTH + textSize;
  int circleY = textY + textSize;
  display.setTextSize(textSize);
  display.setCursor(textX, textY);
  display.print(temp);
  display.drawCircle(circleX, circleY, textSize, WHITE);

  // Draw graph labels
  int maxChars = String(maxTemp).length();
  int minChars = String(minTemp).length();
  int labelChars = max(maxChars, minChars); 
  int labelsX = circleX + textSize * 5;
  display.setTextSize(1);
  display.setCursor(labelsX + (labelChars - maxChars) * CHAR_WIDTH, 0);
  display.print(maxTemp);
  display.setCursor(labelsX + (labelChars - minChars) * CHAR_WIDTH, SCREEN_HEIGHT - CHAR_HEIGHT);
  display.print(minTemp);

  // Define graph bounds
  int graphStartX = labelsX + labelChars * CHAR_WIDTH + 2;
  int graphEndX = SCREEN_WIDTH; 
  int graphStartY = 0;
  int graphEndY = SCREEN_HEIGHT-1;

  // Draw graph axis
  display.drawLine(graphStartX, 0, graphStartX, SCREEN_HEIGHT, SSD1306_WHITE);

  // Plot graph lines
  for (int i=0; i<nPoints-1; i++) {
    int x0 = map(i, 0, nPoints-1, graphStartX, graphEndX);
    int y0 = map(tempArr[i], minTemp, maxTemp, graphEndY, graphStartY);
    int x1 = map(i+1, 0, nPoints-1, graphStartX, graphEndX);
    int y1 = map(tempArr[i+1], minTemp, maxTemp, graphEndY, graphStartY);
    display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);
  }

  // Update display
  display.display(); 

  // Delay 15 mins
  int minutes = 15;
  delay(1000L * 60 * minutes);                                   
}