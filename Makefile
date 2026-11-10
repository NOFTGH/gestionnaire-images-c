CC = gcc
CFLAGS = -std=gnu11 -Wall -Wextra -g
LDFLAGS = -lSDL2

SRCS = main.c pgm.c display.c gfx.c quadtree.c transform.c
OBJS = $(SRCS:.c=.o)
TARGET = projet_image

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
