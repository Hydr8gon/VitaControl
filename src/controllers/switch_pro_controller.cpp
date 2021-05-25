#include <psp2kern/ctrl.h>

#include "switch_pro_controller.h"

SwitchProController::SwitchProController(uint32_t mac0, uint32_t mac1, int port): Controller(mac0, mac1, port)
{
    // Prepare a write request to switch to standard mode
    static uint8_t report[12] = {};
    report[0]  = 0x01;
    report[1]  = 0x01;
    report[10] = 0x03;
    report[11] = 0x30;

    // Send the write request
    requestReport(HID_REQUEST_WRITE, report, sizeof(report));
}

void SwitchProController::processReport(uint8_t *buffer, size_t length)
{
    // Only process the report if it's of the right type
    if (buffer[0] != 0x30)
        return;

    // Interpret the data as an input report
    SwitchProReport0x30 *report = (SwitchProReport0x30*)buffer;

    // Clear the old control data
    controlData.buttons = 0;

    // Map the face buttons
    if (report->b) controlData.buttons |= SCE_CTRL_CROSS;
    if (report->a) controlData.buttons |= SCE_CTRL_CIRCLE;
    if (report->x) controlData.buttons |= SCE_CTRL_TRIANGLE;
    if (report->y) controlData.buttons |= SCE_CTRL_SQUARE;

    // Map the D-pad
    if (report->up)    controlData.buttons |= SCE_CTRL_UP;
    if (report->right) controlData.buttons |= SCE_CTRL_RIGHT;
    if (report->down)  controlData.buttons |= SCE_CTRL_DOWN;
    if (report->left)  controlData.buttons |= SCE_CTRL_LEFT;

    // Map the triggers
    if (report->l)      controlData.buttons |= SCE_CTRL_L1;
    if (report->r)      controlData.buttons |= SCE_CTRL_R1;
    if (report->zl)     controlData.buttons |= SCE_CTRL_LTRIGGER;
    if (report->zr)     controlData.buttons |= SCE_CTRL_RTRIGGER;
    if (report->stickL) controlData.buttons |= SCE_CTRL_L3;
    if (report->stickR) controlData.buttons |= SCE_CTRL_R3;

    // Map the menu buttons
    if (report->plus)  controlData.buttons |= SCE_CTRL_START;
    if (report->minus) controlData.buttons |= SCE_CTRL_SELECT;
    if (report->home)  controlData.buttons |= SCE_CTRL_PSBUTTON;

    // Map the extra buttons
    if (report->capture) controlData.buttons |= SCE_CTRL_EXT1;

    // Map the sticks
    controlData.leftX  = report->leftX  >> 4;
    controlData.leftY  = report->leftY  >> 4;
    controlData.rightX = report->rightX >> 4;
    controlData.rightY = report->rightY >> 4;

    // Map the motion controls
    motionState.accelerX  = report->accelerX;
    motionState.accelerY  = report->accelerY;
    motionState.accelerZ  = report->accelerZ;
    motionState.velocityX = report->velocityX;
    motionState.velocityY = report->velocityY;
    motionState.velocityZ = report->velocityZ;

    // TODO: implement battery level
}
