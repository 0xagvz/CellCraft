PS3DEV  ?= /usr/local/ps3dev
PSL1GHT ?= $(PS3DEV)
export PS3DEV PSL1GHT

CC      := $(PS3DEV)/ppu/bin/powerpc64-ps3-elf-gcc
STRIP   := $(PS3DEV)/ppu/bin/powerpc64-ps3-elf-strip

BUILDDIR := build-ps3
TARGET   := $(BUILDDIR)/UCraft.elf

SRCS := src/main.c src/UCraft.c src/socketio.c src/player.c src/c2s.c \
        src/s2c.c src/util.c src/log.c src/encryption.c src/https.c \
        src/game.c src/world.c src/blocks.c src/storage.c
OBJS := $(SRCS:src/%.c=$(BUILDDIR)/%.o)

INCLUDES := -Iinclude/UCraft -Iinclude/3rdparty -I. \
            -I$(PSL1GHT)/ppu/include \
            -I$(PS3DEV)/portlibs/ppu/include

DEFINES := -DUCRAFT_NO_AUTH

CFLAGS := -mcpu=cell -O2 -std=gnu11 -Wall -Wextra -Wno-unused-parameter \
          $(INCLUDES) $(DEFINES)

LDFLAGS := -L$(PSL1GHT)/ppu/lib -L$(PS3DEV)/portlibs/ppu/lib
LIBS    := -lnet -lsysmodule -lrt -llv2 -lm -lmbedtls -lmbedx509 -lmbedcrypto -lz

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@

$(BUILDDIR)/%.o: src/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
