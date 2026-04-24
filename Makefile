CC     = gcc
CFLAGS = -Wall -Wextra -g
TARGET = scheduler
BIN    = bin

SRCS = main.c process.c fifo.c sjf.c rr.c srtf.c gantt.c
OBJS = $(patsubst %.c,$(BIN)/%.o,$(SRCS))

all: $(BIN) $(TARGET)

$(BIN):
	mkdir -p $(BIN)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

$(BIN)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf $(BIN)

.PHONY: all clean