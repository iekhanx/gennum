#!/bin/bash
# ------------------------------->Makefile<-------------------------------
#      Author : Imran Khan
#        Note : Copyright (c) 2020 by Imran Khan
#
#      Date   : Sat 12 Mar 16:37:30 GMT 2022
#
# This is a TEMPLATE Makefile for compiling C/C++ program, which require
# to modify for the source file(s) and executable binary file(s) name;
# also to adjust the linking libraries as per requirements.
#  ------------------------------------------------------------------------
#
#
ifeq ($(ARCH),arm)
	CC=arm-linux-gnueabi-gcc
	CXX=arm-linux-gnueabi-g++
	CXXFLAGS=-g3 -Wall -std=c++20a
	CFLAGS=-g3 -Wall -pedantic
	LD_FLAGS=
	MSG="** Binary generated for ARM compatible CPU **"
	COMPILER=$(shell $(CC) --version)
else
	CC=clang 
	CXX=clang++
	CXXFLAGS=-g3 -Wall -std=c++2a
	CFLAGS=-g3 -Wall -pedantic `pkg-config --cflags xpm`
	LD_FLAGS=`pkg-config --libs xpm`
	MSG="Binary generated for i986 compatible Intel's CPU"
	COMPILER=$(shell $(CC) --version)
endif

#256 color codes
pink="\033[38;5;206m"
WonltB="\033[48;5;57m"
RonltB="\033[38;5;206;48;5;57m"
Bwhite="\033[38;5;16m"
NORMAL="\\033[0m"
BYellow="\e[1;33;1m"
BoldOn="\\033[1m"
BoldOff="\\033[21m"

#Set up Pkg-config LOOK-UP TABLE FOR REFERRENCE ONLY
#X11_PKG=$(shell pkg-config X11 --cflags --libs)
#SQLITE_PKG = $(shell pkg-config sqlite3 --cflags --libs)
#OPENGL_PKG = $(shell pkg-config opengl --cflags --libs)
#GLFW_PKG = $(shell pkg-config glfw3 --cflags --libs)
#Refer to main Makefile for more pkg-config packages for various dev tool

#Version for binary file
VERSION_MAJOR := 1
VERSION_MINOR := 0
VERSION_PATCH := 1
VERSION_RC := 0
BIN_VERSION_STRING=$(shell printf '%d.%d' $(VERSION_MAJOR) $(VERSION_MINOR))

#Setup Compiling Flags and Linking with libraries cflags ldflags etc
PREFIX=$(HOME)/bin
INCLUDES=
LIBS=
DEBUG_INFO="Debug info included in the binary executable"

BIN=okCanBtn

#Define source file(s)
SRC=src
OBJ=obj

SRCS=$(shell find $(SRC) -name *.cpp -or -name *.c -or -name *.s)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
HDRS=$(wildcard $(SRC)/*.h)
DEPS=$(OBJS:.o=d)

#Defined main target build binary executable
ifeq ($(ARCH),arm)
	TARGET=${BIN}_arm_$(BIN_VERSION_STRING)
else
	TARGET=${BIN}_x64_$(BIN_VERSION_STRING)
endif


#define clean procedure
.PHONY:    depend clean

#Now kick off the compile and link process
All:    $(TARGET)
	@echo $(wonltB)Program compiled with: $(NORMAL)
	@echo $(BYellow)
	@echo $(COMPILER)
	@echo $(NORMAL)
	@echo $(pink)with OS $(shell uname -s -r -o -m) $(NORMAL)
	@echo $(RonltB)$(DEBUG_INFO) $(NORMAL)
	@echo $(BYellow) $(MSG) $(NORMAL)
	@echo $(pink) $(SRCS) $(NORMAL)

$(TARGET):  $(OBJS)  $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LD_FLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ)
	  $(CXX) $(CXXFLAGS) -c $< -o $@


$(OBJ)/%.o: $(SRC)/%.c $(OBJ)
	  $(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	  mkdir -p $@
	  #Do some housekeeping procedure

clean:
	  @echo $(pink) Cleaning up object and binary files.... $(NORMAL)
	  $(RM) -rf $(OBJ)
	  $(RM) $(TARGET)

install:
	   @echo $(pink) Copying files from ... $(NORMAL)
	   cp -v $(TARGET) $(PREFIX)

depend:    $(SRCS)
	   makedepend $(INCLUDES)

#----------------------> End of Makefile <--------------------------
