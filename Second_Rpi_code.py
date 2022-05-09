from picamera.array import PiRGBArray
from picamera import PiCamera
import time
import cv2
from pyzbar.pyzbar import decode
import numpy as np
import serial 
import socket 
camera=PiCamera()
camera.resolution=(640,480)
port=serial.Serial('/dev/ttyACM0',9600)
UDP_IP=”192.168.0.4”
UDP_PORT=5005
sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
sock.bind((UDP_IP,UDP_PORT))
turnleft=”2”
camera.framerate=32
rawCapture=PiRGBArray(camera,size=(640,480))
time.sleep(0.1)
with open('/home/pi/Desktop/section') as f:
    section=f.read().splitlines()

size=len(section)
listY=[0]*size
listI=[0]


for image in camera.capture_continuous(rawCapture,format="bgr",use_video_port=True):
    frame=image.array
    barc=decode(frame)
    font=cv2.FONT_HERSHEY_SIMPLE

    for barcode in barc:
        BarCdata=barcode.data.decode('utf-8')
        x,y,w,h=barcode.rect
        for i in range(size):
            if ((BarCdata in order1[i]) and (listY[i]== 0) ):
            print('..........................................................')
            listY[i]=1
            sock.sendto(turnleft,(UDP_IP,UDP_PORT))

        if BarCdata in order1:
            scanning='right section'
            color=(0,255,0)
        else:
            scanning='wrong section'
            color=(0,0,255)

    cv2.rectangle(frame,(x,y),(x+w,y+h),color,4)
    cv2.putText(frame,scanning,(x,y-10),font,0.5,color,2)
    cv2.circle(frame,(x,y),5,(0,0,255),-1)
    cv2.imshow('laptop cam',frame)
    cv2.moveWindow('laptop cam',0,0)
 
    key=cv2.waitKey(1) & 0xFF
    rawCapture.truncate(0)
    if key == ord('q'):
        break


cv2.destroyAllWindows()

