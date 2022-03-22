#!/bin/bash-- DELETE THIS LINE IN MAKEFILE --
# ------------------------------->Makefile<-------------------------------
#      Author : Imran Khan
#        Note   : Copyright (c) 2020 by Imran Khan
#
#    Date   : Sun  8 Nov 19:46:10 GMT 2020
#
## This is a TEMPLATE Makefile for compiling C/C++ program, which require
# to modify for the source file(s) and executable binary file(s) name; 
# # also to adjust the linking libraries as per requirements.
# #------------------------------------------------------------------------
#
ifdef ARCH
	$(info ARCH defined)
	CC          = arm-linux-gnueabi-gcc
	CXXFLAGS    = -Wall -g -std=c++2a -O2
	CFLAGS      = -static -Wall -pedantic -O2 -g
	MSG         = "** Binary generated for ARM compatible CPU **"
	COMPILER    = $(shell arm-linux-gnueabi-g++ --version)
else
	CC          = gcc
	CXXFLAGS    = -Wall -std=c++2a -O2 -g
	CFLAGS      = -Wall -g -Wstrict-prototypes -ansi -Wextra
	MSG         = "Binary generated for i686 compatible Intel's CPU"
	COMPILER    = $(shell gcc --version)
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

#Set up Pkg-config files for compiling, linking etc
X11_PKG=$(shell pkg-config X11 --cflags --libs)
SQLITE_PKG = $(shell pkg-config sqlite3 --cflags --libs)
OPENGL_PKG = $(shell pkg-config opengl --cflags --libs)
GLFW_PKG = $(shell pkg-config glfw3 --cflags --libs)
#Refer to main Makefile for more pkg-config packages for various dev tool

#Version for binary file
VERSION_MAJOR := 1
VERSION_MINOR := 0
VERSION_PATCH := 1
VERSION_RC := 0
BIN_VERSION_STRING=$(shell printf '%d.%d' $(VERSION_MAJOR) $(VERSION_MINOR))

#Setup Compiling Flags and Linking with libraries cflags ldflags etc
PREFIX      =  $(HOME)/bin
INCLUDES    = -I/usr/local/include
LIBS        = -L/usr/local/lib -lX11 -lXpm -lXext -lm -Wl,-rpath=/usr/local/lib
LDFLAGS     = -g
DEBUG_INFO  = "Debug info included in the binary executable"

EXE    = xLib_Tut15

#Define source file(s) list
SRCS    = mainloop.c app.c button.c getResources.c gradient.c menubar.c menu.c \
		  xc2b.c appOption.c

OBJS    = $(SRCS:.c=.o)

#Defined main target build binary executable
ifeq ($(ARCH),arm)
	TARGET    = ${EXE}_arm_$(BIN_VERSION_STRING)
else
	TARGET    = ${EXE}_i686_$(BIN_VERSION_STRING)
endif


#define clean procedure
.PHONY:    depend clean

#Now kick off the compile and link process
All:    $(TARGET)
	@echo $(wonltB)Program compiled with: $(NORMAL)
	@echo $(BYellow)
	@echo `gcc --version`
	@echo $(NORMAL)
	@echo $(pink)with OS $(shell uname -s -r -o -m) $(NORMAL)
	@echo $(RonltB)$(DEBUG_INFO) $(NORMAL)
	@echo $(BYellow) $(MSG) $(NORMAL)
	@echo $(pink) $(SRCS) $(NORMAL)

$(TARGET):    $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(LDFLAGS) -o $(TARGET)

#Define suffix replacement rules for building o from c sources
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#Do some housekeeping procedure
clean:
	    @echo $(pink) Cleaning up object and binary files.... $(NORMAL)
		     $(RM) *.o *~ $(TARGET)

install:
	    @echo $(pink) Copying files from ... $(NORMAL)
		cp -v $(TARGET) $(PREFIX)

depend:     $(SRCS)
	     makedepend $(INCLUDES)

#----------------------> End of Makefile <--------------------------
