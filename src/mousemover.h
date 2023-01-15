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
#define MWL 6
#define MWR 7

/**
 * @brief Move the mouse cursor into the specified position on a specified monitor.
 * 
 * @param monitorNum The number of your monitor
 * @param x X position
 * @param y Y position
 */
void moveMouseTo(int monitorNum, int x, int y);

/**
 * @brief Move the mouse cursor relatively to the cursor by specified amount of x and y.
 *
 * @param x X position
 * @param y Y position
 */
void moveMouseRel(int x, int y);

/**
 * @brief Drag the mouse cursor into the specified position on a specified monitor.
 *
 * @param monitorNum The number of your monitor
 * @param x X position
 * @param y Y position
 * @param buttonNum The mouse button
 */
void dragMouseTo(int monitorNum, int x, int y, int buttonNum);

/**
 * @brief Drag the mouse cursor relatively to the cursor by specified amount of x and y.
 *
 * @param x X position
 * @param y Y position
 * @param buttonNum The mouse button
 */
void dragMouseRel(int x, int y, int buttonNum);

/**
 * @brief Trigger a mouse button click.
 * 
 * @param buttonNum The mouse button
 * @param timeButtonHeld Time the mouse button will be held after click
 */
void clickMouseButton(int buttonNum, float timeButtonHeld);

/**
 * @brief Trigger a mouse button click at some position.
 *
 * @param monitorNum The number of your monitor
 * @param x X position
 * @param y Y position
 * @param buttonNum The mouse button
 * @param timeButtonHeld Time the mouse button will be held after click
 */
void clickMouseButtonAt(int monitorNum, int x, int y, int buttonNum, float timeButtonHeld);

/**
 * @brief Trigger a mouse button double-click.
 *
 * @param buttonNum The mouse button
 * @param timeButtonHeld Time the mouse button will be held after click
 */
void doubleClickMouseButton(int buttonNum, float timeButtonHeld);

/**
 * @brief Trigger a mouse button double-click at some position.
 *
 * @param monitorNum The number of your monitor
 * @param x X position
 * @param y Y position
 * @param buttonNum The mouse button
 * @param timeButtonHeld Time the mouse button will be held after click
 */
void doubleClickMouseButtonAt(int monitorNum, int x, int y, int buttonNum, float timeButtonHeld);

/**
 * @brief Trigger a mouse button pressed.
 *
 * @param buttonNum The mouse button
 * @param delayBeforeAction The delay before the action will happen
 */
void downMouseButton(int buttonNum, float delayBeforeAction);

/**
 * @brief Trigger a mouse button up.
 *
 * @param buttonNum The mouse button
 * @param delayBeforeAction The delay before the action will happen
 */
void upMouseButton(int buttonNum, float delayBeforeAction);

/**
 * @brief Trigger a mouse to scroll.
 *
 * @param axis The scroll axis
 * @param timesToScroll The amount of times the mouse will scroll
 */
void scrollMouse(int axis, int timesToScroll);

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
