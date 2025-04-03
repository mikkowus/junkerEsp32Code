// This example code is in the Public Domain (or CC0 licensed, at your option.)
// By Evandro Copercini - 2018
//
// This example creates a bridge between Serial and Classical Bluetooth (SPP)
// and also demonstrate that SerialBT have the same functionalities of a normal Serial
// Note: Pairing is authenticated automatically by this device

#include "BluetoothSerial.h"

String device_name = "ESP32-BT-Slave";

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;


String message = "";
char incomingChar;

void setup() {
  Serial.begin(115200);
  SerialBT.begin(device_name);  //Bluetooth device name
  //SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  
}

void loop() {

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    //Serial.write(SerialBT.read());
    Serial.printf("in if SerialBT.available()\n");
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.printf("incomingChar: ");
    Serial.write(incomingChar);
    Serial.printf("\n");
  }

  if (message =="on"){
        Serial.printf("\nled is supposed to turn on.\n");
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else if (message =="off"){
      Serial.printf("\nled is supposed to turn off.\n");
      digitalWrite(LED_BUILTIN, LOW);
    }

  delay(20);
}



/////////////////////////
