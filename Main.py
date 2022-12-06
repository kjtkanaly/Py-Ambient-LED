import numpy as np
import pyautogui
import colorsys
import serial
import time
import sys


def getAverageColorOnScreenHSV():
    # Take screenshot of screen
    img = pyautogui.screenshot()

    # Convert screenshot to array
    data = np.asarray(img)

    # Find the average color
    rgb = (round(np.mean(data[:,:,0])), 
           round(np.mean(data[:,:,1])), 
           round(np.mean(data[:,:,2])))

    # Convert the RGB to HSV
    hsv = colorsys.rgb_to_hsv(rgb[0] / 255, 
                              rgb[1] / 255, 
                              rgb[2] / 255)

    return hsv


def setMatrixColorToScreenAverage(arduino):
    while True:
        hsv = getAverageColorOnScreenHSV()

        msg = str("c" + str(round(hsv[0] * 255)) + 
                  "," + str(round(hsv[1] * 255)) + 
                  "," + str(round(hsv[2] * 255)) + "\n")
        print(msg)

        # Tx the new HSV values to the arduino
        arduino.write(str.encode(msg))
        time.sleep(2)


def setMatrixColorToHueRainbow(arduino):
    sat = 250
    val = 180
    hue = np.zeros((1,255))

    while True:
        for i in range(1, hue.size + 1):
            msg = str("c" + str(i) + 
                      "," + str(sat) + 
                      "," + str(val) + "\n")
            print(msg)

            # Tx the new HSV values to the arduino
            arduino.write(str.encode(msg))

            # Wait for 100 milliseconds
            time.sleep(0.1)


def main():
    # Establish the serial connection
    arduino = serial.Serial(port="/dev/cu.usbserial-110", timeout=0)
    time.sleep(1)

    #setMatrixColorToHueRainbow(arduino)
    setMatrixColorToScreenAverage(arduino)


if __name__ == "__main__":
    main()
