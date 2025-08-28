# Volume-Control-Device
Code for a custom-made volume control device.  

[Article Discussing this Device](https://medium.com/@rockcitymath/building-a-volume-control-device-025434faa18b)


**ESP32 Code** - Reads switch and potentiometer positions via multiplexer IC, then sends a packet of data with all positions over serial.  

**Python Code** - Awaits packets from serial then updates configured programs' volume/mute. 


![IMG_4273 (3)](https://github.com/user-attachments/assets/70d3306a-b5d9-4d4a-a93e-2e99d9bd6e12)
