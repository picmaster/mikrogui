APP=example
CC=gcc
CFLAGS=-O0 -ggdb -Wall -Wstrict-prototypes -Iinclude `pkg-config --cflags sdl`
SLIBS=`pkg-config --libs sdl`

OBJS=\
 src/framebuffer.o \
 src/framebuffer_gen.o \
 src/image.o \
 src/input.o \
 src/mikrogui.o \
 src/platforms/linux_sdl.o \
 src/rect.o \
 src/resources.o \
 src/text.o \
 src/widget.o

all: $(OBJS) examples
#	$(CC) -o $(APP) $(OBJS) $(SLIBS)

examples: framebuffer

framebuffer:
	$(CC) -o examples/framebuffer_example $(OBJS) $(SLIBS)

clean:
	rm -f $(APP) include/*_gen.[ch] src/*.o src/*_gen.[ch] src/platforms/*.o

rebuild: clean all

