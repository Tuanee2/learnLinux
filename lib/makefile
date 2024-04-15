.PHONY: all clean

LIB_NAME_SHARED := test
LIB_NAME_STATIC := test01

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
SRC_DIR := $(CUR_DIR)/src
OBJ_DIR := $(CUR_DIR)/objs
LIB_DIR := $(CUR_DIR)/libs
LIB_SHARED := $(LIB_DIR)/shared
LIB_STATIC := $(LIB_DIR)/static

CC := gcc 
CFLAGS := -I $(INC_DIR)

mk_objs:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(CFLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/hello.c -o $(OBJ_DIR)/hello.o $(CFLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/math.c -o $(OBJ_DIR)/math.o $(CFLAGS)
	$(CC) -c       $(SRC_DIR)/sub.c -o $(OBJ_DIR)/sub.o $(CFLAGS)
	$(CC) -c       $(SRC_DIR)/goodbye.c -o $(OBJ_DIR)/goodbye.o $(CFLAGS)

mk_shared:
	$(CC) -shared $(OBJ_DIR)/hello.o $(OBJ_DIR)/math.o -o $(LIB_SHARED)/lib$(LIB_NAME_SHARED).so

mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME_STATIC).a $(OBJ_DIR)/sub.o $(OBJ_DIR)/goodbye.o

install:
	cp -f $(LIB_SHARED)/lib$(LIB_NAME_SHARED).so /usr/lib
	cp -f $(LIB_STATIC)/lib$(LIB_NAME_STATIC).a /usr/lib

all: mk_objs mk_shared mk_static install
	$(CC)  $(OBJ_DIR)/main.o -L$(LIB_SHARED) -l$(LIB_NAME_SHARED) -L$(LIB_STATIC) -l$(LIB_NAME_STATIC) -o $(BIN_DIR)/use-shared-static-library
	
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED)/*
	rm -rf $(LIB_STATIC)/*
	rm -rf $(BIN_DIR)/*