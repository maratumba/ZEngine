CXXFLAGS=-Wall -Werror -Wextra -Wno-ignored-qualifiers -ggdb -lstdc++ -std=gnu++14 -L/usr/lib64
CXX=g++
CC=gcc
DEST=/usr/local/games
MAKE=make

SDLLIBS = $(shell sdl2-config --libs)
SDLINCS = $(shell sdl2-config --cflags)
SDLIMGLIBS = $(shell pkg-config SDL2_image --libs)
SDLIMGINCS = $(shell pkg-config SDL2_image --cflags)
RAPIDXMLINCS = -I./rapidxml

INCS = $(SDLINCS) $(SDLIMGINCS) $(RAPIDXMLINCS)

ZENGINE_OBJS = \
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
ZENGINE_TARGET = zengine.a

ZDEMO_OBJS = czengine.o
ZDEMO_MAIN = zenginemain.o
ZDEMO_TARGET = ZEngine

Z2K_OBJS = cz2k.o cz2kboard.o cz2ktile.o
Z2K_MAIN = z2kmain.o
Z2K_TARGET = Z2k

all: $(ZDEMO_TARGET) $(Z2K_TARGET)

zengine.a: $(ZENGINE_OBJS)
	ar cr $(ZENGINE_TARGET) $(ZENGINE_OBJS)

ZEngine: $(ZENGINE_TARGET) $(ZDEMO_OBJS) $(ZDEMO_MAIN)
	$(CXX) $(ZDEMO_MAIN) $(ZDEMO_OBJS) $(ZENGINE_TARGET) -o $(ZDEMO_TARGET) $(CXXFLAGS) $(SDLLIBS) $(SDLIMGLIBS)
	mv $(ZDEMO_TARGET) ..

Z2k: $(ZENGINE_TARGET) $(Z2K_OBJS) $(Z2K_MAIN)
	$(CXX) $(Z2K_MAIN) $(Z2K_OBJS) $(ZENGINE_TARGET) -o $(Z2K_TARGET) $(CXXFLAGS) $(SDLLIBS) $(SDLIMGLIBS)
	mv $(Z2K_TARGET) ..

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INCS) -DLINUX -c $<

%.o: %.c %.h
	$(CC) $(CCFLAGS) $(INCS) -DLINUX -c $<

clean:
	rm *.o *.a ../$(ZDEMO_TARGET) ../$(Z2K_TARGET)
