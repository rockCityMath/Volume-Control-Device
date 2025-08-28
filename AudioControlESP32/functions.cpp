#include "functions.h"

void writeToShiftRegister(uint8_t dataByte) {
  digitalWrite(rclk, LOW);                   // Pull RCLK low so we can write new bits into shift register
  shiftOut(ser, srclk, MSBFIRST, dataByte);  // Write new bits into shift register
  digitalWrite(rclk, HIGH);                  // Pull RCLK high to update the storage register with shift register bits
}

int readMux(int channel, bool analog) {

  // MUX only has 15 channels, channel arg shouldnt be outside of those
  if (channel < 0 || channel > 15) {
    return -1;
  }

  // Update MUX control pins so that when we read, we're reading from the channel that's specified
  digitalWrite(s0, bitRead(channel, 0)); // LSB
  digitalWrite(s1, bitRead(channel, 1));
  digitalWrite(s2, bitRead(channel, 2));
  digitalWrite(s3, bitRead(channel, 3)); // MSB
  delay(5);
  
  return analog ? analogRead(sig) : digitalRead(sig_pullup) ;
}

uint8_t mapRV(int value) {
  // Will read value between 4095 and 0 from the potentiometer, map that into 100 to 0
  return map(value, 0, 4095, 0, 100);
}

void performLEDScrollingPattern() {
  int delayMS = 150;
  writeToShiftRegister(0b00000000);
  delay(delayMS);
  writeToShiftRegister(0b10000000);
  delay(delayMS);
  writeToShiftRegister(0b01000000);
  delay(delayMS);
  writeToShiftRegister(0b00100000);
  delay(delayMS);
  writeToShiftRegister(0b00010000);
  delay(delayMS);
  writeToShiftRegister(0b00000001);
  delay(delayMS);
  writeToShiftRegister(0b00010000);
  delay(delayMS);
  writeToShiftRegister(0b00100000);
  delay(delayMS);
  writeToShiftRegister(0b01000000);
  delay(delayMS);
  writeToShiftRegister(0b10000000);
  delay(delayMS);
  writeToShiftRegister(0b00000000);
  delay(delayMS);
}

DataPacket getData() {
  DataPacket p;
  p.rv1 = mapRV(readMux(rv1channel, true));
  p.rv2 = mapRV(readMux(rv2channel, true));
  p.rv3 = mapRV(readMux(rv3channel, true));
  p.rv4 = mapRV(readMux(rv4channel, true));
  p.rv5 = mapRV(readMux(rv5channel, true));
  p.sw1 = (readMux(sw1channel) ^ 1);
  p.sw2 = (readMux(sw2channel) ^ 1);
  p.sw3 = (readMux(sw3channel) ^ 1);
  p.sw4 = (readMux(sw4channel) ^ 1);
  p.sw5 = (readMux(sw5channel) ^ 1);
  return p;
}

bool isUpdatedDataPacket(DataPacket previousPacket, DataPacket currentPacket) {
  DataPacket p = previousPacket;
  DataPacket c = currentPacket;
  return (
    abs(p.rv1 - c.rv1) > 1 ||
    p.sw1 != c.sw1 ||
    abs(p.rv2 - c.rv2) > 1 ||
    p.sw2 != c.sw2 ||
    abs(p.rv3 - c.rv3) > 1 ||
    p.sw3 != c.sw3 ||
    abs(p.rv4 - c.rv4) > 1 ||
    p.sw4 != c.sw4 ||
    abs(p.rv5 - c.rv5) > 1 ||
    p.sw5 != c.sw5
  );
}

void printPacketValuesToSerial (DataPacket packet) {
  Serial.println("------- VALUES ---------");
  Serial.println("RV1: " + String(packet.rv1));
  Serial.println("SW1: " + String(packet.sw1));

  Serial.println("RV2: " + String(packet.rv2));
  Serial.println("SW2: " + String(packet.sw2));

  Serial.println("RV3: " + String(packet.rv3));
  Serial.println("SW3: " + String(packet.sw3));

  Serial.println("RV4: " + String(packet.rv4));
  Serial.println("SW4: " + String(packet.sw4));
  
  Serial.println("RV5: " + String(packet.rv5));
  Serial.println("SW5: " + String(packet.sw5));
  Serial.println("------------------------");
}