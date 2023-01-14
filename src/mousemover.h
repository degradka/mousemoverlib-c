#ifndef MOUSEMOVER_H
#define MOUSEMOVER_H

#ifdef __cplusplus
extern "C" {
#endif

#define LMB 1
#define MMB 2
#define RMB 3
#define MWU 4
#define MWD 5

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
 * @param buttonNum The mouse button
 * @param clickDelay Delay in ms before the click
 * @param buttonHoldTime Time in ms the button will be pressed after the click
 */
void clickMouseButton(int buttonNum, float clickDelay, float buttonHoldTime);

/**
 * @brief Trigger a mouse button click.
 *
 * @param monitorNum The number of your monitor
 * @param x X position
 * @param y Y position
 * @param buttonNum The mouse button
 * @param clickDelay Delay in ms before the click
 * @param buttonHoldTime Time in ms the button will be pressed after the click
 */
void clickMouseButtonAt(int monitorNum, int x, int y, int buttonNum, float clickDelay, float buttonHoldTime);

/**
 * @brief Trigger a mouse button double-click.
 *
 * @param buttonNum The mouse button
 * @param firstClickDelay Delay in ms before the first click
 * @param secondClickDelay Delay in ms before the second click
 * @param buttonHoldTime Time in ms each button will be pressed after the click
 */
void doubleClickMouseButton(int buttonNum, float firstClickDelay, float secondClickDelay, float buttonHoldTime);

/**
 * @brief Get screen width of a specified monitor.
 *
 * @param monitorNum The number of your monitor
 */
int getScreenWidth(int monitorNum);

/**
 * @brief Get screen height of a specified monitor.
 *
 * @param monitorNum The number of your monitor
 */
int getScreenHeight(int monitorNum);

/**
 * @brief Get cursor position X in a specified monitor.
 *
 * @param monitorNum The number of your monitor
 */
int getMouseX(int monitorNum);

/**
 * @brief Get cursor position Y in a specified monitor.
 *
 * @param monitorNum The number of your monitor
 */
int getMouseY(int monitorNum);

#ifdef __cplusplus
}
#endif

#endif
