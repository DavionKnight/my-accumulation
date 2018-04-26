
# Which compiler
CC = g++

#Options for development
CFLAGS= -Wall -ansi
CFLAGS+=-I ./  
LDFLAGS= -static
SOURCES=./main.cpp ./parser.cpp ./user.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=parse

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o parse

