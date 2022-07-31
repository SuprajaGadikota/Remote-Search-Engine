CC = gcc
CFLAGS = -Wall -c -g 
OFLAGS = -o
VFLAGS = --tool=memcheck --leak-check=yes --show-reachable=yes
BIN = bin/
INCLUDE = -I../include/ -I./
HEADER = ../include/
SRC = ../src/
OBJ = obj/
CUNIT_LIB_DIR = -L/usr/lib/    #location of CUnit library
CUNIT_INC_DIR = /usr/include/CUnit/
AUT_INC =  -I$(CUNIT_INC_DIR)

#using shared library
all: $(BIN)test


$(BIN)test: $(OBJ)test.o $(OBJ)testfunctions.o $(OBJ)server_functions.o
	$(CC) $(OFLAGS) test $(OBJ)server_functions.o $(OBJ)test.o $(OBJ)testfunctions.o  $(CUNIT_LIB_DIR) -lcunit
	mv test $(BIN)

$(OBJ)test.o: test.c $(HEADER)utility.h testfunctions.h 
	$(CC) $(CFLAGS) test.c $(INCLUDE)   ${AUT_INC}
	mv test.o $(OBJ)

$(OBJ)testfunctions.o: testfunctions.c $(HEADER)utility.h 
	$(CC) $(CFLAGS) testfunctions.c $(INCLUDE) ${AUT_INC}
	mv testfunctions.o  $(OBJ)

$(OBJ)server_functions.o: $(SRC)server_functions.c $(HEADER)utility.h  
	$(CC) $(CFLAGS) $(SRC)server_functions.c $(INCLUDE)  
	mv server_functions.o $(OBJ)

clean: 
	rm -f $(BIN)test
	rm -f $(OBJ)*.o
