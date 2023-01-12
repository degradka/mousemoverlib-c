#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/extensions/Xinerama.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Error: Please specify the screen number, x and y coordinates as command-line arguments\n");
        return 1;
    }
    int screenNum = atoi(argv[1]);
    int x = atoi(argv[2]);
    int y = atoi(argv[3]);
    Display *dpy;
    dpy = XOpenDisplay(NULL);

    if(dpy == NULL) {
        printf("Cannot open display\n");
        return 1;
    }

    int event_base, error_base;
    if (!XineramaQueryExtension(dpy, &event_base, &error_base)) {
        printf("Error: Xinerama extension not available\n");
        return 1;
    }

    int numScreens;
    XineramaScreenInfo *screens = XineramaQueryScreens(dpy, &numScreens);
    if (screenNum < 0 || screenNum >= numScreens) {
        printf("Error: Invalid screen number\n");
        return 1;
    }

    XWarpPointer(dpy, None, RootWindow(dpy, DefaultScreen(dpy)), 0, 0, 0, 0, screens[screenNum].x_org + x, screens[screenNum].y_org + y);
    XFlush(dpy);
    XCloseDisplay(dpy);
    XFree(screens);
    return 0;
}
