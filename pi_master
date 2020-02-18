#!/usr/bin/python3
from spectrometer import *
from module_with_functions import *
import re

# picamera settings
from picamera import PiCamera
from time import sleep
camera = PiCamera()

# TimeStamp for file name
import datetime
import time
date = datetime.datetime.now().strftime("%m_%d_%Y_%H_%M_%S")

# image Settings
camera.rotation = 180
camera.resolution = (2592, 1944)
camera.framerate = 15
camera.brightness = 70
camera.iso = 400

# read from Arduino
input2 = ser.read()
print ("Read input " + input2.decode("utf-8") + " from Arduino")

# run command from Arduino
trigger = '1'
ser.write(trigger.encode("ascii"))
time.sleep(0.5)
input3 = ser.readlines()
input3 = str(input3)
input3 = re.sub('[^A-Za-z0-9]+', '', input3)
print (input3)

if input3 == "b2rn":

   trigger = '3'  # moving box to sensing position
   ser.write(trigger.encode("ascii"))
   time.sleep(8)

   trigger = '4'  # turn on white LEDs
   ser.write(trigger.encode("ascii"))
   time.sleep(5)
   camera.capture("/home/pi/camera/testcode/"+ date + ".jpg")   # take picture while white LEDs are on
   time.sleep(2)

   trigger = '5'  # turn off white LEDs
   ser.write(trigger.encode("ascii"))
   time.sleep(0.5)

   trigger = '6'  # spectrometer on
   if (ser.open):
       ser.write(trigger.encode("ascii"))
       time.sleep(5)
       bin_location = spectrometer_reading()
       print (bin_location)
