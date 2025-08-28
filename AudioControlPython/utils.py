import win32api
import struct
import config
import ctypes
import serial
from class_definitions import ControllerData

def get_controller_data(mc_serial):

    # If there arent any bytes in the recieve buffer, return nothing
    if (mc_serial.inWaiting() < 1):
        return None

    # Initialize array for storing the 10 bytes expected from the MC
    barr = bytearray(10)

    # Read serial data into the byte array
    size = mc_serial.readinto(barr)

    # > =  byte order         - big endian
    # 10 = size of byte array - 10
    # c =  python type        - char (1 byte)
    s = struct.unpack('>10c', barr)

    # Convert bytes from byte array into appropriate python types
    # MC sends 1 byte per value (uint8_t = 1 byte, bool = 1 byte (in c++/ESP))
    rv1 = int.from_bytes(s[0], config.endianness)
    sw1 = bool.from_bytes(s[5], config.endianness)
    rv2 = int.from_bytes(s[1], config.endianness)
    sw2 = bool.from_bytes(s[6], config.endianness)
    rv3 = int.from_bytes(s[2], config.endianness)
    sw3 = bool.from_bytes(s[7], config.endianness)
    rv4 = int.from_bytes(s[3], config.endianness)
    sw4 = bool.from_bytes(s[8], config.endianness)
    rv5 = int.from_bytes(s[4], config.endianness)
    sw5 = bool.from_bytes(s[9], config.endianness)

    if config.DEBUG_MODE:
        print("--------VALUES----------")
        print("RV1: ", rv1)
        print("SW1: ", sw1)
        print("")
        print("RV2: ", rv2)
        print("SW2: ", sw2)
        print("")
        print("RV3: ", rv3)
        print("SW3: ", sw3)
        print("")
        print("RV4: ", rv4)
        print("SW4: ", sw4)
        print("")
        print("RV5: ", rv5)
        print("SW5: ", sw5)
        print("")
        print("------------------------")

    return ControllerData(rv1, sw1, rv2, sw2, rv3, sw3, rv4, sw4, rv5, sw5)

# Send a pause/play keypress to system
def pause_play_media():
    VK_MEDIA_PLAY_PAUSE = 0xB3  # The virtual-key code for the Media Play/Pause key
    win32api.keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0)
