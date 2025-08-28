#pragma once
#include <Arduino.h>
#include <cstdint>

// 10 byte data packet to be sent over serial
struct DataPacket
{
  uint8_t rv1; // uint8_t = 1 byte
  uint8_t rv2;
  uint8_t rv3;
  uint8_t rv4;
  uint8_t rv5;
  bool sw1; // bool = 1 byte
  bool sw2;
  bool sw3;
  bool sw4;
  bool sw5;
};

// Mux pins
static const int s0 = 21;
static const int s1 = 25;
static const int s2 = 14;
static const int s3 = 27;

static const int sig = 34;         // Analog pin
static const int sig_pullup = 32; // Digital pin

// Mux channels
static const int rv1channel = 13;
static const int sw1channel = 10;

static const int rv2channel = 14;
static const int sw2channel = 11;

static const int rv3channel = 15;
static const int sw3channel = 12;

static const int rv4channel = 1;
static const int sw4channel = 3;

static const int rv5channel = 2;
static const int sw5channel = 4;

// Shift register pins
static const int srclk = 26;
static const int rclk = 19; // these 2 are switch in the schematic I think, this is correct tho
static const int ser = 18;

// Other pins
static const int systemLED = 2;
