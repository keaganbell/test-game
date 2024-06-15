PROJ_ROOT:=$(shell pwd)
PROJ_NAME:=test-game
TARGET:=$(PROJ_ROOT)/$(PROJ_NAME)
LIBS:=-lraylib -lm -ldl
INCS:=-I$(PROJ_ROOT)/source -I$(PROJ_ROOT)/source/corelib

SRCDIR:=$(PROJ_ROOT)/source
SRCS:=$(wildcard $(SRCDIR)/*.c)

BUILDIR:=$(PROJ_ROOT)/build
OBJDIR:=$(BUILDIR)/obj
OBJS:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

CC:=cc
CFLAGS:=-Wall -Wextra -g

include $(SRCDIR)/gamelib/makefile
include $(SRCDIR)/corelib/makefile

all: build-dirs $(TARGET) $(CORETARGET) $(GAMEDLTARGET) 

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCS) -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(TARGET) $(GAMEDLTARGET) $(CORETARGET)

.PHONY: build-dirs
build-dirs:
	mkdir -p $(OBJDIR)
