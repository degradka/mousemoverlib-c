#include "mousemover.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/Xinerama.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

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

void moveMouseRel(int x, int y) {
    Display *dpy = opendisplay();

    Window root_window;
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask;
    XQueryPointer(dpy, DefaultRootWindow(dpy), &root_window, &root_window, &root_x, &root_y, &win_x, &win_y, &mask);

    XWarpPointer(dpy, None, DefaultRootWindow(dpy), 0, 0, 0, 0, root_x + x, root_y + y);
    XFlush(dpy);

    XCloseDisplay(dpy);
}

void dragMouseTo(int monitorNum, int x, int y, int buttonNum) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);

    if (buttonNum < 1 || buttonNum > 3) {
        errorandbail("ERROR: Invalid button\n");
    }

    XTestFakeButtonEvent(dpy, buttonNum, 1, CurrentTime);
    XFlush(dpy);
    XWarpPointer(dpy, None, RootWindow(dpy, DefaultScreen(dpy)), 0, 0, 0, 0, xineext->screens[monitorNum].x_org + x, xineext->screens[monitorNum].y_org + y);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, CurrentTime);
    XFlush(dpy);

    XCloseDisplay(dpy);
    XFree(xineext->screens);
    free(xineext);
}

void dragMouseRel(int x, int y, int buttonNum) {
    Display *dpy = opendisplay();

    if (buttonNum < 1 || buttonNum > 3) {
        errorandbail("ERROR: Invalid button\n");
    }

    Window root_window;
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask;
    XQueryPointer(dpy, DefaultRootWindow(dpy), &root_window, &root_window, &root_x, &root_y, &win_x, &win_y, &mask);

    XTestFakeButtonEvent(dpy, buttonNum, 1, CurrentTime);
    XFlush(dpy);
    XWarpPointer(dpy, None, DefaultRootWindow(dpy), 0, 0, 0, 0, root_x + x, root_y + y);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, CurrentTime);
    XFlush(dpy);

    XCloseDisplay(dpy);
}

void clickMouseButton(int buttonNum, float timeButtonHeld) {
    Display *dpy = opendisplay();

    if (buttonNum < 1 || buttonNum > 3) {
        errorandbail("ERROR: Invalid button\n");
    }

    if (timeButtonHeld <= 0) {
        timeButtonHeld = CurrentTime;
    }

    XTestFakeButtonEvent(dpy, buttonNum, 1, CurrentTime);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, timeButtonHeld);
    XFlush(dpy);

    XCloseDisplay(dpy);
}

void clickMouseButtonAt(int monitorNum, int x, int y, int buttonNum, float timeButtonHeld) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);

    if (buttonNum < 1 || buttonNum > 3) {
        errorandbail("ERROR: Invalid button\n");
    }

    if (timeButtonHeld <= 0) {
        timeButtonHeld = CurrentTime;
    }

    XWarpPointer(dpy, None, RootWindow(dpy, DefaultScreen(dpy)), 0, 0, 0, 0, xineext->screens[monitorNum].x_org + x, xineext->screens[monitorNum].y_org + y);
    XFlush(dpy);

    XTestFakeButtonEvent(dpy, buttonNum, 1, CurrentTime);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, timeButtonHeld);
    XFlush(dpy);

    XCloseDisplay(dpy);
    XFree(xineext->screens);
    free(xineext);
}

void doubleClickMouseButton(int buttonNum, float timeButtonHeld) {
    Display *dpy = opendisplay();

    if (buttonNum < 1 || buttonNum > 3) {
        errorandbail("ERROR: Invalid button\n");
    }

    if (timeButtonHeld <= 0) {
        timeButtonHeld = CurrentTime;
    }

    XTestFakeButtonEvent(dpy, buttonNum, 1, CurrentTime);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, timeButtonHeld);
    XFlush(dpy);

    XTestFakeButtonEvent(dpy, buttonNum, 1, timeButtonHeld);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, timeButtonHeld);
    XFlush(dpy);

    XCloseDisplay(dpy);
}

void doubleClickMouseButtonAt(int monitorNum, int x, int y, int buttonNum, float timeButtonHeld) {
    Display *dpy = opendisplay();
    struct XineramaExtension *xineext = queryxinerama(dpy, monitorNum);

    if (buttonNum < 1 || buttonNum > 3) {
        errorandbail("ERROR: Invalid button\n");
    }

    if (timeButtonHeld <= 0) {
        timeButtonHeld = CurrentTime;
    }

    XWarpPointer(dpy, None, RootWindow(dpy, DefaultScreen(dpy)), 0, 0, 0, 0, xineext->screens[monitorNum].x_org + x, xineext->screens[monitorNum].y_org + y);
    XFlush(dpy);

    XTestFakeButtonEvent(dpy, buttonNum, 1, CurrentTime);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, timeButtonHeld);
    XFlush(dpy);

    XTestFakeButtonEvent(dpy, buttonNum, 1, timeButtonHeld);
    XFlush(dpy);
    XTestFakeButtonEvent(dpy, buttonNum, 0, timeButtonHeld);
    XFlush(dpy);

    XCloseDisplay(dpy);
    XFree(xineext->screens);
    free(xineext);
}

void downMouseButton(int buttonNum, float delayBeforeAction) {
    Display *dpy = opendisplay();

    if (buttonNum < 1 || buttonNum > 3) {
        errorandbail("ERROR: Invalid button\n");
    }

    if (delayBeforeAction <= 0) {
        delayBeforeAction = CurrentTime;
    }

    XTestFakeButtonEvent(dpy, buttonNum, 1, delayBeforeAction);
    XFlush(dpy);

    XCloseDisplay(dpy);
}

void upMouseButton(int buttonNum, float delayBeforeAction) {
    Display *dpy = opendisplay();

    if (buttonNum < 1 || buttonNum > 3) {
        errorandbail("ERROR: Invalid button\n");
    }

    if (delayBeforeAction <= 0) {
        delayBeforeAction = CurrentTime;
    }

    XTestFakeButtonEvent(dpy, buttonNum, 0, delayBeforeAction);
    XFlush(dpy);

    XCloseDisplay(dpy);
}

void scrollMouse(int axis, int timesToScroll) {
    Display *dpy = opendisplay();

    if (axis < 4 || axis > 7) {
        errorandbail("ERROR: Invalid axis\n");
    }

    if (timesToScroll < 0) {
        timesToScroll = 0;
    }

    for (int i = 0; i < timesToScroll; i++) {
        XTestFakeButtonEvent(dpy, axis, 1, CurrentTime);
        XTestFakeButtonEvent(dpy, axis, 0, CurrentTime);
    }

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
