# If true, prints each potentiometer and switch value to console
DEBUG_MODE = False

# If true, the first switch will toggle pause/play when it changes position
SW_1_CONTROLS_PAUSE_PLAY = False

section_1_process_name = "chrome.exe"
section_2_process_name = "msedge.exe"
section_3_process_name = None
section_4_process_name = None
section_5_process_name = None

### SHOULDNT NEED TO CHANGE ANYTHING BELOW THIS LINE

# Seconds to sleep between reading from the MC (so that this program doesnt monopolize the thread)
sleep_between_reads_sec = 0.01

# Endianness of byte array read from MC
endianness = "big"
