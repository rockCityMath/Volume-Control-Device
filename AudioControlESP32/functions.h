#pragma once
#include <Arduino.h>
#include <cstdint>
#include <cstdlib>
#include "definitions.h"

// Write bits to shift register
void writeToShiftRegister(uint8_t dataByte);

// Read from given mux channel using appropriate signal pin
int readMux(int channel, bool analog = false);

// Map RV 0 to 100 range
uint8_t mapRV(int value);

// Display the side to side LED pattern (blocking)
void performLEDScrollingPattern();

// Get all switch and potentiometer values, appropriately mapped
DataPacket getData();

// Determine if the 2 packets are different 
bool isUpdatedDataPacket(DataPacket previousPacket, DataPacket currentPacket);

// Print human-readable list of all the data packet values to serial
void printPacketValuesToSerial (DataPacket packet);