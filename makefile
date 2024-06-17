PROJ_ROOT:=$(shell pwd)
PROJ_NAME:=test-game

LIBS:=-lraylib -lm -ldl
INCS:=-I$(PROJ_ROOT)/source
BUILDIR:=$(PROJ_ROOT)/build
OBJDIR:=$(BUILDIR)/obj

CC:=cc
CFLAGS:=-Wall -Wextra -g -finline-functions -fPIC

TARGET:=$(PROJ_ROOT)/$(PROJ_NAME)
SRCDIR:=$(PROJ_ROOT)/source
SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

GAMEDLTARGET:=$(BUILDIR)/libgame.so
GAMESRCDIR:=$(SRCDIR)/gamelib
GAMESRC:=$(wildcard $(GAMESRCDIR)/*.c)
GAMEOBJS:=$(patsubst $(GAMESRCDIR)/%.c, $(OBJDIR)/%.o, $(GAMESRC))

.PHONY: all
all: $(TARGET) $(GAMEDLTARGET)

.PHONY: game
game: $(GAMEDLTARGET)

$(GAMEDLTARGET): $(GAMEOBJS)
	$(CC) $(CFLAGS) $(INCS) -shared -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(GAMESRCDIR)/%.c | build-dirs
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | build-dirs
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(GAMEDLTARGET)

.PHONY: build-dirs
build-dirs:
	mkdir -p $(OBJDIR)
