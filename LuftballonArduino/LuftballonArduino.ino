/*
 Name:		LuftballonArduino.ino
 Created:	12/4/2018 11:13:28 AM
 Author:	Mads
*/

#include "BluetoothController.h"
#include <Servo.h>

BluetoothController bluetoothController{ 10, 11 };

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	bluetoothController.Setup(9600);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
}

// the loop function runs over and over again until power down or reset
void loop() {
	bluetoothController.Loop();

}
