##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## Makefile
##

all:
	@$(MAKE) -C ai
	@$(MAKE) -C gui
	@$(MAKE) -C server

server:
	@$(MAKE) -C server

gui:
	@$(MAKE) -C gui

clean:
	@$(MAKE) -C ai clean
	@$(MAKE) -C gui clean
	@$(MAKE) -C server clean

fclean:
	@$(MAKE) -C ai fclean
	@$(MAKE) -C gui fclean
	@$(MAKE) -C server fclean

re: fclean all

zappy_ai:
	@$(MAKE) -C ai
