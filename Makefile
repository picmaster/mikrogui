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
 src/platforms/generic_sdl.o \
 src/progressbar.o \
 src/rect.o \
 src/resources.o \
 src/text.o \
 src/widget.o

all: $(OBJS) examples
#	$(CC) -o $(APP) $(OBJS) $(SLIBS)

examples: framebuffer rect progressbar

framebuffer: examples/framebuffer_example.o
	$(CC) -o examples/framebuffer_example $(OBJS) examples/framebuffer_example.o $(SLIBS)

rect: examples/rect_example.o
	$(CC) -o examples/rect_example $(OBJS) examples/rect_example.o $(SLIBS)

progressbar: examples/progressbar_example.o
	$(CC) -o examples/progressbar_example $(OBJS) examples/progressbar_example.o $(SLIBS)

clean:
	rm -f $(APP) include/*_gen.[ch] src/*.o src/*_gen.[ch] src/platforms/*.o
	rm -f examples/*_example

rebuild: clean all

