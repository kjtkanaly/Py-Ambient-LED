import numpy as np
import pyautogui
import colorsys
import serial
import math
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
    sat = 255
    val = 255
    stepSize = 5
    serialDelay = 0.1

    hue = np.linspace(start=1,stop=360,num=360)

    # Set the initial color
    currentColorHSV = (0 / 360,
                       sat / 255,
                       val / 255)
    currentColorRGB = colorsys.hsv_to_rgb(currentColorHSV[0],
                                          currentColorHSV[1],
                                          currentColorHSV[2])

    msg = str("c" + str(currentColorRGB[0] * 255) + 
              "," + str(currentColorRGB[1] * 255) + 
              "," + str(currentColorRGB[2] * 255) + "\n")
    print(msg)

    arduino.write(str.encode(msg))
    time.sleep(serialDelay)

    # Cycle through the rainbow
    while True:
        for i in hue:
            newColorHSV = (i / 360,
                           sat / 255,
                           val / 255)
            newColorRGB = colorsys.hsv_to_rgb(newColorHSV[0], 
                                              newColorHSV[1],
                                              newColorHSV[2])

            print(newColorRGB)

            colorSteps = np.linspace(start=currentColorRGB, stop=newColorRGB, num=stepSize)

            for colorStep in colorSteps:
                
                colorStep = round(colorStep)

                msg = str("c" + str(colorStep[0] * 255) + 
                          "," + str(colorStep[1] * 255) + 
                          "," + str(colorStep[2] * 255) + "\n")
                print(msg)

                # Tx the new HSV values to the arduino
                arduino.write(str.encode(msg))

                # Wait for 100 milliseconds
                time.sleep(serialDelay)

            currentColorRGB = newColorRGB

def LerpBetweenColors():
    sat = 1
    val = 1
    stepSize = 5
    serialDelay = 0.1

    hue = np.linspace(start=1,stop=360,num=360)

    # Set the initial color
    currentColorHSV = (0,
                       sat,
                       val)
    currentColorRGB = colorsys.hsv_to_rgb(currentColorHSV[0],
                                          currentColorHSV[1],
                                          currentColorHSV[2])

    currentColorRGB = tuple([255*x for x in currentColorRGB])

    # Cycle through the rainbow
    for i in hue:
    # for i in range(1,2):
        newColorHSV = (i / 360,
                        sat,
                        val)
        newColorRGB = colorsys.hsv_to_rgb(newColorHSV[0], 
                                          newColorHSV[1],
                                          newColorHSV[2])
        newColorRGB = tuple([math.floor(255*x) for x in newColorRGB])

        steps = np.linspace(currentColorRGB, newColorRGB, 5)
        for step in steps:
            ColorStep = tuple([math.floor(x) for x in step])
            print(ColorStep)

        currentColorRGB = newColorRGB

def main():
    # Establish the serial connection
    #arduino = serial.Serial(port="/dev/cu.usbserial-110", timeout=0)
    # time.sleep(1)

    LerpBetweenColors()
    # setMatrixColorToHueRainbow(arduino)
    # setMatrixColorToScreenAverage(arduino)


if __name__ == "__main__":
    main()
