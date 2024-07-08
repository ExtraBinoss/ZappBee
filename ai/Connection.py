##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## connection.py
##

import os
import sys
import socket
import select
import signal
import subprocess

class Connection:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.queen = False
        self.socket = None
        self.params = None

    def connect(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.socket.connect((self.host, self.port))
        except Exception as e:
            print("Error connecting to server: ", e)
            sys.exit(1)

    def disconnect(self):
        try:
            self.socket.close()
            self.socket = None
        except Exception as e:
            print("Error disconnecting from server: ", e)
    
    def clean_exit(signum, frame):
        os._exit(0)
    
    signal.signal(signal.SIGTERM, clean_exit)

    def send(self, data):
        try:
            if type(data) == str:
                data = data.encode('utf-8')
            self.socket.sendall(data)
        except Exception as e:
            print("Error sending data to server: ", e)
            sys.exit(84)

    def receive(self):
        try:
            data = ""
            while True:
                data += self.socket.recv(1024).decode('utf-8')
                if data == "":
                    print("Server disconnected")
                    try:
                        os.killpg(os.getpgrp(), signal.SIGTERM)
                    except Exception as e:
                        print("AI exited properly")
                        os._exit(0)
                # if "Current" in data:
                #     print("Received: ", data)
                if data.endswith("\n"):
                    break
        except Exception as e:
            print("Error receiving data from server: ", e)
            sys.exit(84)
        return data

    def readable(self):
        try:
            read, write, error = select.select([self.socket], [], [], 0)
            if read:
                return True
            return False
        except Exception as e:
            print("Error checking socket readability: ", e)
            exit(84)

    def waitForData(self):
        messages = []
        result = ""
        while True:
            data = self.receive()
            if data.count("\n") > 1:
                temp = data.split("\n")
                for entry in temp:
                    if "message" in entry:
                        messages.append(entry)
                    else:
                        result += entry
                data = result
            if "dead\n" in data:
                print("WaitForData Died")
                script_dir = os.path.dirname(__file__)
                main_script_path = os.path.join(script_dir, 'Main.py')
                subprocess.Popen([sys.executable, main_script_path, '-p', str(self.params.port), '-n', self.params.name, '-h', self.params.host])
                sys.exit(0)
            if "message" in data:
                messages.append(data)
                continue
            break
        return messages, data
    
    def setParams(self, params):
        self.params = params
