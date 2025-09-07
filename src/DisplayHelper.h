#pragma once
#include <U8g2lib.h>

extern U8G2_SSD1306_72X40_ER_F_SW_I2C u8g2;

void displayInit();
void displayShowStatus(const char* msg, int batteryPercent);
void displayShowWiFiStatus(const char* wifiStatus, const char* provisioningStatus, float batteryVoltage);
