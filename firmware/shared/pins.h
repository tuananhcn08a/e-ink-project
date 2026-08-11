// Shared pin map for the E-Ink bring-up kit
// Board: ESP32-DevKitC v4 (ESP32-WROOM-32, chip ESP32-D0WDQ6)
// Wiring is IDENTICAL for the 4.2" and 7.5" panels via the seller's adapter board.
// Decoded from the seller's demo sketches (share_code_Eink):
//   SPI.begin(SCK, MISO, MOSI, SS) = SPI.begin(13, -1, 14, 15)
//   GxEPD2_XXXc(CS, DC, RST, BUSY) = (15, 27, 26, 25)
//
// | Signal | ESP32 GPIO |
// |--------|------------|
// | CS     | 15         |
// | DC     | 27         |
// | RST    | 26         |
// | BUSY   | 25         |
// | SCK    | 13         |
// | MOSI   | 14         |
// | MISO   | not used   |
#pragma once

#define EPD_CS   15
#define EPD_DC   27
#define EPD_RST  26
#define EPD_BUSY 25
#define EPD_SCK  13
#define EPD_MOSI 14
