#include <SPI.h>
#include <LoRa.h>

// hardware used: invisiblefun.com, saying a company of HongKong based, 
// LoRaWAN chip: SX1276 LoRaWAN
// MCU: Atmega328PB or Atmega328PU or LGT8F328P is pin/pin or object code compatible (www.lgtic.com)
// Real Time Clock: AM8025, AmbiqMirco (ST/TSMC coop company, ASE Taiwan assembly)
// RF power Amp: PSemi chip marking SPA (Murata subsidary, Murata Taiwan assembly /Amkor Korea assembly)
// PCB: Mini LoRa Development Board, PCB V2.0 (China OEM PCB)
// ref: https://www.facebook.com/invisiblefun/posts/pfbid0HpNUCBseRqBnQ8sZ2f5QberJxqALRAVBevNrfMchXY3tJSkpYHzkCUTYtWmqsRGNl 
//      In case you need circuit diagram / schematic, written request is available at xiao_laba_cn@yahoo.com
//      or load the simplified diagram by webpage, https://github.com/xiaolaba/AVR_IFS_LoRa_simpleGateway_testing
//      2022-02-05, xiaolaba
#include "LED.hpp"  // LED blink every second, and for SX1276 pin assignment, and hex stamp of build

// software requirement for development,
// install library https://github.com/sandeepmistry/arduino-LoRa
// install Minicore to support Atmega328PB


//const long frequency = 915E6;  // LoRa Frequency 915MHZ
const long frequency = 923E6;  // LoRa Frequency 923MHZ




void setup() {
  Serial.begin(9600);
  while (!Serial);

  buildInfo();

  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(frequency)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }

  Serial.println("LoRa Receiver @ " + String(frequency/1E6) + "MHz");

}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }

  blinkLED ();

  
}
