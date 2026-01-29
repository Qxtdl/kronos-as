CC = gcc
CFLAGS = -g -Wall -Wextra -Werror \
	-Wno-error=unused-variable -Wno-error=unused-parameter -Wno-error=switch

BUILD = build
OUTPUT = $(BUILD)/kronos-as
PROG_NAME = internet
OUTPUT_ARGS = examples/$(PROG_NAME).s build/$(PROG_NAME).bin build/$(PROG_NAME)_ram.bin

CSRCS = $(shell find src -name '*.c')
OBJS = $(patsubst %.c,$(BUILD)/%.o,$(CSRCS))

all: clean $(OBJS) $(OUTPUT) run

$(BUILD)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $(OUTPUT)

run:
	./$(OUTPUT) $(OUTPUT_ARGS)
	python kronos_encoder.py build/$(PROG_NAME).bin
	python kronos_ram_encoder.py build/$(PROG_NAME)_ram.bin

clean:
	rm -rf $(BUILD)
