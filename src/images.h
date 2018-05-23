#define WiFi_Logo_width 60
#define WiFi_Logo_height 36
const uint8_t WiFi_Logo_bits[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0x03, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0xFF, 0x07, 0xC0, 0x83, 0x01, 0x80, 0xFF, 0xFF, 0xFF,
  0x01, 0x00, 0x07, 0x00, 0xC0, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x0C, 0x00,
  0xC0, 0xFF, 0xFF, 0x7C, 0x00, 0x60, 0x0C, 0x00, 0xC0, 0x31, 0x46, 0x7C,
  0xFC, 0x77, 0x08, 0x00, 0xE0, 0x23, 0xC6, 0x3C, 0xFC, 0x67, 0x18, 0x00,
  0xE0, 0x23, 0xE4, 0x3F, 0x1C, 0x00, 0x18, 0x00, 0xE0, 0x23, 0x60, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xE0, 0x03, 0x60, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x07, 0x60, 0x3C, 0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C,
  0xFC, 0x73, 0x18, 0x00, 0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00,
  0xE0, 0x87, 0x70, 0x3C, 0x1C, 0x70, 0x18, 0x00, 0xE0, 0x8F, 0x71, 0x3C,
  0x1C, 0x70, 0x18, 0x00, 0xC0, 0xFF, 0xFF, 0x3F, 0x00, 0x00, 0x08, 0x00,
  0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x0C, 0x00, 0x80, 0xFF, 0xFF, 0x1F,
  0x00, 0x00, 0x06, 0x00, 0x80, 0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x07, 0x00,
  0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0xF8, 0xFF, 0xFF,
  0xFF, 0x7F, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x01, 0x00, 0x00,
  0x00, 0x00, 0xFC, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFF,
  0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xFF, 0x1F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };

  const uint8_t activeSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00011000,
    B00100100,
    B01000010,
    B01000010,
    B00100100,
    B00011000
};

const uint8_t inactiveSymbol[] PROGMEM = {
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000
};

const uint8_t bulb[] PROGMEM = {
  0x00, 0x00, 0xC0, 0x07, 0x20, 0x08, 0x10, 0x10, 0x08, 0x20, 0x08, 0x20, 
  0x08, 0x20, 0x08, 0x20, 0x08, 0x20, 0x10, 0x10, 0x20, 0x08, 0xC0, 0x07, 
  0x40, 0x04, 0xC0, 0x07, 0x40, 0x04, 0xC0, 0x07, };

const uint8_t switch_off[] PROGMEM = {
  0x00, 0x00, 0xFE, 0x7F, 0xFE, 0x7F, 0xFA, 0x7F, 0xF2, 0x7F, 0xE2, 0x7F, 
  0xC2, 0x7F, 0x82, 0x7F, 0x02, 0x7F, 0x02, 0x7E, 0x02, 0x7C, 0x02, 0x78, 
  0x02, 0x70, 0x02, 0x60, 0xFE, 0x7F, 0x00, 0x00, };

const uint8_t switch_on[] PROGMEM = {
  0x00, 0x00, 0xFE, 0x7F, 0x06, 0x40, 0x0E, 0x40, 0x1E, 0x40, 0x3E, 0x40, 
  0x7E, 0x40, 0xFE, 0x40, 0xFE, 0x41, 0xFE, 0x43, 0xFE, 0x47, 0xFE, 0x4F, 
  0xFE, 0x5F, 0xFE, 0x7F, 0xFE, 0x7F, 0x00, 0x00, };
const uint8_t alarm[] PROGMEM = {
  0x01, 0x81, 0x02, 0x41, 0x04, 0x21, 0xC8, 0x17, 0xE0, 0x0F, 0xF0, 0x1F, 
  0xF0, 0x1D, 0xF8, 0x39, 0xF8, 0x39, 0xF8, 0x31, 0xFC, 0x71, 0xFC, 0x71, 
  0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0x00, 0x00, };
