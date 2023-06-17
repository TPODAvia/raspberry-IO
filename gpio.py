import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(14, GPIO.IN)
GPIO.setup(4, GPIO.IN)

try:
    while True:
        value_14 = GPIO.input(14)
        value_4 = GPIO.input(4)
        print("GPIO 14 Value: ", value_14)
        print("GPIO 4 Value: ", value_4)
        time.sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()