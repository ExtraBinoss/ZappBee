##
## EPITECH PROJECT, 2024
## B-YEP-400-MPL-4-1-zappy-robin.glaude
## File description:
## Makefile
##

CXX := g++
CXXFLAGS := -Isrc/includes -std=c++2a -Wall -Wextra
SRCS := $(shell find src -name '*.cpp')
OBJS := $(SRCS:.cpp=.o)
SFML_LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lpthread
TARGET := zappy_gui

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(SFML_LIBS)
	mv $(TARGET) ../$(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../$(TARGET)

re: fclean all
