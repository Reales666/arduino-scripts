import serial
import time
import sys
import re

from config.constants import BAUDRATE

if len(sys.argv) == 2:
    arduino_port_input = str(sys.argv[1])

    try:
        arduino_port = re.search(r'^COM\d$', arduino_port_input).group()
    except Exception as e:
        raise Exception("Format of <arduino_port> parameter incorrect. E.g: COM1")

else:
    raise Exception("Number of parameters incorrect. Usage: python ets2_telemetry_reader.py <arduino_port> (e.g: COM4)")

arduino = serial.Serial(port=arduino_port, baudrate=BAUDRATE, timeout=.1)


def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data


while True:
    num = input("Enter a number: ")  # Taking input from user
    value = write_read(num)
    print(value)  # printing the value
