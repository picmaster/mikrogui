#!/usr/bin/env python
#
# Copyright (C) 2016 Nikolay Dimitrov <picmaster@mail.bg>
#
# SPDX-License-Identifier: BSD-3-Clause
#
# Tiny GUI/resource compiler for the mikrogui project

import sys, json, string, glob, os
from datetime import *

VERSION = "0.1.0"
URL = "https://github.com/picmaster/mikrogui"

DISPLAY = {"w": -1, "h": -1}

# Counters for object instance IDs
obj_ids = {"image": -1, "rect": -1}

def timestamp():
    return datetime.now().strftime("%d.%B.%Y %H:%M:%S")

def get_next_object_id(obj_type):
    obj_ids[obj_type] += 1
    return obj_ids[obj_type]

def reset_object_ids():
    obj_ids["image"] = 0
    obj_ids["rect"] = 0

def fill_text_template(tmpl, params):
    t = string.Template(tmpl)
    return t.safe_substitute(params)

def fill_template(tmpl, code, params):
    print "Reading template: %s" % tmpl
    t = string.Template(open(tmpl).read())

    print "Writing generated code: %s" % code
    open(code, "w").write(t.safe_substitute(params))
    #open(code, "w").write(t.substitute(params))

def gen_framebuffer_code(args):
    global DISPLAY

    display_name = args[1]
    display_conf = "configs/display/%s.conf" % display_name
    print "Reading display configuration: %s" % display_conf
    display = json.load(open(display_conf))["display"]

    w, h, bpp, pixfmt = display["width"], display["height"], display["bpp"], display["pixel_format"]
    pixels = w * h
    DISPLAY["w"], DISPLAY["h"] = w, h

    if bpp in range(1, 9):
        bytes = pixels
        pixtype = "uint8_t"
    elif bpp in range(8, 17):
        bytes = pixels * 2
        pixtype = "uint16_t"
    elif bpp > 16 and bpp <= 24:
        bytes = pixels * 3
        pixtype = "uint32_t"
    elif bpp > 24 and bpp <= 32:
        bytes = pixels * 4
        pixtype = "uint32_t"
    else:
        bytes = 0
        pixtype = ""

    pixmask = "%s" % hex(pow(2, bpp) - 1)

    params = {"disp_conf": "%s.conf" % display_name, "guic_info": "guic.py v%s" % VERSION, "timestamp": timestamp()}
    params["bytes"] = bytes
    params["pixels"] = pixels
    params["width"] = w
    params["height"] = h
    params["bpp"] = bpp
    params["pixfmt"] = pixfmt
    fill_template("templates/framebuffer/framebuffer_gen.c.tmpl", "src/framebuffer_gen.c", params)

    params = {"disp_conf": "%s.conf" % display_name, "guic_info": "guic.py v%s" % VERSION, "timestamp": timestamp()}
    params["type"] = pixtype
    params["mask"] = pixmask
    fill_template("templates/framebuffer/framebuffer_gen.h.tmpl", "include/framebuffer_gen.h", params)

def gen_image_instance(form_name, image):
    #print "image: %s" % image
    t = open("templates/form/image_def.tmpl").read()
    p = {"form": form_name, "id": get_next_object_id("image")}
    p["x"] = image["geometry"]["x"]
    p["y"] = image["geometry"]["y"]
    p["w"] = image["geometry"]["w"]
    p["h"] = image["geometry"]["h"]
    p["pixmap_resource"] = image["path"]
    return fill_text_template(t, p)

def gen_rect_instance(form_name, rect):
    t = open("templates/form/rect_def.tmpl").read()
    p = {"form": form_name, "id": get_next_object_id("rect")}
    p["x"] = rect["geometry"]["x"]
    p["y"] = rect["geometry"]["y"]
    p["w"] = rect["geometry"]["w"]
    p["h"] = rect["geometry"]["h"]
    p["color"] = rect["color"]
    return fill_text_template(t, p)

