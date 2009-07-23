CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lSDL -lGL
SOURCES=main.cpp core/SDLwindow.h core/window.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=learn-gl

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	rm *.o $(EXECUTABLE)