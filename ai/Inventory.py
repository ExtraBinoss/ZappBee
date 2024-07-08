##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## Inventory.py
##

class Inventory:
    def __init__(self):
        self.inventory = [0, 0, 0, 0, 0, 0, 0, 0]
        self.items = ["player", "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

    def updateInventory(self, data):
        if data is None:
            return
        data = data.replace("\n", "")
        if "[ " in data:
            data = data.replace("[ ", "")
            data = data.replace(" ]", "")
        else:
            data = data.replace("[", "")
            data = data.replace("]", "")
        data = data.split(", ")
        for item in data:
            try:
                name, count = item.split(" ")
                if name in self.items:
                    self.inventory[self.items.index(name)] = int(count)
            except ValueError:
                print("Error: Invalid inventory data")
                print("Data: ", data)
                return
