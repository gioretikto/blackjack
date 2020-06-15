CC = gcc
CFLAGS = `pkg-config --cflags --libs gtk+-3.0` -std=c99 -Wall
SYSTEM = `uname -s`

ifeq ($(SYSTEM), SunOS)
	CFLAGS+= -D__EXTENSIONS__
endif

LDLIBS = `pkg-config --libs gtk+-3.0`
SRCS = main.c gtk_engine.c black.c
OBJS = $(SRCS:.c=.o)
PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
TARGET = blackjack

$(TARGET): $(OBJS)
	 $(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
clean:
	rm -f $(OBJS)
install:
	install $(TARGET) $(BINDIR)
