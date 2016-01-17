## What is mikrogui?

A small graphics library for embedded systems (mostly Cortex-M devices).

## Features

- modular, extensible design
- provides access to the raster display via framebuffer, allowing the drawing
  of graphics objects like dots, lines, rectangles, images, monospaced font
  rendering
- fast rendering in "deferred" mode, which means all drawing happens against
  the framebuffer, and the framebuffer is flushed only once per frame to the
  platform display
- a menu system, capable of handling input events and drawing widgets. The 
- simple and small source code, allowing easy code review
- small resource usage on the target (TODO: Add specific numbers from the ARM
  build)
- code generation based on formal specifications

## Dependencies

- mikrogui requires a C99-capable compiler (which unfortunately excludes Keil
  MDK-ARM). So far I've tested with gcc-4.7.2 on Linux.
- Python 2.7. I've tested the code generation on Linux and Windows 7.

## How to compile

```
git clone https://github.com/picmaster/mikrogui.git
cd mikrogui
tools/guic.py 320x240_8bpp
make
```

## Code generator

The code generator (tools/guic.py) is used to convert formal specifications to
source code. My initial intention was to automatically generate all the
straight-forward code that doesn't need human creativity, thus reducing the
error-prone work, and also speeding-up re-designs. The code generator is used
to generate:
- hardware-specific framebuffer (framebuffer_gen.[ch])
- GUI forms instances (form_*_gen.[ch])
- resources (still TBD)

The code generator uses text templates (located in "templates" directory) to
generate source code. I intentionally try to avoid fuzzy preprocessor hacks as
much as possible, in order to improve code readability.

## Bug tracking

All issues are being handled at [the project's "Issues" page](https://github.com/picmaster/mikrogui/issues).
