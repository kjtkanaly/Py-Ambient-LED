import serial
import time
import sys

arduino = serial.Serial(port='/dev/cu.usbserial-110', timeout=0)
time.sleep(2)

code = ""

print("Enter '1' to turn 'on' the LED and '0' to turn LED 'off'")

while True:

    var = str(input())

    if (var == '1'):
        arduino.write(str.encode('1'))

        time.sleep(0.1)

        while arduino.in_waiting:
            code += arduino.readline().decode('utf-8')

        print(code)
        code = ""

    elif (var == '0'):
        arduino.write(str.encode('0'))
        
        time.sleep(0.1)

        while arduino.in_waiting:
            code += arduino.readline().decode('utf-8')

        print(code)
        code = ""

        

    elif (var == 'end'):
        sys.exit()