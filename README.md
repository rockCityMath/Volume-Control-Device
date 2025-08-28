# Volume-Control-Device
Code for a custom-made volume control device.

ESP32 Code - Reads switch and potentiometer positions via multiplexer IC, then sends a packet of data with all positions over serial.
Python Code - Awaits packets from serial then updates configured programs' volume/mute. 
