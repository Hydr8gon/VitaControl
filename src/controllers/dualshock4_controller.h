#ifndef DUALSHOCK4_CONTROLLER_H
#define DUALSHOCK4_CONTROLLER_H

#include "../controller.h"

struct DualShock4Report0x11
{
    uint8_t reportId;

    uint8_t leftX;
    uint8_t leftY;
    uint8_t rightX;
    uint8_t rightY;

    uint8_t dpad     : 4;
    uint8_t square   : 1;
    uint8_t cross    : 1;
    uint8_t circle   : 1;
    uint8_t triangle : 1;

    uint8_t l1      : 1;
    uint8_t r1      : 1;
    uint8_t l2      : 1;
    uint8_t r2      : 1;
    uint8_t share   : 1;
    uint8_t options : 1;
    uint8_t l3      : 1;
    uint8_t r3      : 1;

    uint8_t ps   : 1;
    uint8_t tpad : 1;
    uint8_t      : 0;

    uint8_t triggerL;
    uint8_t triggerR;

    uint16_t timestamp;
    uint8_t battery;

    int16_t velocityX;
    int16_t velocityY;
    int16_t velocityZ;

    int16_t accelerX;
    int16_t accelerY;
    int16_t accelerZ;

    uint8_t unk0[5];

    uint8_t batteryLevel : 4;
    uint8_t usbPlugged   : 1;
    uint8_t headphones   : 1;
    uint8_t microphone   : 1;
    uint8_t              : 0;

    uint8_t unk1[4];

    unsigned int touch1Id        : 7;
    unsigned int touch1ActiveNeg : 1;
    unsigned int touch1X         : 12;
    unsigned int touch1Y         : 12;

    unsigned int touch2Id        : 7;
    unsigned int touch2ActiveNeg : 1;
    unsigned int touch2X         : 12;
    unsigned int touch2Y         : 12;
}
__attribute__((packed));

class DualShock4Controller: public Controller
{
    public:
        DualShock4Controller(uint32_t mac0, uint32_t mac1, int port);

        void processReport(uint8_t *buffer, size_t length);
};

#endif // DUALSHOCK4_CONTROLLER_H
