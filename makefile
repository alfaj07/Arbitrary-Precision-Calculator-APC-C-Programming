CC := gcc
CFLAGS := -Wall -Wextra -std=c11
OBJ := $(patsubst %.c,%.o,$(wildcard *.c))
TARGET := apc.exe
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
.PHONY: all clean              