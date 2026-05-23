#ifndef HW_CONFIG_H
#define HW_CONFIG_H

// ======================================================
// SOUND
// ======================================================

#define ENABLE_SOUND 0

// ======================================================
// SD CARD
// ======================================================
// NO tiene slot

#define SD_CS      -1
#define SD_SCK     -1
#define SD_MOSI    -1
#define SD_MISO    -1

// ======================================================
// I2S AUDIO
// ======================================================
// Sin usar por ahora

#define I2S_DO     -1
#define I2S_BCK    -1
#define I2S_WS     -1

// ======================================================
// TFT DISPLAY - T-Display-S3
// ST7789 i8080 Parallel 8bit
// ======================================================

#define PIN_LCD_BL    38

#define PIN_LCD_D0    39
#define PIN_LCD_D1    40
#define PIN_LCD_D2    41
#define PIN_LCD_D3    42
#define PIN_LCD_D4    45
#define PIN_LCD_D5    46
#define PIN_LCD_D6    47
#define PIN_LCD_D7    48

#define PIN_POWER_ON  15

#define PIN_LCD_RES   5
#define PIN_LCD_CS    6
#define PIN_LCD_DC    7
#define PIN_LCD_WR    8
#define PIN_LCD_RD    9

// ======================================================
// BUTTONS
// ======================================================

#define BTN_A         0
#define BTN_B         14
#define BTN_UP        -1
#define BTN_DOWN      -1
#define BTN_LEFT      -1
#define BTN_RIGHT     -1
#define BTN_START     -1
#define BTN_SELECT    -1

#endif
