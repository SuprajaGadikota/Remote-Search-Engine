CC=gcc
CFLAGS=-c -Wall -g
FLAGS=-o
SRC=../src/
OBJ=../obj/
BIN=../bin/
INCLUDE=-I ../include/
HEADER=../include/
CCOV= -fprofile-arcs -ftest-coverage
LFLAGS= -lgcov --coverage

ALL : $(BIN)server $(BIN)client

$(BIN)server : $(OBJ)server.o $(OBJ)server_functions.o 
	$(CC) $(CCOV) $(FLAGS) server $(OBJ)server.o $(OBJ)server_functions.o $(LFLAGS)
	mv server ../bin/

$(OBJ)server.o : $(SRC)server.c $(HEADER)utility.h 
	$(CC) $(CCOV) $(CFLAGS) $(INCLUDE) $(SRC)server.c $(LFLAGS)
	mv server.o ../obj/

$(OBJ)server_functions.o : $(SRC)server_functions.c $(HEADER)utility.h 
	$(CC) $(CCOV) $(CFLAGS) $(INCLUDE) $(SRC)server_functions.c $(LFLAGS)
	mv server_functions.o ../obj/

$(BIN)client : $(OBJ)client.o $(OBJ)client_functions.o
	$(CC) $(CCOV) $(FLAGS) client $(OBJ)client.o $(OBJ)client_functions.o $(LFLAGS)
	mv client ../bin/

$(OBJ)client.o : $(SRC)client.c $(HEADER)utility.h
	$(CC) $(CCOV) $(CFLAGS) $(INCLUDE) $(SRC)client.c $(LFLAGS)
	mv client.o ../obj/

$(OBJ)client_functions.o : $(SRC)client_functions.c $(HEADER)utility.h
	$(CC) $(CCOV) $(CFLAGS) $(INCLUDE) $(SRC)client_functions.c $(LFLAGS)
	mv client_functions.o ../obj/

clean:
	rm $(BIN)server	
	rm $(BIN)client
	rm $(OBJ)*.o
