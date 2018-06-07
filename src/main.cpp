
#include <Wire.h>    // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include "OLEDDisplayUi.h"
#include <Hash.h>
#include "images.h"
#include <Encoder.h>
#include <esphomelib/application.h>

SSD1306 display(0x3c, D6, D5);
OLEDDisplayUi ui(&display);

// Encoder myEnc(D1, D2);
char *currentNotification = "No notifications";
char *currentScene = "No scene activated";
char *currentMediaInput = "No input media";

using namespace esphomelib;
Application::MakeGPIOBinarySensor switchSensor;
mqtt::MQTTClientComponent *mqttClient;

long oldPosition = -999;
bool isButtonPressed = false;
long lastUpdateMillis = 0;

bool showNotification = false;
int shownNotificationCounter = 0;

bool partyButtonActivated = false;


void msOverlay(OLEDDisplay *display, OLEDDisplayUiState *state)
{
    //   display->setTextAlignment(TEXT_ALIGN_RIGHT);
    //   display->setFont(ArialMT_Plain_10);
    //   display->drawString(128, 0, String(millis()));
    display->drawHorizontalLine(0, 20, 128);
    if (showNotification)
    {
        display->drawXbm(112, 0, 16, 16, alarm);
    }

    if (partyButtonActivated)
    {
        display->drawXbm(112, 0, 16, 16, party);
    }
}

void drawScenesFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // Text alignment demo

    // The coordinates define the left starting point of the text
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
    display->drawString(0 + x, 0 + y, "Huidige scene: ");
    // display->drawString(0 + x, 15 + y, "Notification:");
    display->setFont(ArialMT_Plain_16);
    display->drawStringMaxWidth(0 + x, 24 + y, 128, currentScene);
}
void drawMediaInputFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // Text alignment demo

    // The coordinates define the left starting point of the text
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
    display->drawString(0 + x, 0 + y, "Media input: ");
    // display->drawString(0 + x, 15 + y, "Notification:");
    display->setFont(ArialMT_Plain_16);
    display->drawStringMaxWidth(0 + x, 24 + y, 128, currentMediaInput);
}

void drawNotificationFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y)
{
    // Text alignment demo

    // The coordinates define the left starting point of the text
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->setFont(ArialMT_Plain_10);
    display->drawString(0 + x, 0 + y, "Last notification: ");
    // display->drawString(0 + x, 15 + y, "Notification:");
    display->setFont(ArialMT_Plain_16);
    display->drawStringMaxWidth(0 + x, 24 + y, 128, currentNotification);
}
void onSceneButtonPressed()
{
    mqttClient->publish("hasd/scene/cmd", "TOGGLE", 0, false);
}

void onMediaInputButtonPressed()
{
    mqttClient->publish("hasd/media/cmd", "TOGGLE", 0, false);
}

FrameCallback frames[] = {drawNotificationFrame, drawScenesFrame, drawMediaInputFrame};
void (*frameButtonPressCallbacks[])() = {onSceneButtonPressed, onMediaInputButtonPressed, onSceneButtonPressed};
// how many frames are there?
int frameCount = 3;

// Overlays are statically drawn on top of a frame eg. a clock
OverlayCallback overlays[] = {msOverlay};
int overlaysCount = 1;
void handleKey()
{
    ui.nextFrame();
    
}

void onNotification(const std::string &message)
{
    Serial.println("onNotification");
    currentNotification = new char[message.length() + 1];
    strcpy(currentNotification, message.c_str());
    Serial.println(currentNotification);
    showNotification = true;
}
void onMediaInputChange(const std::string &message)
{
    currentMediaInput = new char[message.length() + 1];
    strcpy(currentMediaInput, message.c_str());
}
void onSceneChange(const std::string &message)
{
    currentScene = new char[message.length() + 1];
    strcpy(currentScene, message.c_str());
}
void onPartyButton(const std::string &message)
{

    if (message == "OFF")
    {
        partyButtonActivated = false;
    }
    else
    {
        partyButtonActivated = true;
    }
}

void setupUI()
{
    ui.setTargetFPS(30);
    ui.setActiveSymbol(activeSymbol);
    ui.setInactiveSymbol(inactiveSymbol);
    ui.setIndicatorPosition(BOTTOM);
    // Defines where the first frame is located in the bar.
    ui.setIndicatorDirection(LEFT_RIGHT);
    ui.disableAutoTransition();
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
    Serial.begin(115200);
    pinMode(D3, INPUT_PULLUP);
    attachInterrupt(D3, handleKey, RISING);
    App.set_name("livingroom-notification");
    App.init_log();

    App.init_wifi("Merel8bis_Boven", "eenhoorn");
    mqttClient = App.init_mqtt("192.168.178.22", "", "");
    // App.init_ota()->start_safe_mode();
    mqttClient->subscribe("hasd/notification", onNotification);
    mqttClient->subscribe("hasd/scene/current", onSceneChange);
    mqttClient->subscribe("hasd/media/input", onMediaInputChange);
    mqttClient->subscribe("stat/partybutton/POWER", onPartyButton);
    auto aswitch = App.make_gpio_binary_sensor("Switch1", 16);
    auto rotary = App.make_rotary_encoder_sensor("RotarySwitch", D1, D2);
    App.setup();
    // Initialising the UI will init the display too.

    setupUI();

    display.flipScreenVertically();
}
void resetNotificationIcon()
{
    if (showNotification && shownNotificationCounter > 500)
    {
        shownNotificationCounter = 0;
        showNotification = false;
    }
    else
    {
        shownNotificationCounter++;
    }
}

void loop()
{
    // draw the current demo method
    int remainingTimeBudget = ui.update();
    App.loop();
    resetNotificationIcon();
    // long newPosition = myEnc.read();
    // if (newPosition != oldPosition)
    // {
    //     if (newPosition > oldPosition)
    //     {
    //         ui.nextFrame();
    //     }
    //     else
    //     {
    //         ui.previousFrame();
    //     }
    //     // ui.transitionToFrame(newPosition);
    //     oldPosition = newPosition;
    //     Serial.println(newPosition);
    // }
    if (remainingTimeBudget > 0)
    {
        // You can do some work here
        // Don't do stuff if you are below your
        // time budget.
        delay(remainingTimeBudget);
    }
}
