CC= gcc
CFLAGS= -g -Wall
LIBS= -lm
SOURCES= args.c netw.c main.c 
OBJECTS = $(SOURCES:.c=.o)
TARGET= main


all: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)

OBJECTS: $(SOURCES)
	gcc -c $(SOURCES) $(OBJECTS)

clean: 
	rm $(OBJECTS) $(TARGET)
