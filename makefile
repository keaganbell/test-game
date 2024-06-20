PROJ_ROOT:=$(shell pwd)
PROJ_NAME:=test-game

LIBS:=-lraylib -lm -ldl
INCS:=-I$(PROJ_ROOT)/source
BUILDIR:=$(PROJ_ROOT)/build
OBJDIR:=$(BUILDIR)/obj

CC:=cc
CFLAGS:=-Wall -Wextra -fPIC
DEFINES:=-DPLATFORM_LINUX
BUILD_CONFIG:=dev

TARGET:=$(PROJ_ROOT)/$(PROJ_NAME)
SRCDIR:=$(PROJ_ROOT)/source
SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

GAMEDLTARGET:=$(BUILDIR)/libgame.so
GAMESRCDIR:=$(SRCDIR)/gamelib
GAMESRC:=$(wildcard $(GAMESRCDIR)/*.c)
GAMEOBJS:=$(patsubst $(GAMESRCDIR)/%.c, $(OBJDIR)/%.o, $(GAMESRC))


# build configuration detection ###################################################
# default build config is development unless specified at make runtime
# e.g., make TARGET_CONFIG=release clean all
ifeq ($(TARGET_CONFIG), debug)
BUILD_CONFIG=debug
else ifeq ($(TARGET_CONFIG), release)
BUILD_CONFIG=release
endif

ifeq ($(BUILD_CONFIG), dev)
CFLAGS += -g -ggdb
DEFINES += -DHOTRELOAD
else ifeq ($(BUILD_CONFIG), debug)
CFLAGS += -g -O2
else ifeq ($(BUILD_CONFIG), release)
CFLAGS += -O3
endif


.PHONY: all
all: $(TARGET) $(GAMEDLTARGET)

.PHONY: game
game: $(GAMEDLTARGET)

$(GAMEDLTARGET): $(GAMEOBJS)
	$(CC) $(CFLAGS) $(INCS) -shared -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(GAMESRCDIR)/%.c | build-dirs
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $@ $^ $(DEFINES) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | build-dirs
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(DEFINES) $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(GAMEDLTARGET)

.PHONY: build-dirs
build-dirs:
	mkdir -p $(OBJDIR)
