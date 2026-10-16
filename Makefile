PS3DEV  ?= /usr/local/ps3dev
PSL1GHT ?= $(PS3DEV)
export PS3DEV PSL1GHT

CC      := $(PS3DEV)/ppu/bin/powerpc64-ps3-elf-gcc
STRIP   := $(PS3DEV)/ppu/bin/powerpc64-ps3-elf-strip

BUILDDIR := build-ps3
TARGET   := $(BUILDDIR)/CellCraft.elf

SRCS := src/main.c src/CellCraft.c src/socketio.c src/player.c src/c2s.c \
        src/s2c.c src/util.c src/log.c src/encryption.c src/https.c \
        src/game.c src/world.c src/blocks.c src/storage.c src/ps3ui.c
OBJS := $(SRCS:src/%.c=$(BUILDDIR)/%.o)

INCLUDES := -Iinclude/CellCraft -Iinclude/3rdparty -I. \
            -I$(PSL1GHT)/ppu/include \
            -I$(PS3DEV)/portlibs/ppu/include \
            -I$(PS3DEV)/portlibs/ppu/include/freetype2

ifdef AUTH
LWJSON_SRCS := 3rdparty/lwjson/lwjson/src/lwjson/lwjson.c \
               3rdparty/lwjson/lwjson/src/lwjson/lwjson_stream.c
LWJSON_OBJS := $(LWJSON_SRCS:3rdparty/lwjson/lwjson/src/lwjson/%.c=$(BUILDDIR)/lwjson_%.o)
OBJS += $(LWJSON_OBJS)
INCLUDES += -I3rdparty/lwjson/lwjson/src/include
DEFINES := -DLWJSON_IGNORE_USER_OPTS -DENDIAN=0
else
DEFINES := -DCELLCRAFT_NO_AUTH -DENDIAN=0
endif

CFLAGS := -mcpu=cell -O2 -std=gnu11 -Wall -Wextra -Wno-unused-parameter \
          $(INCLUDES) $(DEFINES)

LDFLAGS := -L$(PSL1GHT)/ppu/lib -L$(PS3DEV)/portlibs/ppu/lib
LIBS    := -lnet -lsysmodule -lsysutil -lrt -llv2 -lm -lmbedtls -lmbedx509 -lmbedcrypto -ltiny3d -lrsx -lgcm_sys -lfont3d -lfreetype -lz -lm

all: $(TARGET)

TITLE     := CellCraft
APPID     := CELLCRAFT
CONTENTID := UP0001-$(APPID)_00-0000000000000000
SFOXML    := $(PS3DEV)/bin/sfo.xml
ICON0     := assets/ICON0.PNG

SPRXLINKER      := $(PS3DEV)/bin/sprxlinker
MAKE_SELF       := $(PS3DEV)/bin/make_self
MAKE_SELF_NPDRM := $(PS3DEV)/bin/make_self_npdrm
SFO             := $(PS3DEV)/bin/sfo
PKGTOOL         := $(PS3DEV)/bin/pkg

STRIPPED := $(BUILDDIR)/CellCraft_stripped.elf
SELF     := $(BUILDDIR)/CellCraft.self
PKGFILE  := $(BUILDDIR)/CellCraft.pkg

self: $(SELF)
$(SELF): $(TARGET)
	$(STRIP) $< -o $(STRIPPED)
	$(SPRXLINKER) $(STRIPPED)
	$(MAKE_SELF) $(STRIPPED) $@

pkg: $(PKGFILE)
$(PKGFILE): $(SELF)
	mkdir -p $(BUILDDIR)/pkg/USRDIR
	cp $(ICON0) $(BUILDDIR)/pkg/ICON0.PNG
	$(MAKE_SELF_NPDRM) $(STRIPPED) $(BUILDDIR)/pkg/USRDIR/EBOOT.BIN $(CONTENTID) >> /dev/null
	$(SFO) --title "$(TITLE)" --appid "$(APPID)" -f $(SFOXML) $(BUILDDIR)/pkg/PARAM.SFO
	$(PKGTOOL) --contentid $(CONTENTID) $(BUILDDIR)/pkg/ $@ >> /dev/null

# Release: genera los dos .pkg listos para subir a GitHub.
RELEASEDIR := release
release: release-offline release-online
release-offline:
	$(MAKE) clean pkg
	mkdir -p $(RELEASEDIR)
	cp $(PKGFILE) $(RELEASEDIR)/CellCraft-offline.pkg
release-online:
	$(MAKE) clean pkg AUTH=1
	mkdir -p $(RELEASEDIR)
	cp $(PKGFILE) $(RELEASEDIR)/CellCraft-online.pkg

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) $(LIBS) -o $@

FLAGSTAMP := $(BUILDDIR)/.flags
$(FLAGSTAMP): | $(BUILDDIR)
	@echo "$(DEFINES)" | cmp -s - $@ || echo "$(DEFINES)" > $@
$(OBJS): $(FLAGSTAMP)

$(BUILDDIR)/%.o: src/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/lwjson_%.o: 3rdparty/lwjson/lwjson/src/lwjson/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean self pkg release release-offline release-online
