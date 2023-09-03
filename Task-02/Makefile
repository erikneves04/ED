CC = gcc
CFLAGS = -Wall -I$(INCDIR)
LDFLAGS = -lm
SRCDIR = src
BINDIR = bin
OBJDIR = obj
INCDIR = include
EXEFILE = $(BINDIR)/main

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))

.PHONY: all clean run profile

all: $(EXEFILE)

$(EXEFILE): $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -pg -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)

$(shell mkdir -p $(BINDIR) $(OBJDIR))

run: all
	./$(BINDIR)/main fibonacci-recursivo 1 40
	./$(BINDIR)/main fibonacci-iterativo 1 40