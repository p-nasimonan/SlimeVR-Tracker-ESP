#include "DisplayHelper.h"
#include <Wire.h>
#include <WiFi.h>

U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

void displayInit() {
    u8g2.begin();
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(0, 15, "SlimeVR");
    u8g2.drawStr(0, 25, "ESP32-C3");
    u8g2.sendBuffer();
    delay(2000);
}

void displayShowStatus(const char* msg, int batteryPercent) {
    u8g2.clearBuffer();
    u8g2.drawStr(0, 15, msg);
    char batt[20];
    snprintf(batt, sizeof(batt), "Battery: %d%%", batteryPercent);
    u8g2.drawStr(0, 35, batt);
    u8g2.sendBuffer();
}

void displayShowDetailedStatus(const char* wifiSSID, bool slimevrConnected, float batteryVoltage) {
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_5x8_tf);
    
    // WiFi情報（1行目）
    if (WiFi.isConnected() && wifiSSID && strlen(wifiSSID) > 0) {
        char wifi[16];
        snprintf(wifi, sizeof(wifi), "WiFi:%.10s", wifiSSID);
        u8g2.drawStr(0, 8, wifi);
    } else {
        u8g2.drawStr(0, 8, "WiFi:None");
    }
    
    // SlimeVR接続状況（2行目）
    if (slimevrConnected) {
        u8g2.drawStr(0, 18, "SlimeVR:OK");
    } else {
        u8g2.drawStr(0, 18, "SlimeVR:--");
    }
    
    // バッテリー電圧（3行目）
    char voltage[16];
    snprintf(voltage, sizeof(voltage), "Batt:%.2fV", batteryVoltage);
    u8g2.drawStr(0, 28, voltage);
    
    // バッテリー残量バー（4行目）
    int barWidth = (int)((batteryVoltage - 3.0) / 1.2 * 60); // 3.0V-4.2Vを60pxにマップ
    if (barWidth < 0) barWidth = 0;
    if (barWidth > 60) barWidth = 60;
    u8g2.drawFrame(0, 32, 62, 6);
    u8g2.drawBox(1, 33, barWidth, 4);
    
    u8g2.sendBuffer();
}
