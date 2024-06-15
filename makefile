PROJ_ROOT:=$(shell pwd)
PROJ_NAME:=test-game

LIBS:=-lraylib -lm -ldl
INCS:=-I$(PROJ_ROOT)/source -I$(PROJ_ROOT)/source/corelib
BUILDIR:=$(PROJ_ROOT)/build
OBJDIR:=$(BUILDIR)/obj

CC:=cc
CFLAGS:=-Wall -Wextra -g

TARGET:=$(PROJ_ROOT)/$(PROJ_NAME)
SRCDIR:=$(PROJ_ROOT)/source
SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

GAMEDLTARGET:=$(BUILDIR)/libgame.so
GAMESRCDIR:=$(SRCDIR)/gamelib
GAMESRC:=$(wildcard $(GAMESRCDIR)/*.c)
GAMEOBJS:=$(patsubst $(GAMESRCDIR)/%.c, $(OBJDIR)/%.o, $(GAMESRC))

CORETARGET:=$(BUILDIR)/libcore.so
CORESRCDIR:=$(SRCDIR)/corelib
CORESRC:=$(wildcard $(CORESRCDIR)/*.c)
COREOBJS:=$(patsubst $(CORESRCDIR)/%.c, $(OBJDIR)/%.o, $(CORESRC))

all: $(TARGET) $(CORETARGET) $(GAMEDLTARGET) 

.PHONY: game
game: $(GAMEDLTARGET)

.PHONY: core
core: $(CORETARGET)

$(CORETARGET): $(COREOBJS)
	$(CC) $(CFLAGS) $(INCS) -shared -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(CORESRCDIR)/%.c | build-dirs
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

$(GAMEDLTARGET): $(GAMEOBJS)
	$(CC) $(CFLAGS) $(INCS) -shared -o $@ $^ $(LIBS) $(BUILDIR)/libcore.so

$(OBJDIR)/%.o: $(GAMESRCDIR)/%.c | build-dirs
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | build-dirs
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(GAMEDLTARGET) $(CORETARGET)

.PHONY: build-dirs
build-dirs:
	mkdir -p $(OBJDIR)
