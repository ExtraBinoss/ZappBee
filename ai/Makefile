##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## Makefile
##

TARGET := zappy_ai
PYTHON := python3
SRC := $(wildcard *.py)
RM := rm -rf

all:
	ln -s ai/Main.py ../zappy_ai

clean:
	@$(RM) -r __pycache__

fclean: clean
	@$(RM) ../$(TARGET)

re: fclean all
