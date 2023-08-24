CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lm
SRCDIR = src
BINDIR = bin
OBJDIR = obj
INCDIR = include
EXEFILE = $(BINDIR)/matop

SRCFILES = $(wildcard $(SRCDIR)/*.c)
OBJFILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCFILES))

.PHONY: all clean run

all: $(EXEFILE)

$(EXEFILE): $(OBJFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)

$(shell mkdir -p $(BINDIR) $(OBJDIR))

run: all
	./$(BINDIR)/matop -s -x 5 -y 5
	./$(BINDIR)/matop -m -x 5 -y 5
	./$(BINDIR)/matop -t -x 5 -y 5