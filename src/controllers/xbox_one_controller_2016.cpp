#include <psp2kern/ctrl.h>

#include "xbox_one_controller_2016.h"

XboxOneController2016::XboxOneController2016(uint32_t mac0, uint32_t mac1, int port): Controller(mac0, mac1, port)
{
    // Send an empty write request just to receive a response
    static uint8_t report[4] = {};
    requestReport(HID_REQUEST_WRITE, report, sizeof(report));
}

void XboxOneController2016::processReport(uint8_t *buffer, size_t length)
{
    // Only process the report if it's of the right type
    if (buffer[0] != 0x01)
        return;

    // Interpret the data as an input report
    XboxOne2016Report0x01 *report = (XboxOne2016Report0x01*)buffer;

    // Clear the old control data
    controlData.buttons = 0;

    // Map the face buttons
    if (report->a) controlData.buttons |= SCE_CTRL_CROSS;
    if (report->b) controlData.buttons |= SCE_CTRL_CIRCLE;
    if (report->y) controlData.buttons |= SCE_CTRL_TRIANGLE;
    if (report->x) controlData.buttons |= SCE_CTRL_SQUARE;

    // Map the D-pad
    int dpad = report->dpad - 1;
    if (dpad == DPAD_NW || dpad == DPAD_N || dpad == DPAD_NE)
        controlData.buttons |= SCE_CTRL_UP;
    if (dpad == DPAD_NE || dpad == DPAD_E || dpad == DPAD_SE)
        controlData.buttons |= SCE_CTRL_RIGHT;
    if (dpad == DPAD_SE || dpad == DPAD_S || dpad == DPAD_SW)
        controlData.buttons |= SCE_CTRL_DOWN;
    if (dpad == DPAD_SW || dpad == DPAD_W || dpad == DPAD_NW)
        controlData.buttons |= SCE_CTRL_LEFT;

    // Map the triggers
    if (report->lb)       controlData.buttons |= SCE_CTRL_L1;
    if (report->rb)       controlData.buttons |= SCE_CTRL_R1;
    if (report->triggerL) controlData.buttons |= SCE_CTRL_LTRIGGER;
    if (report->triggerR) controlData.buttons |= SCE_CTRL_RTRIGGER;
    if (report->stickL)   controlData.buttons |= SCE_CTRL_L3;
    if (report->stickR)   controlData.buttons |= SCE_CTRL_R3;

    // Map the menu buttons
    if (report->menu)  controlData.buttons |= SCE_CTRL_START;
    if (report->view)  controlData.buttons |= SCE_CTRL_SELECT;
    // TODO: Guide is actually in a report with type 0x02, not here
    // if (report->guide) controlData.buttons |= SCE_CTRL_PSBUTTON;

    // Map the sticks
    controlData.leftX  = report->leftX  >> 8;
    controlData.leftY  = report->leftY  >> 8;
    controlData.rightX = report->rightX >> 8;
    controlData.rightY = report->rightY >> 8;

    // TODO: implement battery level
}
