CPPFLAGS = -std=c++17 -Wall -MD -MP 
TARGET := main

SRC = $(wildcard *.cpp)
all: main

main: $(SRC:%.cpp=%.o)
	g++ $(CPPFLAGS) -o $@ $^
	
clean:
	rm -rf $(TARGET) *.o

-include $(SRC:%.cpp=%.d)