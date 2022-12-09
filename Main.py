import numpy as np
import pyautogui
import colorsys
import asyncio
import serial
import math
import time


def getAvgScreenHSV():
    img = pyautogui.screenshot()

    # Convert screenshot to array
    data = np.asarray(img)

    # Compute the average
    rgb = (round(np.mean(data[:,:,0])), 
           round(np.mean(data[:,:,1])), 
           round(np.mean(data[:,:,2])))

    # Convert the RGB to HSV
    hsv = colorsys.rgb_to_hsv(rgb[0] / 255, 
                              rgb[1] / 255, 
                              rgb[2] / 255)

    return hsv


async def sendAvgScrHueToArduino(arduino, serialDelay=1, debug=False):
    while True:
        hsv = getAvgScreenHSV()
        hue = hsv[0]
        
        SerialMsg = str(f"h{str(math.floor(hue * 255))}\n")

        if debug:
            print(f"Normal Hue: {str(math.floor(hue * 360))}")
            print(f"Serial Msg: {SerialMsg}")

        # Tx the new HSV values to the arduino
        arduino.write(str.encode(SerialMsg))

        await asyncio.sleep(serialDelay)


def main():
    # Establish the serial connection
    arduino = serial.Serial(port="/dev/cu.usbserial-110", timeout=0)
    time.sleep(0.1)
    # arduino = None

    # setMatrixColorToHueRainbow(arduino)
    asyncio.run(sendAvgScrHueToArduino(arduino=arduino,serialDelay=1,debug=True))


if __name__ == "__main__":
    main()
