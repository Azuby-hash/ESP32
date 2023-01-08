#ifndef SERVER_h
#define SERVER_h

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

extern bool deviceConnected;
extern bool checkDeviceConnected;

extern BLEServer *bleServer;
extern BLECharacteristic testCharacteristics;
extern BLEDescriptor testDescriptor;

void BLEServerStartService();

void BLEServerStopService();

void BLEServerSetup();

void BLEServerPerformAction();

#endif