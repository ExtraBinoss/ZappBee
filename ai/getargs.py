##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## getargs.py
##

import getopt
import sys

class Params:
    def __init__(self):
        self.host = "localhost"
        self.port = 0
        self.name = ""
        self.x = 0
        self.y = 0
        self.client_nb = 0
    
    def usage(self, av):
        if len(av) == 2 and av[1] == "-help":
                print("Usage: ./zappy_ai -p port -n name -h machine")
                print("\t-p\tport numbe")
                print("\t-n\tname of the team")
                print("\t-h\tname of the machine; localhost by default")
                sys.exit(0)
        else:
            print("Usage: ./zappy_ai -p port -n name -h machine")
            sys.exit(84)

    def get_args(self, av):
        if len(av) != 7 and len(av) != 5:
             self.usage(av)
        try:
            opts, args = getopt.getopt(av[1:], "p:n:h:")
        except getopt.GetoptError:
            self.usage(av)
        for opt, arg in opts:
            if opt == "-p":
                self.port = int(arg)
            elif opt == "-n":
                self.name = arg
            elif opt == "-h":
                self.host = arg
        if self.port == 0 or self.name == "":
            self.usage(av)
        return self
