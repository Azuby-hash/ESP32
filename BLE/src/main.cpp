/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-ble-server-client/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#include <server/server.h>

void setup() {
  // Start serial communication 
  Serial.begin(9600);
  BLEServerSetup();
  BLEServerStartService();
}

void loop() {
  BLEServerPerformAction();
  delay(3000);
}

