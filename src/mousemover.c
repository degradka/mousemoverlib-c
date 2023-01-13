#include "mousemover.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/Xinerama.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static void errorandbail(char *format, ...) {
    va_list list;
    va_start(list, format);
    vfprintf(stderr, format, list);
    va_end(list);
    exit(1);
}

void moveMouseTo(int monitorNum, int x, int y) {
    Display *dpy;
    dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
        errorandbail("Cannot open display\n");
        return;
    }

    int event_base, error_base;
    if (!XineramaQueryExtension(dpy, &event_base, &error_base)) {
        errorandbail("Error: Xinerama extension not available\n");
        return;
    }

    int numScreens;
    XineramaScreenInfo *screens = XineramaQueryScreens(dpy, &numScreens);
    if (monitorNum < 0 || monitorNum >= numScreens) {
        errorandbail("Error: Invalid monitor number\n");
        return;
    }

    XWarpPointer(dpy, None, RootWindow(dpy, DefaultScreen(dpy)), 0, 0, 0, 0, screens[monitorNum].x_org + x, screens[monitorNum].y_org + y);

    XFlush(dpy);
    XCloseDisplay(dpy);
    XFree(screens);
}

void clickMouse(int monitorNum, int buttonNum, float clickDelay) {
    Display *dpy;
    dpy = XOpenDisplay(NULL);

    if (dpy == NULL) {
        errorandbail("Cannot open display\n");
        return;
    }

    int event_base, error_base;
    if (!XineramaQueryExtension(dpy, &event_base, &error_base)) {
        errorandbail("Error: Xinerama extension not available\n");
        return;
    }

    int numScreens;
    XineramaScreenInfo *screens = XineramaQueryScreens(dpy, &numScreens);
    if (monitorNum < 0 || monitorNum >= numScreens) {
        errorandbail("Error: Invalid monitor number\n");
        return;
    }

    if (clickDelay <= 0) {
        clickDelay = CurrentTime;
    }

    XTestFakeButtonEvent(dpy, buttonNum, 1, clickDelay);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, clickDelay);
    XFlush(dpy);

    XCloseDisplay(dpy);
    XFree(screens);
}
