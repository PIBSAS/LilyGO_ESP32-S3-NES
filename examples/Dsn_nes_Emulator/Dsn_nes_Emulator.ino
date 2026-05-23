#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <FS.h>
#include <LittleFS.h>
#include <driver/spi_master.h>
#include <esp_heap_caps.h>
#include "hw_config.h"
#include "tft_driver.h"
 
TFTDriver tft;

extern void setup_controller();
extern "C" int nofrendo_main(int argc, char* argv[]);
extern "C" bool vid_preload_rom(const char* path);
extern "C" int show_menu();
extern "C" const char* get_selected_game();

void setup() {
  Serial.begin(115200);
  delay(100); 
  Serial.println("\n\n====================================");
  Serial.println("NES Emulator Setup - T-Display-S3");
  Serial.println("====================================\n");
 
  setup_controller();
  Serial.println("[1/5] Controller initialized.");
  Serial.println("[2/5] Initializing TFT");

  tft.init();

  tft.fillScreen(TFT_BLACK);

  Serial.printf(
      "     TFT ready: %dx%d\n",
      DISPLAY_WIDTH,
      DISPLAY_HEIGHT
  );
 
    // ==================================================
    // LITTLEFS
    // ==================================================

    Serial.println("[3/5] Mounting LittleFS");

    if (!LittleFS.begin(true)) {

        Serial.println("     LittleFS mount FAILED");

    } else {

        Serial.println("     LittleFS mounted");

        File root = LittleFS.open("/");

        File file = root.openNextFile();

        while (file) {

            Serial.printf(
                "     %s (%d bytes)\n",
                file.name(),
                file.size()
            );

            file = root.openNextFile();
        }
    }

    // ==================================================
    // OPTIONAL SD
    // ==================================================

    Serial.println("[4/5] SD Card");

#if SD_CS >= 0

    SPIClass spiSD(SPI2_HOST);

    spiSD.begin(
        SD_SCK,
        SD_MISO,
        SD_MOSI,
        SD_CS
    );

    if (!SD.begin(SD_CS, spiSD, 20000000)) {

        Serial.println("     SD not detected");

    } else {

        Serial.println("     SD mounted");

        File root = SD.open("/");

        File file = root.openNextFile();

        while (file) {

            Serial.printf(
                "     SD: %s (%d bytes)\n",
                file.name(),
                file.size()
            );

            file = root.openNextFile();
        }
    }

#else

    Serial.println("     SD disabled in hw_config");

#endif

    // ==================================================
    // MEMORY
    // ==================================================

    Serial.println("[5/5] Memory");

    Serial.printf(
        "     Free heap: %u bytes\n",
        esp_get_free_heap_size()
    );

    Serial.printf(
        "     Free PSRAM: %u bytes\n",
        heap_caps_get_free_size(MALLOC_CAP_SPIRAM)
    );

    Serial.printf(
        "     Total PSRAM: %u bytes\n",
        heap_caps_get_total_size(MALLOC_CAP_SPIRAM)
    );

    if (heap_caps_get_total_size(MALLOC_CAP_SPIRAM) == 0) {

        Serial.println();
        Serial.println("WARNING: PSRAM NOT DETECTED");
        Serial.println("Enable OPI PSRAM in board settings");
    }

    Serial.println();
    Serial.println("====================================");
    Serial.println("Setup complete");
    Serial.println("====================================");

    delay(300);

    // ==================================================
    // MENU
    // ==================================================

    int selected = show_menu();

    if (selected < 0) {

        Serial.println("No ROM selected");

        return;
    }

    const char* rom_file = get_selected_game();

    Serial.printf(
        "Starting ROM: %s\n",
        rom_file
    );

#if ENABLE_SOUND

    char* argv[] = {
        (char*)"nes",
        (char*)"-sound",
        (char*)"-volume",
        (char*)"100",
        (char*)"-sample",
        (char*)"16000",
        (char*)rom_file
    };

    nofrendo_main(7, argv);

#else

    char* argv[] = {
        (char*)"nes",
        (char*)"-nosound",
        (char*)rom_file
    };

    nofrendo_main(3, argv);

#endif
}

// ======================================================
// LOOP
// ======================================================

void loop() {

    delay(1000);
}
