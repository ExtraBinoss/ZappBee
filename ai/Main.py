#!/usr/bin/env python3
##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## Main.py
##

import os
import sys
import time
import time
import random
import subprocess
from os import fork
from time import sleep
from getargs import Params
from Actions import Actions
from Inventory import Inventory
from Connection import Connection

#./zappy_ref-2-0-2/zappy_server -p 4040 -x 10 -y 10 -n GOGOLITOS TESTING -c 4 -f 100
#./zappy_ai -p 4040 -n GOGOLITOS -h localhost
#./zappy_gui -p 4040 -h localhost #in zappy_ref-2-0-2

class AI:
    def __init__(self, params):
        self.id = int(time.time())
        if not os.path.exists("ai_log"):
            os.makedirs("ai_log")
        if len(os.listdir("ai_log")) > 5:
            for file in os.listdir("ai_log"):
                try:
                    os.remove(f"ai_log/{file}")
                except FileNotFoundError:
                    print(f"File {file} not found and could not be removed.")
        self.logfile = open(f"ai_log/{params.name}_{self.id}{random.randint(0, 10000)}.log", "a+")
        self.params = params
        self.connection = Connection(params.host, params.port)
        self.items = ["player", "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]
        self.level = 1
        self.k = -1
        self.messages = []
        self.waitForElevation = False
        self.look_res = []
        self.inventory = Inventory()
        self.actions = Actions(self.connection, self.logfile)
        self.needs = [0, 0, 0, 0, 0, 0, 0, 0]
        self.elevation_ritual = [
            [1, 20, 1, 0, 0, 0, 0, 0],
            [2, 20, 1, 1, 1, 0, 0, 0],
            [2, 20, 2, 0, 1, 0, 2, 0],
            [4, 20, 1, 1, 2, 0, 1, 0],
            [4, 20, 1, 2, 1, 3, 0, 0],
            [6, 25, 1, 2, 3, 0, 1, 0],
            [6, 25, 2, 2, 2, 2, 2, 1]
        ]
        self.global_need = [0, 30, 9, 8, 10, 5, 6, 1]
        self.child_need = [0, 30, 0, 0, 0, 0, 0, 0]
        self.queen = False

    def writeLog(self, data):
        if self.waitForElevation:
            return
        self.logfile.write(time.strftime("%H:%M:%S", time.localtime()))
        self.logfile.write(" : ")
        self.logfile.write(data)
        self.logfile.write("\n")

    def connect_to_server(self):
        if self.connection is None:
            sys.exit(84)
        self.connection.connect()
        data = self.connection.receive()
        if data is None or data != "WELCOME\n":
            sys.exit(84)
        self.writeLog("Connection: " + data)
        self.connection.send(self.params.name + "\n")
        data = self.connection.receive()
        if data is None or data == "ko\n":
            sys.exit(84)
        if data.count("\n") == 2:
            data = data.split("\n")
            self.params.client_nb = int(data[0])
            self.params.x = int(data[1].split(" ")[0])
            self.params.y = int(data[1].split(" ")[1])
            self.writeLog(f"Client number: {self.params.client_nb}, X: {self.params.x}, Y: {self.params.y}")
        else:
            self.params.client_nb = int(data)
            data = self.connection.receive()
            if data is None or data == "ko\n":
                sys.exit(84)
            self.params.x = int(data.split(" ")[0])
            self.params.y = int(data.split(" ")[1])
            self.writeLog(f"Client number: {self.params.client_nb}, X: {self.params.x}, Y: {self.params.y}")

    def appendMessages(self, messages_data):
        messages = messages_data[0]
        data = messages_data[1]
        if len(messages) > 0:
            for message in messages:
                self.messages.append(message)
        return data

    def countItems(self, data):
        self.look_res = []
        for sublist in data:
            tmp = []
            tmp.append(sublist.count('player'))
            tmp.append(sublist.count('food'))
            tmp.append(sublist.count('linemate'))
            tmp.append(sublist.count('deraumere'))
            tmp.append(sublist.count('sibur'))
            tmp.append(sublist.count('mendiane'))
            tmp.append(sublist.count('phiras'))
            tmp.append(sublist.count('thystame'))
            self.look_res.append(tmp)
    
    def updateNeeds(self):
        if self.level == 1:
            self.needs = [ritual - inventory for ritual, inventory in zip(self.elevation_ritual[0], self.inventory.inventory)]
        elif self.queen:
            self.needs = [ritual - inventory for ritual, inventory in zip(self.global_need, self.inventory.inventory)]
        else:
            self.needs = [ritual - inventory for ritual, inventory in zip(self.child_need, self.inventory.inventory)]

    def findBestTile(self):
        best_tile = -1
        best_match = -1
        sum_needs = sum(self.needs[2:])

        if self.needs == [] or sum_needs == 0 and self.needs[1] < 3:
            return -1
        for index, tile in enumerate(self.look_res):
            if self.needs[1] >= 3:
                match = sum(need * item for need, item in zip(self.needs[1:], tile[1:]))
            else:
                match = sum(need * item for need, item in zip(self.needs[2:], tile[2:]))
            if match > best_match:
                best_match = match
                best_tile = index
        if best_match <= 0:
            self.appendMessages(self.actions.left())
            self.appendMessages(self.actions.forward())
            self.appendMessages(self.actions.forward())
            return -1
        return best_tile
    
    def go(self, best_tile):
        minTile = 1
        nAdd = 1
        middleTile = 0
        nMiddleToAdd = 2
        while (best_tile > minTile):
            self.appendMessages(self.actions.forward())
            nAdd += 2
            minTile += nAdd
            middleTile += nMiddleToAdd
            nMiddleToAdd += 2
        nForward = best_tile - middleTile
        if (nForward < 0):
            self.appendMessages(self.actions.left())
            nForward = -nForward
        elif (nForward > 0):
            self.appendMessages(self.actions.right())
        for _ in range(nForward):
            self.appendMessages(self.actions.forward())

    def takeItems(self, best_tile):
        for index, (need, count) in enumerate(zip(self.needs[1:], self.look_res[best_tile][1:])):
            if need > 0 and count > 0:
                for _ in range(min(need, count)):
                    self.appendMessages(self.actions.take(self.items[index + 1]))
    
    def checkElevation(self):
        if self.level == 1:
            for i in range(1, 8):
                if i == 1:
                    if self.inventory.inventory[i] < self.elevation_ritual[0][i] - 5:
                        return False
                    continue
                if self.inventory.inventory[i] < self.elevation_ritual[0][i]:
                    return False
            return True
        for i in range(1, 8):
            if i == 1:
                if self.inventory.inventory[i] < self.child_need[i] - 5:
                    return False
                continue
            if self.inventory.inventory[i] < self.global_need[i]:
                return False
        return True

    def elevate(self):
        for i in range(2, 8):
            for _ in range(self.elevation_ritual[self.level - 1][i]):
                self.appendMessages(self.actions.set(self.items[i]))
        data = self.appendMessages(self.actions.incantation())
        data = data.split("\n")
        for entry in data:
            if "ko" in entry:
                return 1
            if "Current level" in entry:
                self.level = int(entry.split(" ")[2])
                self.writeLog(f"Level update: {self.level}")
                if self.level == 8:
                    self.writeLog("I obtained ultimate wisdom, goodbye")
                    print("I obtained ultimate wisdom, goodbye")
                    sys.exit(0)
                return 0
        data = self.appendMessages(self.connection.waitForData())
        self.writeLog(f"Elevation result: {data}")
        if data == "ko\n":
            return 1
        try:
            self.level = int(data.split(" ")[2])
            self.writeLog(f"Level update: {self.level}")
            if self.level == 8:
                self.writeLog("I obtained ultimate wisdom, goodbye")
                print("I obtained ultimate wisdom, goodbye")
                sys.exit(0)
        except ValueError:
            return 1
        except IndexError:
            return 1
        return 0

    def startElevation(self):
        if self.level == 1:
            self.elevate()
            return 0
        while True:
            self.appendMessages(self.actions.broadcast(self.params.name))
            self.countItems(self.appendMessages(self.actions.look()))
            if self.look_res[0][0] == 6:
                break
        while True:
            outcome = self.elevate()
            if self.level == 8:
                return 0
            if outcome == 1:
                return 1

    def goToBroadcast(self):
        self.writeLog("Going to broadcast")
        while True:
            #Receive message from server:
            if len(self.messages) == 0 or self.connection.readable():
                data = self.connection.receive()
                data = data.split("\n")
                for entry in data:
                    self.writeLog(f"goToBroadcast Received: {entry}")
                    if "dead" in entry:
                        print("Broad Died")
                        self.writeLog("Died during broadcast")
                        script_dir = os.path.dirname(__file__)
                        correct_subdir = 'ai'
                        main_script_path = os.path.join(script_dir, correct_subdir, 'Main.py')
                        subprocess.Popen([sys.executable, main_script_path, '-p', str(self.params.port), '-n', self.params.name, '-h', self.params.host])
                        sys.exit(84)
                    if "Current level" in entry:
                        self.level = int(entry.split(" ")[2])
                        self.writeLog(f"Level update: {self.level}")
                        # self.waitForElevation = True # if here, mean elevation started
                        # and ia stuck in this loop where it get it's level or it's death
                        # so it's not bad to be stuck here
                        if self.level == 8:
                            print("I obtained ultimate wisdom, goodbye")
                            self.writeLog("I obtained ultimate wisdom, goodbye")
                            sys.exit(0)
                    if "message" in entry and self.params.name in entry:
                        self.messages.append(entry)

            #get k from message:
            if len(self.messages) == 0: #in case catch message from other team
                continue
            message = self.messages[0]
            self.writeLog(f"Using message: {message}")
            if "message" not in message:
                print("Unexpected message skipped: ", message)
                continue
            for char in message:
                if char.isdigit():
                    self.k = int(char)
                    break
            self.writeLog(f"K: {self.k}")

            #go in direction of k:
            match self.k:
                case 1:
                    self.appendMessages(self.actions.forward())
                case 2:
                    self.appendMessages(self.actions.forward())
                    self.appendMessages(self.actions.left())
                    self.appendMessages(self.actions.forward())
                case 3:
                    self.appendMessages(self.actions.left())
                    self.appendMessages(self.actions.forward())
                case 4:
                    self.appendMessages(self.actions.left())
                    self.appendMessages(self.actions.forward())
                    self.appendMessages(self.actions.left())
                    self.appendMessages(self.actions.forward())
                case 5:
                    self.appendMessages(self.actions.left())
                    self.appendMessages(self.actions.left())
                    self.appendMessages(self.actions.forward())
                case 6:
                    self.appendMessages(self.actions.right())
                    self.appendMessages(self.actions.forward())
                    self.appendMessages(self.actions.right())
                    self.appendMessages(self.actions.forward())
                case 7:
                    self.appendMessages(self.actions.right())
                    self.appendMessages(self.actions.forward())
                case 8:
                    self.appendMessages(self.actions.forward())
                    self.appendMessages(self.actions.right())
                    self.appendMessages(self.actions.forward())
                case 0:
                    self.writeLog("Waiting for elevation")
                    # self.waitForElevation = True
                    # return
            
            #clear messages so k is up to date with current position
            self.inventory.updateInventory(self.appendMessages(self.actions.inventory()))
            self.messages = []
            self.writeLog("Messages cleared")

    def processMessages(self):
        for message in self.messages:
            if self.params.name in message:
                if self.level == 1:     
                    return
                self.goToBroadcast()
                return
            # other messages handle here
        self.messages = []
    
    def runQueen(self):
        self.queen = True
        self.connection.setParams(self.params)

        #Lay eggs:
        for _ in range(5 - self.params.client_nb):
            data = self.appendMessages(self.actions.fork())
            if data == "ko\n":
                print("Error laying egg")
                sys.exit(84)
        
        while True:
            #Connection childs:
            try:
                data = int(self.appendMessages(self.actions.connect_nbr()))
                for _ in range(data):
                    if fork() == 0:
                        main(False, self.params)
                        sys.exit(0)
            except ValueError:
                print("Bad server response to connect_nbr")
                print("Data: ", data)

            #Receive messages from server:
            if self.connection.readable():
                data = self.connection.receive()
                data = data.split("\n")
                for entry in data:
                    self.writeLog(f"Received: {entry}")
                    if "dead" in entry:
                        print("Queen Died")
                        script_dir = os.path.dirname(__file__)
                        main_script_path = os.path.join(script_dir, 'Main.py')
                        subprocess.Popen([sys.executable, main_script_path, '-p', str(self.params.port), '-n', self.params.name, '-h', self.params.host])
                        break
                # the queen does not take message from the underlings, but if it has to, it will be here

            #Update needs:
            self.updateNeeds()

            #Process messages:
            # for now the queen does not get messages

            #Elevation:
            if self.checkElevation():
                if self.startElevation() == 1:
                    #elevate 2 -> 8 failed, send fail message, regather ressources, lay eggs, connect new ai, ...
                    break

            if self.level == 8:
                print("I obtained ultimate wisdom, goodbye")
                sys.exit(0)

            #Gather resources:
            self.countItems(self.appendMessages(self.actions.look()))
            best_tile = self.findBestTile()
            if best_tile != -1:
                self.go(best_tile)
                self.takeItems(best_tile)
            
            #Update inventory:
            self.inventory.updateInventory(self.appendMessages(self.actions.inventory()))
    
    def runChild(self):
        self.connection.setParams(self.params)

        while True:
            #Receive messages from server:
            if self.connection.readable():
                data = self.connection.receive()
                data = data.split("\n")
                for entry in data:
                    self.writeLog(f"Received: {entry}")
                    if "dead" in entry:
                        print("Child Died")
                        script_dir = os.path.dirname(__file__)
                        main_script_path = os.path.join(script_dir, 'Main.py')
                        subprocess.Popen([sys.executable, main_script_path, '-p', str(self.params.port), '-n', self.params.name, '-h', self.params.host])
                        break
                    if "Current level" in entry:
                        self.level = int(entry.split(" ")[2])
                        if self.level == 8:
                            print("I obtained ultimate wisdom, goodbye")
                            sys.exit(0)
                    if "message" in entry:
                        self.messages.append(entry)

            if self.level == 8:
                print("I am level 8, I am free")
                break

            #Update needs:
            self.updateNeeds()

            #Process messages:
            self.processMessages()

            #If in ritual, wait for elevation:
            if self.waitForElevation:
                continue

            #Elevation:
            if self.checkElevation():
                self.startElevation()

            #Gather resources:
            self.countItems(self.appendMessages(self.actions.look()))
            best_tile = self.findBestTile()
            if best_tile != -1:
                self.go(best_tile)
                self.takeItems(best_tile)
            
            # #Update inventory:
            self.inventory.updateInventory(self.appendMessages(self.actions.inventory()))

def main(queen=True, params=None):
    if params is None:
        params = Params()
        params.get_args(sys.argv)

    print(f"Host: {params.host}, Port: {params.port}, Name: {params.name}")

    ai = AI(params)
    ai.connect_to_server()
    if queen:
        ai.runQueen()
    else:
        ai.runChild()

if __name__ == "__main__":
    main()
