#include <server/server.h>
#include <string.h>
#include <iostream>

bool deviceConnected = false;

//BLE server name
#define bleServerName "Azuby's ESP32"
#define LED_PIN 23

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "91bad492-b950-4226-aa2b-4ede9fa42f59"

BLEServer *bleServer;
BLEService *bleService;
BLECharacteristic testCharacteristics("ca73b3ba-39f6-4ab3-91ae-186dc9577d99", 
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor testDescriptor(BLEUUID((uint16_t)0x2903));

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("isConnected\n");
    pinMode(LED_PIN, OUTPUT);   
  };
  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("\nisDisconnected");
    BLEServerStartService();
  }
};

class MyCharacteristicCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();
    if (value.length() > 0) {
      Serial.println(strcmp(value.c_str(), "true"));
      if (strcmp(value.c_str(), "true") == 0) {
        digitalWrite(LED_PIN, HIGH);
      } else if (strcmp(value.c_str(), "false") == 0) {
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
};

void BLEServerStartService() {
  // Create the BLE Service
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  bleServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...\n");
}

void BLEServerStopService() {
  bleService->stop();
}

void BLEServerSetup() {
      // Create the BLE Device
  BLEDevice::init(bleServerName);

  // Create the BLE Server
  bleServer = BLEDevice::createServer();
  bleServer->setCallbacks(new MyServerCallbacks());

  bleService = bleServer->createService(SERVICE_UUID);

  testCharacteristics.setCallbacks(new MyCharacteristicCallbacks());
  bleService->addCharacteristic(&testCharacteristics);
  testDescriptor.setValue("Test description value!");
  testCharacteristics.addDescriptor(&testDescriptor);

  bleService->start();
}

void BLEServerPerformAction() {
  if (deviceConnected) {
    // testCharacteristics.setValue("Test send value!");
    // testCharacteristics.notify();
    // Serial.println("Send\n\n");
  } else {
    
  }
}