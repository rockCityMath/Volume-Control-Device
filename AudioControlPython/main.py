import serial
import time
from enum import StrEnum
import os
import shutil
import threading
from pycaw.pycaw import AudioUtilities
import sys
import time
import config
import utils
from class_definitions import ControllerData

# MC = Microcontroller
mc_serial = serial.Serial(port='COM3', baudrate=9600, timeout=.1)

# Track the current state of pause (only applicable if sw1 is controlling it)
paused = False

while True:
    controller_data = utils.get_controller_data(mc_serial)

    if (controller_data == None):
        continue

    # Sometimes ESP sends weird high values when it first starts up, allowing those crashes the program
    if(controller_data.rv1 > 100 or controller_data.rv2 > 100):
        continue

    # Pycaw represents volume level from 0 to 1 (EG: 0.5 being 50% of max volume)
    # Need to map to that from the value the ESP sends (0 to 100), called min-max normalization
    MIN_MAX_NORMALIZATION__MAX = 100

    # Iterate through all audio sessions, update values of each to match hardware controller
    sessions = AudioUtilities.GetAllSessions()
    for idx, session in enumerate(sessions):
        if (session.Process is not None):

            if(session.Process.name() == config.section_1_process_name):
                session.SimpleAudioVolume.SetMasterVolume(controller_data.rv1 / MIN_MAX_NORMALIZATION__MAX, None)
                if config.SW_1_CONTROLS_PAUSE_PLAY and (controller_data.sw1 != paused):
                    utils.pause_play_media()
                    paused = not paused
                elif not config.SW_1_CONTROLS_PAUSE_PLAY:
                    session.SimpleAudioVolume.SetMute(controller_data.sw1, None)

            elif(session.Process.name() == config.section_2_process_name):
                session.SimpleAudioVolume.SetMasterVolume(controller_data.rv2 / MIN_MAX_NORMALIZATION__MAX, None)
                session.SimpleAudioVolume.SetMute(controller_data.sw2, None)

            elif(session.Process.name() == config.section_3_process_name):
                session.SimpleAudioVolume.SetMasterVolume(controller_data.rv3 / MIN_MAX_NORMALIZATION__MAX, None)
                session.SimpleAudioVolume.SetMute(controller_data.sw3, None)

            elif(session.Process.name() == config.section_4_process_name):
                session.SimpleAudioVolume.SetMasterVolume(controller_data.rv4 / MIN_MAX_NORMALIZATION__MAX, None)
                session.SimpleAudioVolume.SetMute(controller_data.sw4, None)

            elif(session.Process.name() == config.section_5_process_name):
                session.SimpleAudioVolume.SetMasterVolume(controller_data.rv5 / MIN_MAX_NORMALIZATION__MAX, None)
                session.SimpleAudioVolume.SetMute(controller_data.sw5, None)

    # Sleep before reading again
    time.sleep(config.sleep_between_reads_sec)

