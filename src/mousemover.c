#include "mousemover.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/Xinerama.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static void errorandbail(char *format, ...) {
    va_list list;
    va_start(list, format);
    vfprintf(stderr, format, list);
    va_end(list);
    exit(1);
}

static Display *opendisplay(void) {
    Display *dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        errorandbail("ERROR: Cannot open display\n");
        return NULL;
    }
    return dpy;
}

struct XineramaExtension {
    int eventbase;
    int errorbase;
    int monitornum;
    int numscreens;
    XineramaScreenInfo *screens;
};

static struct XineramaExtension *queryxinerama(Display *dpy, int monitornum) {
    struct XineramaExtension *ext = malloc(sizeof(struct XineramaExtension));
    ext->monitornum = monitornum;

    if (!XineramaQueryExtension(dpy, &ext->eventbase, &ext->eventbase)) {
        errorandbail("ERROR: Xinerama extension not available\n");
        return NULL;
    }

    ext->screens = XineramaQueryScreens(dpy, &ext->numscreens);
    if (monitornum < 0 || monitornum >= ext->numscreens) {
        errorandbail("ERROR: Invalid monitor number\n");
        return NULL;
    }
    return ext;
}

void moveMouseTo(int monitorNum, int x, int y) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);

    XWarpPointer(dpy, None, RootWindow(dpy, DefaultScreen(dpy)), 0, 0, 0, 0, xineext->screens[monitorNum].x_org + x, xineext->screens[monitorNum].y_org + y);

    XFlush(dpy);
    XCloseDisplay(dpy);
    XFree(xineext->screens);
    free(xineext);
}

void clickMouse(int monitorNum, int buttonNum, float clickDelay) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);

    if (buttonNum < 1 || buttonNum > 5) {
        errorandbail("ERROR: Invalid button number\n");
    }

    if (clickDelay <= 0) {
        clickDelay = CurrentTime;
    }

    XTestFakeButtonEvent(dpy, buttonNum, 1, clickDelay);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, clickDelay);
    XFlush(dpy);

    XCloseDisplay(dpy);
    XFree(xineext->screens);
    free(xineext);
}
