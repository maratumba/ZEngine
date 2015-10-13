CXXFLAGS=-Wall -Werror -Wextra -Wno-ignored-qualifiers -ggdb -lstdc++ -std=gnu++14 -L/usr/lib64
CXX=g++
CC=gcc
DEST=/usr/local/games
MAKE=make

SDLLIBS = $(shell sdl2-config --libs)
SDLINCS = $(shell sdl2-config --cflags)
RAPIDXMLINCS = -I./rapidxml

INCS = $(SDLINCS) $(RAPIDXMLINCS)

ZENGINE_OBJS = \
	czengine.o \
	cblitter.o \
	csdlblitter.o \
	cdrawable.o \
	csdlsprite.o \
	cspriteanim.o \
	csdlinputsink.o \
	ccharacter.o \
	cpolygon.o \
	ccollider.o \
	canimator.o \
	canimatorscale.o \
	canimatormove.o
ZENGINE_MAIN = zenginemain.o
ZENGINE_TARGET = ZEngine

 
Z2K_OBJS = cz2k.o cz2kboard.o cz2ktile.o
Z2K_MAIN = z2kmain.o
Z2K_TARGET = Z2k

all: $(ZENGINE_TARGET) $(Z2K_TARGET)

ZEngine: $(ZENGINE_OBJS) $(ZENGINE_MAIN)
	$(CXX) $(ZENGINE_MAIN) $(ZENGINE_OBJS) -o $(ZENGINE_TARGET) $(CXXFLAGS) $(SDLLIBS)
	mv $(ZENGINE_TARGET) ..

Z2k: $(Z2K_OBJS) $(ZENGINE_OBJS) $(Z2K_MAIN)
	$(CXX) $(Z2K_MAIN) $(ZENGINE_OBJS) $(Z2K_OBJS) -o $(Z2K_TARGET) $(CXXFLAGS) $(SDLLIBS)
	mv $(Z2K_TARGET) ..

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INCS) -DLINUX -c $<

%.o: %.c %.h
	$(CC) $(CCFLAGS) $(INCS) -DLINUX -c $<

clean:
	rm *.o ../$(ZENGINE_TARGET) ../$(Z2K_TARGET)
