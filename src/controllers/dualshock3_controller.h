#ifndef DUALSHOCK3_CONTROLLER_H
#define DUALSHOCK3_CONTROLLER_H

#include "../controller.h"

struct DualShock3Report0x01
{
    uint8_t reportId;
    uint8_t unk0;

    uint8_t select : 1;
    uint8_t l3     : 1;
    uint8_t r3     : 1;
    uint8_t start  : 1;
    uint8_t up     : 1;
    uint8_t right  : 1;
    uint8_t down   : 1;
    uint8_t left   : 1;

    uint8_t l2       : 1;
    uint8_t r2       : 1;
    uint8_t l1       : 1;
    uint8_t r1       : 1;
    uint8_t triangle : 1;
    uint8_t circle   : 1;
    uint8_t cross    : 1;
    uint8_t square   : 1;

    uint8_t ps : 1;
    uint8_t    : 0;

    uint8_t unk1;

    uint8_t leftX;
    uint8_t leftY;
    uint8_t rightX;
    uint8_t rightY;

    uint8_t unk2[31];

    int16_t accelerX;
    int16_t accelerY;
    int16_t accelerZ;

    int16_t velocityZ;
}
__attribute__((packed));

class DualShock3Controller: public Controller
{
    public:
        DualShock3Controller(uint32_t mac0, uint32_t mac1, int port);

        void processReport(uint8_t *buffer, size_t length);
};

#endif // DUALSHOCK3_CONTROLLER_H
