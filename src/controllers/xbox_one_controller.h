#ifndef XBOX_ONE_CONTROLLER_H
#define XBOX_ONE_CONTROLLER_H

#include "../controller.h"

struct XboxOneReport0x01
{
    uint8_t reportId;

    uint16_t leftX;
    uint16_t leftY;
    uint16_t rightX;
    uint16_t rightY;

    uint16_t triggerL;
    uint16_t triggerR;

    uint8_t dpad;

    uint8_t a  : 1;
    uint8_t b  : 1;
    uint8_t    : 1;
    uint8_t x  : 1;
    uint8_t y  : 1;
    uint8_t    : 1;
    uint8_t lb : 1;
    uint8_t rb : 1;

    uint8_t        : 3;
    uint8_t menu   : 1;
    uint8_t guide  : 1;
    uint8_t stickL : 1;
    uint8_t stickR : 1;
    uint8_t        : 0;

    uint8_t view : 1;
    uint8_t      : 0;

}
__attribute__((packed));

class XboxOneController: public Controller
{
    public:
        XboxOneController(uint32_t mac0, uint32_t mac1, int port);

        void processReport(uint8_t *buffer, size_t length);
};

#endif // XBOX_ONE_CONTROLLER_H
