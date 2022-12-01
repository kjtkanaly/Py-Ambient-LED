import cv2
import numpy as np
import pyautogui
import time
from PIL import Image
from matplotlib import pyplot

print("HEllo")

screenWidth, screenHeight = pyautogui.size()
print(str(screenWidth) + ", " + str(screenHeight))

# Move mouse pointer...neat
#pyautogui.moveTo(100,150)

img = pyautogui.screenshot()

# img.save("Test.jpg")

# Dispaly Screenshot
# pyplot.imshow(img)
# pyplot.show()

# Convert screenshot to array
data = np.asarray(img)

print(type(data))
print(data.shape)

print(round(np.mean(data[:,:,0])))
print(round(np.mean(data[:,:,1])))
print(round(np.mean(data[:,:,2])))



