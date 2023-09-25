#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#               : 2021-11-15 - Versao 1.1 memlog
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/matop

all:  mem perf gprof

mem: $(EXE)
	$(EXE) -s -p /tmp/somalog.out -l -x 4 -y 5
	$(EXE) -m -p /tmp/multlog.out -l -x 5 -y 5
	$(EXE) -t -p /tmp/transplog.out -l -x 5 -y 4
	$(EXE) -c /tmp/out.txt -p /tmp/transplog.out -l -x 5 -y 4

perf: $(EXE)
	$(EXE) -s -p /tmp/soma10.out  -x 10 -y 10
	$(EXE) -m -p /tmp/mult10.out  -x 10 -y 10
	$(EXE) -t -p /tmp/transp10.out  -x 10 -y 10
	$(EXE) -s -p /tmp/soma20.out  -x 20 -y 20
	$(EXE) -m -p /tmp/mult20.out  -x 20 -y 20
	$(EXE) -t -p /tmp/transp20.out  -x 20 -y 20
	$(EXE) -s -p /tmp/soma30.out  -x 30 -y 30
	$(EXE) -m -p /tmp/mult30.out  -x 30 -y 30
	$(EXE) -t -p /tmp/transp30.out  -x 30 -y 30
	$(EXE) -s -p /tmp/soma40.out  -x 40 -y 40
	$(EXE) -m -p /tmp/mult40.out  -x 40 -y 40
	$(EXE) -t -p /tmp/transp40.out  -x 40 -y 40
	$(EXE) -s -p /tmp/soma50.out  -x 50 -y 50
	$(EXE) -m -p /tmp/mult50.out  -x 50 -y 50
	$(EXE) -t -p /tmp/transp50.out  -x 50 -y 50
	$(EXE) -m -p /tmp/mult10log.out -l -x 10 -y 10

gprof: $(BIN)/matop
	$(EXE) -s -p /tmp/soma50gprof.out  -x 50 -y 50
	gprof $(EXE) gmon.out > /tmp/soma50gprof.txt
	$(EXE) -m -p /tmp/mult50gprof.out  -x 50 -y 50
	gprof $(EXE) gmon.out > /tmp/mult50gprof.txt
	$(EXE) -t -p /tmp/transp50gprof.out  -x 50 -y 50
	gprof $(EXE) gmon.out > /tmp/transp50gprof.txt
	

$(BIN)/matop: $(OBJS)
	$(CC) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out *grind*
