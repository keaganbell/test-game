GAMEDLTARGET:=$(BUILDIR)/libgame.so
GAMESRCDIR:=$(SRCDIR)/gamelib
GAMESRC:=$(wildcard $(GAMESRCDIR)/*.c)
GAMEOBJS:=$(patsubst $(GAMESRCDIR)/%.c, $(OBJDIR)/%.o, $(GAMESRC))

$(GAMEDLTARGET): $(GAMEOBJS)
	$(CC) $(CFLAGS) $(INCS) -shared -o $@ $^ $(LIBS) $(BUILDIR)/libcore.so

$(OBJDIR)/%.o: $(GAMESRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)
