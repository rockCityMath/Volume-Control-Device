#include "definitions.h"
#include "functions.h"

// If in debug mode, ESP will print human-readable values of every switch and potentiometer to serial
// Otherwise, it will write the DataPacket to serial
const bool DEBUG_MODE = false;

// Wait for "poll" to be received on serial before sending data
// If set false, ESP will send data anytime a potentiometer or switch changes values
const bool AWAIT_POLL = false;

String fromSerial = "";
DataPacket previousPacket = getData();

void setup() {

  // Setup with 9600 baud, python script is expected to use this
  Serial.begin(9600);

  // Setup all the pins
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sig_pullup, INPUT_PULLUP);
  pinMode(sig, INPUT);
  pinMode(rclk, OUTPUT);
  pinMode(srclk, OUTPUT);
  pinMode(ser, OUTPUT);
  pinMode(systemLED, OUTPUT);

  // Ensure all the shift register pins are LOW
  digitalWrite(ser, LOW);
  digitalWrite(srclk, LOW);
  digitalWrite(rclk, LOW);

  // Display scrolling pattern after startup is complete
  performLEDScrollingPattern();
}

void loop() {

  // Reflect switch states with LEDs
  uint8_t ledValues = 0;
  ledValues |= ((readMux(sw1channel) ^ 1) << 7);
  ledValues |= ((readMux(sw2channel) ^ 1) << 6);
  ledValues |= ((readMux(sw3channel) ^ 1) << 5);
  ledValues |= ((readMux(sw4channel) ^ 1) << 4);
  ledValues |= ((readMux(sw5channel) ^ 1) << 0);
  writeToShiftRegister(ledValues);

  // Send switch and potentiometer values (if appropriate based on config)
  if(Serial.available() > 0 || !AWAIT_POLL) {

    if (AWAIT_POLL) {
      fromSerial = Serial.readStringUntil('\n');
    }

    if(fromSerial == "poll" || !AWAIT_POLL) {

      DataPacket currentPacket = getData();
      bool isUpdatedPacket = isUpdatedDataPacket(previousPacket, currentPacket);

      // Dont send/print anything unless the packet has new values 
      if (!isUpdatedPacket) {
        return;
      }

      if(DEBUG_MODE) {
        printPacketValuesToSerial(currentPacket);
        previousPacket = currentPacket;
      }
      else {
        uint8_t* structPtr = (uint8_t*) &currentPacket;
        for (byte i = 0; i < sizeof(DataPacket); i++)  Serial.write(*structPtr++);
        previousPacket = currentPacket;
      }
    }
  }
}
