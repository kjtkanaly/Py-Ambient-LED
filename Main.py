import numpy as np
import pyautogui
import colorsys
import serial
import time
import sys

# Establish the serial connection
arduino = serial.Serial(port='/dev/cu.usbserial-110', timeout=0)
time.sleep(1)

# Take screenshot of screen
img = pyautogui.screenshot()

# Convert screenshot to array
data = np.asarray(img)

# Find the average color
rgb     = (round(np.mean(data[:,:,0])), round(np.mean(data[:,:,1])), round(np.mean(data[:,:,2])))
rgb     = (0, 250, 0)

# Convert the RGB to HSV
hsv = colorsys.rgb_to_hsv(rgb[0] / 255, rgb[1] / 255, rgb[2] / 255)

print("HSV: " , hsv[0] * 360, hsv[1] * 255, hsv[2] * 255)

# Send the HSV values to the arduino
msg = str("c" + round(hsv[0] * 360)) + " " + str(round(hsv[1] * 255)) + " " + str(round(hsv[2] * 255))
print(msg)
# arduino.write(str(hsv[0] * 360).encode)
#time.sleep(0.1)
