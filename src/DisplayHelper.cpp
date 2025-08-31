#include "DisplayHelper.h"
#include <Wire.h>

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

void displayInit() {
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
}

void displayShowStatus(const char* msg, int batteryPercent) {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 15, msg);
    char batt[20];
    snprintf(batt, sizeof(batt), "Battery: %d%%", batteryPercent);
    u8g2.drawStr(0, 35, batt);
    u8g2.sendBuffer();
}
