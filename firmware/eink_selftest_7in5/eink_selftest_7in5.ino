// E-Ink hardware self-test — 7.5" 3-color (black/white/red), 640x384
// Board: ESP32-DevKitC v4. Panel driver: GxEPD2_750c.
//
// Purpose: prove the kit + panel are healthy. Draws a test pattern that makes
// defects obvious: full-panel border, corner markers, black/red bands, a
// diagonal, and text. If any region is missing, smeared, or a color is dead,
// the panel or the FFC connection is suspect.
//
// Pins (see firmware/shared/pins.h): CS=15 DC=27 RST=26 BUSY=25 SCK=13 MOSI=14

#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <SPI.h>

#define EPD_CS   15
#define EPD_DC   27
#define EPD_RST  26
#define EPD_BUSY 25
#define EPD_SCK  13
#define EPD_MOSI 14

// GxEPD2_750c: 640 x 384, 3-color. Page height limited to fit ESP32 RAM.
GxEPD2_3C<GxEPD2_750c, GxEPD2_750c::HEIGHT / 2> display(
    GxEPD2_750c(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

void drawTestPattern() {
  const int W = display.width();
  const int H = display.height();

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    // 1) Outer border — reveals edge/scan-line defects.
    display.drawRect(0, 0, W, H, GxEPD_BLACK);
    display.drawRect(4, 4, W - 8, H - 8, GxEPD_RED);

    // 2) Corner solid squares — check all four corners actually update.
    const int c = 40;
    display.fillRect(0, 0, c, c, GxEPD_BLACK);
    display.fillRect(W - c, 0, c, c, GxEPD_RED);
    display.fillRect(0, H - c, c, c, GxEPD_RED);
    display.fillRect(W - c, H - c, c, c, GxEPD_BLACK);

    // 3) Color bands — black band and red band side by side.
    display.fillRect(60, 70, (W - 120) / 2 - 5, 40, GxEPD_BLACK);
    display.fillRect(60 + (W - 120) / 2 + 5, 70, (W - 120) / 2 - 5, 40, GxEPD_RED);

    // 4) Diagonal line — catches missing columns/rows.
    display.drawLine(60, 130, W - 60, H - 60, GxEPD_BLACK);

    // 5) Text in both colors.
    display.setFont(&FreeMonoBold18pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(70, 210);
    display.print("E-INK 7.5 SELF-TEST");
    display.setTextColor(GxEPD_RED);
    display.setCursor(70, 255);
    display.print("kit + panel OK");

    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(70, 300);
    display.printf("res %dx%d  driver GxEPD2_750c", W, H);
  } while (display.nextPage());
}

void setup() {
  Serial.begin(115200);
  delay(300);
  Serial.println();
  Serial.println("=== E-Ink 7.5\" self-test ===");
  Serial.printf("BUSY pin (%d) idle level: %d\n", EPD_BUSY, digitalRead(EPD_BUSY));

  SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
  display.init(115200);
  Serial.printf("Panel reports: %d x %d\n", display.width(), display.height());

  Serial.println("Drawing test pattern...");
  drawTestPattern();
  Serial.println("Done. Hibernating.");
  display.hibernate();
}

void loop() {}
