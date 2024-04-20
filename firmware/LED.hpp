// xiaolaba 

// hardware used: invisiblefun.com, SX1276 LoRaWAN chip, Mini LoRa Development Board, PCB V2.0
// ref: https://www.facebook.com/invisiblefun/posts/pfbid0HpNUCBseRqBnQ8sZ2f5QberJxqALRAVBevNrfMchXY3tJSkpYHzkCUTYtWmqsRGNl 
//      In case you need circuit diagram / schematic, written request is available at xiao_laba_cn@yahoo.com
//      or load the simplified diagram by webpage, https://github.com/xiaolaba/AVR_IFS_LoRa_simpleGateway_testing
//      2022-02-05, xiaolaba
//
// usage, 
// #include "LED.hpp"  // LED blink every second, and for SX1276 pin assignment, and hex stamp of build


/*
- https://www.facebook.com/invisiblefun/posts/2951385615082036
- invisiblefun.com Mini LoRa Development Board
- Samtech SX1276 for 915Mhz and 923Mhz application, LoRaWan chip
- MCU ATMEGA328PB
- AM1805 RTC (I2C interface, PC5/SCL0, PC4/SDA0)
- Extra Interrupt pin for further development, PC0 / PC1 / PC3 pin used
 */

// install this library, a must
// https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json
// testing done, sucess, 2022-06-20

// specific for this PCB & m328
/*
PC3 ADC3 (ADC Input Channel 3)
PCINT11 (Pin Change Interrupt 11)

PC2 ADC2 (ADC Input Channel 2)
PCINT10 (Pin Change Interrupt 10)

PC1 SCK1 (SPI1 Master Clock output)
ADC1 (ADC Input Channel 1)
PCINT9 (Pin Change Interrupt 9)

PC0 MISO1
ADC0 (ADC Input Channel 0)
PCINT8 (Pin Change Interrupt 8)
*/


//xiaolaba, 2022-06-17
//#define F_CPU 1000000L
// uses MiniCore 328PB, no bootloader, 1MHz internal RC 

// SX1276 and m328 pin route
const int csPin = PIN_PB2;          // PIN_PB2, PB2, LoRa radio chip select
const int resetPin = PIN_PC2;       // PC2, LoRa radio reset
const int irqPin = PIN_PD2;          // PD2, change for your board; must be a hardware interrupt pin

// PCB V2.0, on board route
const int reedSwitchPin =  PIN_PB0;// the number of the reedSwitch pin
const int ledPin = PIN_PD5;         // on broad LED testing

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int reedSwitchState = LOW;      // ledState used to set the LED


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // 1 second interval at which to blink (milliseconds)

void blinkLED () {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);	// toggle port pin, LED will be on or off
	
	Serial.println("hi xiaolaba, this LED blinking/toggling per second");
  }   
}




void buildInfo(){
  // Combined string in RAM
  Serial.println( "RAM string, Compiled by xiaolaba: " __DATE__ ", " __TIME__ ", " __VERSION__);
  
  // The string in Flash
  Serial.print( F("ROM string, Compiled by xiaolaba: "));
  Serial.print( F(__DATE__));
  Serial.print( F(", "));
  Serial.print( F(__TIME__));
  Serial.print( F(", "));
  Serial.println( F(__VERSION__));
}