
/*
  This code is specifically designed for an Arduino Uno R4 board. It utilizes the
  ArduinoBLE library to establish a Bluetooth® Low Energy (BLE) service, enabling
  a central device to control the onboard LED. When the central device connects to
  the Arduino and writes a value to a specific characteristic, it will alter the
  state of the LED accordingly. Any non-zero value will turn on the LED, while a
  zero value will turn it off.

  Board: Arduino Uno R4 WiFI
*/


#include <ArduinoBLE.h>

const int leftMotorBack = 5;
const int leftMotorForth = 6;
const int rightMotorBack = 3;
const int rightMotorForth = 4;

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED

void setup() {
pinMode(leftMotorBack, OUTPUT);
pinMode(leftMotorForth, OUTPUT);
pinMode(rightMotorBack, OUTPUT);
pinMode(rightMotorForth, OUTPUT);
Serial.begin(9600);

  while (!Serial);

  // set LED pin to output mode
  pinMode(ledPin, OUTPUT);
   // initialize the Bluetooth® Low Energy hardware
  BLE.begin();

  // set advertised local name and service UUID:
  BLE.setLocalName("UNO R4 LED");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("BLE LED Peripheral");
}
void moveForward(){
digitalWrite(leftMotorForth,HIGH);
digitalWrite(rightMotorForth,HIGH);
}
void moveBackward(){
digitalWrite(leftMotorBack,HIGH);
digitalWrite(rightMotorBack,HIGH);
}
void stop(){
digitalWrite(leftMotorBack,LOW);
digitalWrite(rightMotorBack,LOW);
digitalWrite(leftMotorForth,LOW);
digitalWrite(rightMotorForth,LOW);
}
void turnRight(){
digitalWrite(leftMotorForth,HIGH);
digitalWrite(rightMotorBack,HIGH);
}
void turnLeft(){
digitalWrite(leftMotorBack,HIGH);
digitalWrite(rightMotorForth,HIGH);
}
void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value() == 1) {   // any value other than 0z
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          stop();
          moveForward();
          

        } else if (switchCharacteristic.value() ==2){   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          stop();
          moveBackward();}
          

          else if (switchCharacteristic.value() ==3){   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          stop();
          turnRight();

        }
        else if (switchCharacteristic.value() ==4){   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
          stop();
          turnLeft(); }
          else 
        {                              // a 0 value
          Serial.println(F("LED off"));
          digitalWrite(ledPin, LOW);          // will turn the LED off
          stop();
        }
      }
    }
  }
  }
  

