CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0` -std=c99 -ggdb3
LDLIBS = `shell pkg-config --libs gtk+-3.0`
OBJFILES = main.o gtk_engine.o black.o
TARGET = blackjack
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET)
install:
	cp $(TARGET) /usr/local/bin