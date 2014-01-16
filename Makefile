CXXFLAGS=-Wall -Werror -O2 -ggdb -lstdc++ -std=gnu++11
CXX=g++
CC=gcc
DEST=/usr/local/games
MAKE=make

SDLLIBS = $(shell sdl2-config --libs)
SDLINCS = $(shell sdl2-config --cflags)
RAPIDXMLINCS = -I./rapidxml

INCS = $(SDLINCS) $(RAPIDXMLINCS)

OBJS=czengine.o cblitter.o csdlblitter.o cdrawable.o csdlsprite.o \
	 cspriteanim.o csdlinputsink.o ccharacter.o cpolygon.o ccollider.o

TARGET=ZEngine

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INCS) -DLINUX -c $<

%.o: %.c %.h
	$(CC) $(CCFLAGS) $(INCS) -DLINUX -c $<

ZEngine: $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS) $(SDLLIBS)

all: $(TARGET)

clean:
	rm *.o $(TARGET)
