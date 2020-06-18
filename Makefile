CC = gcc
CFLAGS = -std=c99 -W -Wextra -Werror -Wall -pedantic `pkg-config --cflags gtk+-3.0` -Wstrict-prototypes -Wmissing-prototypes -Wshadow -Wconversion
SYSTEM = `uname -s`

ifeq ($(SYSTEM), SunOS)
	CFLAGS+= -D__EXTENSIONS__
endif

LDLIBS = `pkg-config --libs gtk+-3.0`
SRCS = main.c gui.c resources.c deck.c black.c
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
	