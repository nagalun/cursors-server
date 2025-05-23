LOBJS   = level/Level.cpp level/LevelObject.cpp level/LevelManager.cpp
LOOBJS := $(shell find level/objects/ -name '*.cpp')
MOBJS   = misc/FixedArray.cpp misc/IdSys.cpp misc/Util.cpp limiter.cpp
OBJS    = main.cpp Server.cpp Cursor.cpp

UWS = uWebSockets/src/Extensions.cpp uWebSockets/src/Group.cpp uWebSockets/src/Epoll.cpp uWebSockets/src/Networking.cpp uWebSockets/src/Hub.cpp uWebSockets/src/Node.cpp uWebSockets/src/WebSocket.cpp uWebSockets/src/HTTPSocket.cpp uWebSockets/src/Socket.cpp

ALLOBJS = $(OBJS) $(MOBJS) $(LOBJS) $(LOOBJS) $(UWS)

CC = g++

COMPILER_FLAGS = -Wall -std=c++17
REL_CFLAGS = -O2
DBG_CFLAGS = -Og -g

LIBS = -I ./uWebSockets/src/ -lcrypto -lssl -lz

OUT = out

all : $(ALLOBJS)
	$(CC) $(ALLOBJS) $(COMPILER_FLAGS) $(REL_CFLAGS) $(LIBS) -o $(OUT)

g : $(ALLOBJS)
	$(CC) $(ALLOBJS) $(COMPILER_FLAGS) $(DBG_CFLAGS) $(LIBS) -o $(OUT)

