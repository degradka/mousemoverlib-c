#ifndef MOUSEMOVER_H
#define MOUSEMOVER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Move the mouse cursor into the specified position on a specified monitor.
 * 
 * @param monitorNum The number of your monitor
 * @param x X position
 * @param y Y position
 */
void moveMouseTo(int monitorNum, int x, int y);

/**
 * @brief Trigger a mouse button click.
 * 
 * @param monitorNum The number of your monitor
 * @param buttonNum The mouse button
 * @param clickDelay Delay between the current click and the next click
 */
void clickMouse(int monitorNum, int buttonNum, float clickDelay);

#ifdef __cplusplus
}
#endif

#endif
