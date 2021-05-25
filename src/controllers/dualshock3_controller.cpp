#include <psp2kern/ctrl.h>

#include "dualshock3_controller.h"

DualShock3Controller::DualShock3Controller(uint32_t mac0, uint32_t mac1, int port): Controller(mac0, mac1, port)
{
    // Prepare a feature request to make the controller functional
    static uint8_t buffer[5] = {};
    buffer[0] = 0xF4;
    buffer[1] = 0x42;
    buffer[2] = 0x03;
    buffer[3] = 0x00;
    buffer[4] = 0x00;

    // Send the feature request
    requestReport(HID_REQUEST_FEATURE, buffer, sizeof(buffer));
}

void DualShock3Controller::processReport(uint8_t *buffer, size_t length)
{
    // Only process the report if it's of the right type
    if (buffer[0] != 0x01)
        return;

    // Interpret the data as an input report
    DualShock3Report0x01 *report = (DualShock3Report0x01*)buffer;

    // Clear the old control data
    controlData.buttons = 0;

    // Map the face buttons
    if (report->cross)    controlData.buttons |= SCE_CTRL_CROSS;
    if (report->circle)   controlData.buttons |= SCE_CTRL_CIRCLE;
    if (report->triangle) controlData.buttons |= SCE_CTRL_TRIANGLE;
    if (report->square)   controlData.buttons |= SCE_CTRL_SQUARE;

    // Map the D-pad
    if (report->up)    controlData.buttons |= SCE_CTRL_UP;
    if (report->right) controlData.buttons |= SCE_CTRL_RIGHT;
    if (report->down)  controlData.buttons |= SCE_CTRL_DOWN;
    if (report->left)  controlData.buttons |= SCE_CTRL_LEFT;

    // Map the triggers
    if (report->l1) controlData.buttons |= SCE_CTRL_L1;
    if (report->r1) controlData.buttons |= SCE_CTRL_R1;
    if (report->l2) controlData.buttons |= SCE_CTRL_LTRIGGER;
    if (report->r2) controlData.buttons |= SCE_CTRL_RTRIGGER;
    if (report->l3) controlData.buttons |= SCE_CTRL_L3;
    if (report->r3) controlData.buttons |= SCE_CTRL_R3;

    // Map the menu buttons
    if (report->start)  controlData.buttons |= SCE_CTRL_START;
    if (report->select) controlData.buttons |= SCE_CTRL_SELECT;
    if (report->ps)     controlData.buttons |= SCE_CTRL_PSBUTTON;

    // Map the sticks
    controlData.leftX  = report->leftX;
    controlData.leftY  = report->leftY;
    controlData.rightX = report->rightX;
    controlData.rightY = report->rightY;

    motionState.accelerX  = report->accelerX;
    motionState.accelerY  = report->accelerY;
    motionState.accelerZ  = report->accelerZ;
    motionState.velocityZ = report->velocityZ;

    // TODO: implement battery level
}
