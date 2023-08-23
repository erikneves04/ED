# Makefile para compilar os arquivos src/mat.c e src/matop.c

CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lm
SRCDIR = src
BINDIR = bin
OBJDIR = obj
INCDIR = include

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))
EXEFILE = $(BINDIR)/program

.PHONY: all clean

all: $(EXEFILE)

$(EXEFILE): $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)

$(shell mkdir -p $(BINDIR) $(OBJDIR))