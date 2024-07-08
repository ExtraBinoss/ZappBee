##
## EPITECH PROJECT, 2023
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## Makefile
##

SRC = $(shell find src/ -name '*.c')
OBJ = $(SRC:.c=.o)
TARGET = zappy_server
CC = gcc
CFLAGS = -Wall -Wextra \
         -I includes \
         -I includes/instructions_headers \
         -I includes/map_headers \
         -I includes/network_headers \
		 -I includes/gui_events \
		 -lm \
		 -g3
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS)
	mv $(TARGET) ../$(TARGET)
	mkdir -p log

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../$(TARGET)
	$(RM) -r log

re: fclean all
