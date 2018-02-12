#!/usr/bin/python
import socket
from PIL import Image,ImageGrab
import re
import time

i=0
location='./'
while True:
	print 'begain cap'
	im=ImageGrab.grab()
	name=str(i)+'.jpg'
	im.save(location+name)
	print time.ctime()+'screen'+i+'save'
	time.sleep(3)
	i=i+1
	if i>10:
		break
		

'''
HOST='123.57.134.176'
PORT= 12456
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((HOST,PORT))       
while 1:
       data=s.recv(1024)     
       print data         
       cmd=raw_input("Please input cmd:")       
       s.sendall(cmd)      
s.close()   
'''

'''
#!/usr/bin/python
import socket

#host = socket.gethostname()
host = '192.168.0.88'
#print host
port = 5000
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect((host,port))

print s.recv(1024)
s.close()
'''
