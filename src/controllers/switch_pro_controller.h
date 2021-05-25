#ifndef SWITCH_PRO_CONTROLLER_H
#define SWITCH_PRO_CONTROLLER_H

#include "../controller.h"

struct SwitchProReport0x30
{
    uint8_t reportId;
    uint8_t timer;

    uint8_t connInfo : 4;
    uint8_t battery  : 4;

    uint8_t y  : 1;
    uint8_t x  : 1;
    uint8_t b  : 1;
    uint8_t a  : 1;
    uint8_t    : 2;
    uint8_t r  : 1;
    uint8_t zr : 1;

    uint8_t minus   : 1;
    uint8_t plus    : 1;
    uint8_t stickL  : 1;
    uint8_t stickR  : 1;
    uint8_t home    : 1;
    uint8_t capture : 1;
    uint8_t         : 0;

    uint8_t down  : 1;
    uint8_t up    : 1;
    uint8_t right : 1;
    uint8_t left  : 1;
    uint8_t       : 2;
    uint8_t l     : 1;
    uint8_t zl    : 1;

    uint16_t leftX  : 12;
    uint16_t leftY  : 12;
    uint16_t rightX : 12;
    uint16_t rightY : 12;

    uint8_t vibrator;

    uint16_t accelerX;
    uint16_t accelerY;
    uint16_t accelerZ;

    uint16_t velocityX;
    uint16_t velocityY;
    uint16_t velocityZ;
}
__attribute__((packed));

class SwitchProController: public Controller
{
    public:
        SwitchProController(uint32_t mac0, uint32_t mac1, int port);

        void processReport(uint8_t *buffer, size_t length);
};

#endif // SWITCH_PRO_CONTROLLER_H
