#APP=framebuffer
APP=mikrogui
CC=gcc
CFLAGS=-O0 -ggdb -Wall -Wstrict-prototypes -I. `pkg-config --cflags sdl`
SLIBS=`pkg-config --libs sdl`

OBJS=framebuffer_gen.o framebuffer.o mikrogui.o platforms/linux/linux_backend.o

all: $(OBJS)
	$(CC) -o $(APP) $(OBJS) $(SLIBS)

clean:
	rm -f *.o *_gen.[ch] $(APP)

rebuild: clean all

