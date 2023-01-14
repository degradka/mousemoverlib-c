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

void clickMouseButton(int buttonNum, float clickDelay, float buttonHoldTime) {
    Display *dpy = opendisplay();

    if (clickDelay <= 0) {
        clickDelay = CurrentTime;
    }

    if (buttonHoldTime <= 0) {
        buttonHoldTime = CurrentTime;
    }

    XTestFakeButtonEvent(dpy, buttonNum, 1, clickDelay);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, buttonHoldTime);
    XFlush(dpy);

    XCloseDisplay(dpy);
}

void clickMouseButtonAt(int monitorNum, int x, int y, int buttonNum, float clickDelay, float buttonHoldTime) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);

    if (clickDelay <= 0) {
        clickDelay = CurrentTime;
    }

    if (buttonHoldTime <= 0) {
        buttonHoldTime = CurrentTime;
    }

    XWarpPointer(dpy, None, RootWindow(dpy, DefaultScreen(dpy)), 0, 0, 0, 0, xineext->screens[monitorNum].x_org + x, xineext->screens[monitorNum].y_org + y);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 1, clickDelay);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, buttonHoldTime);
    XFlush(dpy);

    XCloseDisplay(dpy);
    XFree(xineext->screens);
    free(xineext);
}

void doubleClickMouseButton(int buttonNum, float firstClickDelay, float secondClickDelay, float buttonHoldTime) {
    Display *dpy = opendisplay();

    if (firstClickDelay <= 0) {
        firstClickDelay = CurrentTime;
    }

    if (secondClickDelay <= 0) {
        secondClickDelay = CurrentTime;
    }

    if (buttonHoldTime <= 0) {
        buttonHoldTime = CurrentTime;
    }

    XTestFakeButtonEvent(dpy, buttonNum, 1, firstClickDelay);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, buttonHoldTime);
    XFlush(dpy);

    XTestFakeButtonEvent(dpy, buttonNum, 1, secondClickDelay);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, buttonHoldTime);
    XFlush(dpy);

    XCloseDisplay(dpy);
}

int getScreenWidth(int monitorNum) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);
    int width = xineext->screens[monitorNum].width;
    XCloseDisplay(dpy);
    XFree(xineext->screens);
    free(xineext);
    return width;
}

int getScreenHeight(int monitorNum) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);
    int height = xineext->screens[monitorNum].height;
    XCloseDisplay(dpy);
    XFree(xineext->screens);
    free(xineext);
    return height;
}

int getMouseX(int monitorNum) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);

    Window root_return, child_return;
    int root_x_return, root_y_return;
    int win_x_return, win_y_return;
    unsigned int mask_return;
    XQueryPointer(dpy, RootWindow(dpy, DefaultScreen(dpy)), &root_return, &child_return, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return);

    int mouseX = win_x_return - xineext->screens[monitorNum].x_org;

    XFree(xineext->screens);
    free(xineext);
    XCloseDisplay(dpy);

    return mouseX;
}

int getMouseY(int monitorNum) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);

    Window root_return, child_return;
    int root_x_return, root_y_return;
    int win_x_return, win_y_return;
    unsigned int mask_return;
    XQueryPointer(dpy, RootWindow(dpy, DefaultScreen(dpy)), &root_return, &child_return, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return);

    int mouseY = win_y_return - xineext->screens[monitorNum].y_org;

    XFree(xineext->screens);
    free(xineext);
    XCloseDisplay(dpy);

    return mouseY;
}
