
#include "functions.h"


void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);

  connectWifi();
}

void loop() {
  server.handleClient();
  delay(2);
}
