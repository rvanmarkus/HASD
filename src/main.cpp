
#include <Wire.h>    // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include "OLEDDisplayUi.h"
#include <Hash.h>

#include "images.h"

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
// SSD1306Spi        display(D0, D2, D8);
// or
// SH1106Spi         display(D0, D2);

// Initialize the OLED display using brzo_i2c
// D3 -> SDA
// D5 -> SCL
// SSD1306Brzo display(0x3c, D3, D5);
// or
// SH1106Brzo  display(0x3c, D3, D5);

// Initialize the OLED display using Wire library
#include <esphomelib/application.h>
// SH1106 display(0x3c, D3, D5);
SSD1306 display(0x3c, D2, D1);
OLEDDisplayUi ui(&display);

esphomelib::Application::MakeGPIOBinarySensor switchSensor;
char *currentNotification = "No notifications";
using namespace esphomelib;
bool showNotification = false;
int shownNotificationCounter = 0;

void msOverlay(OLEDDisplay *display, OLEDDisplayUiState* state) {
//   display->setTextAlignment(TEXT_ALIGN_RIGHT);
//   display->setFont(ArialMT_Plain_10);
//   display->drawString(128, 0, String(millis()));
    if (showNotification) {
        display->drawXbm(112,0, 16, 16, alarm);
    }
}

void drawLightsFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // draw an xbm image.
  // Please note that everything that should be transitioned
  // needs to be drawn relative to x and y

  display->drawXbm(x + 34, y + 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}

void drawNotificationFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  // Text alignment demo

  // The coordinates define the left starting point of the text
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(0 + x, 10 + y, "Notification:");
  display->setFont(ArialMT_Plain_16);
  display->drawStringMaxWidth(0 + x, 24 + y, 128, currentNotification);

  // The coordinates define the center of the text
//   display->setTextAlignment(TEXT_ALIGN_CENTER);
//   display->drawString(64 + x, 22 + y, "Center aligned (64,22)");

  // The coordinates define the right end of the text
//   display->setTextAlignment(TEXT_ALIGN_RIGHT);
//   display->drawString(128 + x, 33 + y, "Right aligned (128,33)");
}


// This array keeps function pointers to all frames
// frames are the single views that slide in
FrameCallback frames[] = { drawNotificationFrame, drawLightsFrame };

// how many frames are there?
int frameCount = 2;

// Overlays are statically drawn on top of a frame eg. a clock
OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;

void onNotification(const std::string &message)
{
    Serial.println("onNotification");
    currentNotification = new char[message.length() + 1];
    strcpy(currentNotification, message.c_str());
    Serial.println(currentNotification);
    showNotification = true;
}


void setupUI()
{
    ui.setTargetFPS(30);
    ui.setActiveSymbol(activeSymbol);
    ui.setInactiveSymbol(inactiveSymbol);
    ui.setIndicatorPosition(BOTTOM);
    // Defines where the first frame is located in the bar.
    ui.setIndicatorDirection(LEFT_RIGHT);

    // You can change the transition that is used
    // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
    ui.setFrameAnimation(SLIDE_LEFT);

    // Add frames
    ui.setFrames(frames, frameCount);
    ui.setOverlays(overlays, overlaysCount);
    ui.init();
}

void setup()
{

    App.set_name("livingroom-notification");
    App.init_log();

    App.init_wifi("Walhalla", "W0danHeerst");
    auto mqttClient = App.init_mqtt("192.168.178.186", "", "");
    // App.init_ota()->start_safe_mode();
    mqttClient->subscribe("livingroom-notification", onNotification);
    auto aswitch = App.make_gpio_binary_sensor("Switch1", 16);
    App.setup();
    // Initialising the UI will init the display too.

    setupUI();

    display.flipScreenVertically();
}
void resetNotificationIcon() {
    if (showNotification && shownNotificationCounter > 500) {
        shownNotificationCounter = 0;
        showNotification = false;
    } else {
        shownNotificationCounter++;
    }
}

void loop()
{
    // draw the current demo method
    int remainingTimeBudget = ui.update();
    App.loop();
    resetNotificationIcon();
    if (remainingTimeBudget > 0) {
        // You can do some work here
        // Don't do stuff if you are below your
        // time budget.
        delay(remainingTimeBudget);
    }
}
