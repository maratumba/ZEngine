CXXFLAGS=-Wall -Werror -O2 -ggdb -lstdc++ -std=gnu++11
CXX=g++
CC=gcc
DEST=/usr/local/games
MAKE=make
#ALLEGROLIBS = $(shell pkg-config --libs allegro-5.0)
#ALLEGROINCS = $(shell pkg-config --cflags allegro-5.0) 
SDLLIBS = $(shell sdl2-config --libs)
SDLINCS = $(shell sdl2-config --cflags)

OBJS=czengine.o cblitter.o csdlblitter.o cdrawable.o csdlsprite.o cspriteanim.o csdlinputable.o
TARGET=ZEngine

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(SDLINCS) -DLINUX -c $<

%.o: %.c %.h
	$(CC) $(CCFLAGS) $(SDLINCS) -DLINUX -c $<

all: $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS) $(SDLLIBS)

clean:
	rm *.o $(TARGET)
