#pragma once

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>
#include <Arduino.h>

#define WIFI_SSID "WIFI SSID"  // Your WIFI SSID
#define WIFI_PASSWORD "WIFI PASSWORD"   // Your WIFI PASSWORD

#define LED1 4

void sentHtml();
void connectWifi();
int getNumbersAndCalculate();

