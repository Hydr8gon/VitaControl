#include <psp2kern/ctrl.h>

#include "dualshock4_controller.h"

DualShock4Controller::DualShock4Controller(uint32_t mac0, uint32_t mac1, int port): Controller(mac0, mac1, port)
{
    static const uint8_t ledColours[][3] =
    {
        { 0x00, 0x00, 0x40 }, // Blue
        { 0x40, 0x00, 0x00 }, // Red
        { 0x00, 0x40, 0x00 }, // Green
        { 0x20, 0x00, 0x20 }, // Pink
    };

    // Prepare a write request to switch to extended mode and set LED colours
    static uint8_t buffer[79] = {};
    buffer[0]  = 0xA2;
    buffer[1]  = 0x11;
    buffer[2]  = 0xC0;
    buffer[3]  = 0x20;
    buffer[4]  = 0xF3;
    buffer[5]  = 0x04;
    buffer[9]  = ledColours[port][0];
    buffer[10] = ledColours[port][1];
    buffer[11] = ledColours[port][2];

    // Calculate the CRC of the data (including the 0xA2 byte) and append it to the end
    uint32_t crc = calculateCrc(buffer, 75);
    buffer[75] = crc >>  0;
    buffer[76] = crc >>  8;
    buffer[77] = crc >> 16;
    buffer[78] = crc >> 24;

    // Send the write request, omitting the 0xA2 byte
    requestReport(HID_REQUEST_WRITE, buffer + 1, sizeof(buffer) - 1);

    // Set the touchpad dimensions
    touchData.touchWidth  = 1920;
    touchData.touchHeight =  940;
    touchData.touchDeadX  =   60;
    touchData.touchDeadY  =  120;
}

void DualShock4Controller::processReport(uint8_t *buffer, size_t length)
{
    // Only process the report if it's of the right type
    if (buffer[0] != 0x11)
        return;

    // Interpret the data as an input report
    DualShock4Report0x11 *report = (DualShock4Report0x11*)buffer;

    // Clear the old control data
    controlData.buttons = 0;

    // Map the face buttons
    if (report->cross)    controlData.buttons |= SCE_CTRL_CROSS;
    if (report->circle)   controlData.buttons |= SCE_CTRL_CIRCLE;
    if (report->triangle) controlData.buttons |= SCE_CTRL_TRIANGLE;
    if (report->square)   controlData.buttons |= SCE_CTRL_SQUARE;

    // Map the D-pad
    if (report->dpad == DPAD_NW || report->dpad == DPAD_N || report->dpad == DPAD_NE)
        controlData.buttons |= SCE_CTRL_UP;
    if (report->dpad == DPAD_NE || report->dpad == DPAD_E || report->dpad == DPAD_SE)
        controlData.buttons |= SCE_CTRL_RIGHT;
    if (report->dpad == DPAD_SE || report->dpad == DPAD_S || report->dpad == DPAD_SW)
        controlData.buttons |= SCE_CTRL_DOWN;
    if (report->dpad == DPAD_SW || report->dpad == DPAD_W || report->dpad == DPAD_NW)
        controlData.buttons |= SCE_CTRL_LEFT;

    // Map the triggers
    if (report->l1) controlData.buttons |= SCE_CTRL_L1;
    if (report->r1) controlData.buttons |= SCE_CTRL_R1;
    if (report->l2) controlData.buttons |= SCE_CTRL_LTRIGGER;
    if (report->r2) controlData.buttons |= SCE_CTRL_RTRIGGER;
    if (report->l3) controlData.buttons |= SCE_CTRL_L3;
    if (report->r3) controlData.buttons |= SCE_CTRL_R3;

    // Map the menu buttons
    if (report->options) controlData.buttons |= SCE_CTRL_START;
    if (report->share)   controlData.buttons |= SCE_CTRL_SELECT;
    if (report->ps)      controlData.buttons |= SCE_CTRL_PSBUTTON;

    // Map the extra buttons
    if (report->tpad) controlData.buttons |= SCE_CTRL_EXT1;

    // Map the sticks
    controlData.leftX  = report->leftX;
    controlData.leftY  = report->leftY;
    controlData.rightX = report->rightX;
    controlData.rightY = report->rightY;

    // Map the touchscreen
    touchData.touchActive[0] = !report->touch1ActiveNeg;
    touchData.touchId[0]     = report->touch1Id;
    touchData.touchX[0]      = report->touch1X;
    touchData.touchY[0]      = report->touch1Y;
    touchData.touchActive[1] = !report->touch2ActiveNeg;
    touchData.touchId[1]     = report->touch2Id;
    touchData.touchX[1]      = report->touch2X;
    touchData.touchY[1]      = report->touch2Y;

    // Map the motion controls
    motionState.accelerX  = report->accelerX;
    motionState.accelerY  = report->accelerY;
    motionState.accelerZ  = report->accelerZ;
    motionState.velocityX = report->velocityX;
    motionState.velocityY = report->velocityY;
    motionState.velocityZ = report->velocityZ;

    // TODO: implement battery level
}
