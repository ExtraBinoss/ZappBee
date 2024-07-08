##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## Actions.py
##

from Connection import Connection
import sys
import time

class Actions:
    def __init__(self, connection, logfile):
        self.connection = connection
        self.logfile = logfile

    def writeLog(self, data):
        self.logfile.write(time.strftime("%H:%M:%S", time.localtime()))
        self.logfile.write(" : ")
        self.logfile.write(data)
        self.logfile.write("\n")

    def left(self):
        self.writeLog("Sending Left")
        self.connection.send("Left\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response
    
    def right(self):
        self.writeLog("Sending Right")
        self.connection.send("Right\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response
        
    def forward(self):
        self.writeLog("Sending Forward")
        self.connection.send("Forward\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response
    
    def take(self, item):
        self.writeLog(f"Sending Take {item}")
        self.connection.send(f"Take {item}\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response
    
    def set(self, item):
        self.writeLog(f"Sending Set {item}")
        self.connection.send(f"Set {item}\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response
    
    def inventory(self):
        self.writeLog("Sending Inventory")
        self.connection.send("Inventory\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response
    
    def look(self):
        self.writeLog("Sending Look")
        self.connection.send("Look\n")
        messages, data = self.connection.waitForData()
        self.writeLog("Response: " + data)
        data = data.replace("\n", "")
        data = data.split(",")
        for i in range(len(data)):
            data[i] = data[i].replace("[", "")
            data[i] = data[i].replace("]", "")
            data[i] = data[i].replace(" ", "")
            data[i] = data[i].replace("player", "player ")
            data[i] = data[i].replace("food", "food ")
            data[i] = data[i].replace("linemate", "linemate ")
            data[i] = data[i].replace("deraumere", "deraumere ")
            data[i] = data[i].replace("sibur", "sibur ")
            data[i] = data[i].replace("mendiane", "mendiane ")
            data[i] = data[i].replace("phiras", "phiras ")
            data[i] = data[i].replace("thystame", "thystame ")
            data[i] = data[i].rstrip()
            data[i] = data[i].split(" ")
        self.writeLog("Formated Data: " + str(data))
        return messages, data

    def connect_nbr(self):
        self.writeLog("Sending Connect_nbr")
        self.connection.send("Connect_nbr\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response

    def incantation(self):
        self.writeLog("Sending Incantation")
        self.connection.send("Incantation\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response

    def broadcast(self, message):
        self.writeLog(f"Sending Broadcast {message}")
        self.connection.send(f"Broadcast {message}\n")
        # print(f"Broadcast {message}")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response

    def fork(self):
        self.writeLog("Sending Fork")
        self.connection.send("Fork\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response
    
    def eject(self):
        self.writeLog("Sending Eject")
        self.connection.send("Eject\n")
        response = self.connection.waitForData()
        self.writeLog("Response: " + response[1])
        return response
