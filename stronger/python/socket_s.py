#!/usr/bin/python

import socket
import threading

host = '192.168.0.88'
port = 5000

class ThreadSocket(object):
        """
        
        """
        def __init__(self, host, port):
                self.host = host
                self.port = port
                self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                self.sock.bind((self.host, self.port))

        def listen(self):
                self.sock.listen(20)
                while True:
                        client, address = self.sock.accept()
                        client.settimeout(60)
                        threading.Thread(target=self.handleClientRequest, args=(
client, address)).start()

        def handleClientRequest(self, client, address):
			print 'client:'+str(address)+' connected'
			data = client.recv(1024)
			if 0 == cmp(data[:4], 'main'[:4]):
				resp = 'you are main'
				print resp
		  		client.send(resp)
				mainThread = 1

            while True:
            	try:
					if 1==mainThread
                                data = client.recv(1024)
                                if 0 == cmp(data[:4], 'main'[:4]):
                                        resp = 'you are main'
                                        print resp
                                        client.send(resp)
                                elif 0 == cmp(data[:4], 'main'[:4]):
                                        resp = 'you are normal'
                                        print resp
                                        client.send(resp)
                                else:
                                        raise error("Client has disconnected")
                        except:
                                client.close()
                                print 'client:'+str(address)+' break'
                                break

if __name__ == '__main__':
        server=ThreadSocket(host,port)
        server.listen()


