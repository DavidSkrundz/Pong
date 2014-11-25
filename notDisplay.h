
#ifndef ArduinoTemplate_notDisplay_h
#define ArduinoTemplate_notDisplay_h

// Screen Drawing Library
#include <Adafruit_ST7735.h>

// Shorter Color Definitions
#define	BLACK ST7735_BLACK
#define	BLUE ST7735_BLUE
#define	RED ST7735_RED
#define	GREEN ST7735_GREEN
#define CYAN ST7735_CYAN
#define MAGENTA ST7735_MAGENTA
#define YELLOW ST7735_YELLOW
#define WHITE ST7735_WHITE

// Standard U Of A Library Settings, Assuming Atmel Mega SPI Pins
#define SD_CS    5  // Chip Select Line For SD Card
#define TFT_CS   6  // Chip Select Line For TFT Display
#define TFT_DC   7  // Data/Command Line For TFT
#define TFT_RST  8  // Reset Line For TFT (Or Connect To +5V)

// Create the screen Hook
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initDisplay() {
	// Initialize Screen
	tft.initR(INITR_BLACKTAB);   // black tab
	tft.fillScreen(BLACK);
}

#endif
