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
camera.framerate=32
rawCapture=PiRGBArray(camera,size=(640,480))
time.sleep(0.1)

with open('/home/pi/Desktop/order') as f:
    order1=f.read().splitlines()
size=len(order1)
listY=[0]*size
listI=[0]
ProductFound=0
TotalOrder=size
ItemsLeft=TotalOrder-ProductFound
print('Total items :',TotalOrder)
print('Product Found : ',ProductFound)
print('Items Left : ',ItemsLeft)


for image in camera.capture_continuous(rawCapture,format="bgr",use_video_port=True):
    frame=image.array
    barc=decode(frame)
    font=cv2.FONT_HERSHEY_SIMPLEX
    datas, addr=sock.recvfrom(1024)
    datas=int(datas)

    if datas == 2:
        port.write(b”12”)//turn left
    if listI[0]==0:
        port.write(b'0')
        listI[0]=1
        print(listI)

    for barcode in barc:
        BarCdata=barcode.data.decode('utf-8')
        #print(BarCdata)
        x,y,w,h=barcode.rect
        #print(listY)

        for i in range(size):
            if ((BarCdata in order1[i]) and (listY[i]== 0) and 300<x<400):
            print('..............................................................................')
            print('correct order')
            print('..............................................................................')
            print('..............................................................................')
            listY[i]=1
            ProductFound+=1
            TotalOrder=size
            ItemsLeft=TotalOrder-ProductFound
            print('Total items :',TotalOrder)
            print('Product Found : ',ProductFound)
            print('Items Left : ',ItemsLeft)

            if (y<240 and 300<x<400):
                print('BarCode up')
                port.write(b'2')
                print('..............................................................................')
            elif(y>240 and 300<x<400):
                print('Barcode Down')
                port.write(b'1')
                print(x)
                print(y)
                print('..............................................................................')
            else:
                print('out...........................................................................')

        if BarCdata in order1:
            #print('right order(bar code)')
             scanning='right order'
             color=(0,255,0)
        else:
            #print('wrong order(bar code)')
             scanning='wrong order'
             color=(0,0,255)
        
        cv2.rectangle(frame,(x,y),(x+w,y+h),color,4)
        cv2.putText(frame,scanning,(x,y-10),font,0.5,color,2)
        cv2.circle(frame,(x,y),5,(0,0,255),-1)

    cv2.line(frame,(0,240),(640,240),(255,0,0),2)
    cv2.line(frame,(300,0),(300,480),(0,0,255),2)
    cv2.line(frame,(400,0),(400,480),(0,0,255),2)
    cv2.imshow('laptop cam',frame)
    cv2.moveWindow('laptop cam',0,0)
 
    key=cv2.waitKey(1) & 0xFF
    rawCapture.truncate(0)
    if key == ord('q'):
        break
cv2.destroyAllWindows()




  

