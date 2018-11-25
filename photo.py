import os
import serial
import time
arduino = serial.Serial('/dev/ttyACM0', 9600, timeout = 1)
time.sleep(1)
while True:
    # time.sleep(0.5)
    data = arduino.read()
    print data
    if len(data) > 0:
        # print data
        print "PHOTO"
        os.system('fswebcam -r 1280x1080 image.jpg')
        os.system('scp image.jpg felix@eduroam-5-212.epfl.ch:~/Documents/programming/WildFollower/images')
        os.system('rm image.jpg')

