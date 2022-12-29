
#include <Wire.h>
 
#define SLAVE_ADDRESS 0x04
 
String strRecievedFromRPi = "";
 
void setup() {
 
pinMode(LED_BUILTIN, OUTPUT);
Wire.begin(SLAVE_ADDRESS);
Wire.onReceive(receiveData);
}
 
void loop() {
}
 
void receiveData(int byteCount) {
 
while ( Wire.available()) {
strRecievedFromRPi = Wire.read();
}
 
// turn on or off the LED
if (strRecievedFromRPi == "1") {
digitalWrite(LED_BUILTIN, HIGH);
}
if (str_recieved_from_RPi == "0") {
digitalWrite(LED_BUILTIN, LOW);
}
 
strRecievedFromRPi = "";
 
}
