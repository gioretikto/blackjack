CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0` -std=c99 -Wall
LDLIBS = `pkg-config --libs gtk+-3.0`
OBJFILES = main.o gtk_engine.o black.o
TARGET = blackjack
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(LDLIBS) -o $(TARGET) $(OBJFILES) 
clean:
	rm -f $(OBJFILES)
install:
	cp $(TARGET) /usr/local/bin