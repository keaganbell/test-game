CORETARGET:=$(BUILDIR)/libcore.so
CORESRCDIR:=$(SRCDIR)/corelib
CORESRC:=$(wildcard $(CORESRCDIR)/*.c)
COREOBJS:=$(patsubst $(CORESRCDIR)/%.c, $(OBJDIR)/%.o, $(CORESRC))

$(CORETARGET): $(COREOBJS)
	$(CC) $(CFLAGS) $(INCS) -shared -o $@ $^ $(LIBS)

$(OBJDIR)/%.o: $(CORESRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCS) -o $@ -c $< $(LIBS)
