CC = gcc
CFLAGS = -Wall -I$(INCDIR) -pg  
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
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR) gmon.out 

$(shell mkdir -p $(BINDIR) $(OBJDIR))

run: all
	./$(BINDIR)/main fatorial-recursivo 1 16
	./$(BINDIR)/main fatorial-iterativo 1 20
	./$(BINDIR)/main fibonacci-recursivo 1 40
	./$(BINDIR)/main fibonacci-iterativo 1 40

profile: all
	./$(BINDIR)/main fibonacci-recursivo 1 40
	gprof ./$(BINDIR)/main > output.txt 
