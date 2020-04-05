CC = gcc
CFLAGS = -Wall -pedantic -Wextra -std=c99 
LDFLAGS=`(pkg-config --cflags gtk+-3.0)`
OBJFILES = main.o gtk_engine.o black.o
TARGET = blackjack
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET)
install:
	cp $(TARGET) /usr/local/bin