def gen_widget_array(form_name, widgets):
    t1 = open("templates/form/widget_array.tmpl").read()
    t2 = open("templates/form/widget_array_element.tmpl").read()
    p = {"form": form_name}

    image_id = 1
    rect_id = 1
    widget_array_elements = ""
    for widget in widgets:
        if widget["type"] == "image":
            widget_array_elements += fill_text_template(t2, {"form": form_name, "widget": "image%d" % image_id})
            image_id += 1
        elif widget["type"] == "rect":
            widget_array_elements += fill_text_template(t2, {"form": form_name, "widget": "rect%d" % rect_id})
            rect_id += 1
    p["widget_array_elements"] = widget_array_elements

    return fill_text_template(t1, p)

def gen_forms_code(args):
    for form_conf in glob.iglob("forms/*.form"):
        reset_object_ids()
        form_name = os.path.splitext(os.path.basename(form_conf))[0]

        print "\nReading GUI form: %s" % form_conf
        form = json.load(open(form_conf))["form"]

        params = dict()
        params["form_conf"] = form_conf
        params["guic_info"] = "guic.py v%s" % VERSION
        params["timestamp"] = timestamp()
        params["form_name"] = form_name
        params["form_x"] = 0
        params["form_y"] = 0
        params["form_w"] = DISPLAY["w"]
        params["form_h"] = DISPLAY["h"]

        form_event_prototypes = ""
        input_event_prototypes = ""
        handlers_def = ""
        if "event_handlers" in form:
            handlers = form["event_handlers"]
            t1 = open("templates/form/form_event_prototype.tmpl").read()
            t2 = open("templates/form/input_event_prototype.tmpl").read()
            t3 = open("templates/form/event_handler_def.tmpl").read()

            for handler in handlers:
                p = {"form": form_name, "handler": handler}
                if handler in ("enter", "leave"):
                    form_event_prototypes += fill_text_template(t1, p)
                elif handler in ("handle_input"):
                    input_event_prototypes += fill_text_template(t2, p)
                handlers_def += fill_text_template(t3, p)

        params["form_event_prototypes"] = form_event_prototypes
        params["input_event_prototypes"] = input_event_prototypes
        params["handlers_def"] = handlers_def

        image_defs = ""
        rect_defs = ""
        image_decls = ""
        rect_decls = ""
        if "widgets" in form:
            widgets = form["widgets"]
            for widget in widgets:
                if widget["type"] == "image":
                    image_defs += gen_image_instance(form_name, widget)
                    #image_decls += 
                elif widget["type"] == "rect":
                    rect_defs += gen_rect_instance(form_name, widget)

        params["image_defs"] = image_defs
        params["rect_defs"] = rect_defs
        params["widget_array"] = gen_widget_array(form_name, widgets)

        t = open("templates/form/form_children.tmpl").read()
        params["children"] = fill_text_template(t, {"form": form_name})

        fill_template("templates/form/form_{name}_gen.c.tmpl", "src/form_%s_gen.c" % form_name, params)

def main(args):
    print "guic.py v%s\n" % VERSION
    gen_framebuffer_code(args)
    gen_forms_code(args)
    return

    fonts = list()
    images = list()

    form_file = open(args[1])
    form = json.load(form_file)

    widgets = form["form"]["widgets"]
    print "Found %d widgets:\n" % len(widgets)

    for w in widgets:
        print "%s: %s" % (w["id"], w["type"])

    # Scan for resources
    for w in widgets:
        if w["type"] == "label":
            fonts.append(w["font"])

        if w["type"] == "image":
            images.append(w["path"])

    # Remove duplicates
    fonts = list(set(fonts))
    images = list(set(images))

    print "\nResource list:"
    print "\tFonts: %s" % fonts
    print "\tImages: %s" % images

    generate_bin_arrays(fonts + images)

if __name__ == "__main__":
    main(sys.argv)

def gen_bin_arrays(in_files, out_file_basename = "resources_gen"):
    f = open("%s.h" % out_file_basename, "w")
    f.write("// Do not edit this file! It was automatically generated by GUIC.\n\n")
    f.write("typedef enum resource_id_e\n{\n")
    f.write("    RES_ID_INVALID = 0,\n")

    for i in in_files:
        f.write("    RES_ID_%s,\n" % i)

    f.write("    RES_ID_MAX\n")
    f.write("} resource_id_t;\n\n")
    f.close()
