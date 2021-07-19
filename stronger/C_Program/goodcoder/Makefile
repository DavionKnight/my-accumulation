
CC = g++

#Options for development
CFLAGS= -Wall -ansi
CFLAGS+=-I ./ -I./ullib/include 
#LDFLAGS= -L./ullib/lib -lullib
SOURCES=./parser.cpp ./user.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test
EXETEST=gtest

all: $(SOURCES) $(EXECUTABLE) $(EXETEST)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) main.cpp -o $@ -L./ullib/lib -lullib -lpthread
$(EXETEST): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) main_gtest.cpp -g  -o $@ -L./ullib/lib -lullib -lgtest -lgtest_main -lpthread 

.cpp.o:
	$(CC) $(CFLAGS) -c $< -g -o $@

clean:
	rm -rf *.o $(EXETEST) $(EXECUTABLE)

