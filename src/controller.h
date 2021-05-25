#ifndef CONTROLLER_H
#define CONTROLLER_H

enum HidRequestType
{
    HID_REQUEST_READ = 0,
    HID_REQUEST_WRITE,
    HID_REQUEST_UNKNOWN,
    HID_REQUEST_FEATURE
};

enum DpadDirections
{
    DPAD_N = 0,
    DPAD_NE,
    DPAD_E,
    DPAD_SE,
    DPAD_S,
    DPAD_SW,
    DPAD_W,
    DPAD_NW
};

enum BatteryStates
{
    BATTERY_CHARGING = 0xEE,
    BATTERY_CHARGED  = 0xEF,
    BATTERY_FULL     = 0x05
};

enum SceCtrlButtonsExt
{
    SCE_CTRL_EXT1 = 0x04000000,
	SCE_CTRL_EXT2 = 0x08000000
};

struct ControlData
{
    uint32_t buttons = 0;
    uint8_t leftX  = 0;
    uint8_t leftY  = 0;
    uint8_t rightX = 0;
    uint8_t rightY = 0;
};

struct TouchData
{
    bool touchActive[2] = {};
    uint8_t touchId[2] = {};
    uint16_t touchX[2] = {};
    uint16_t touchY[2] = {};
    uint16_t touchWidth = 0;
    uint16_t touchHeight = 0;
    uint16_t touchDeadX = 0;
    uint16_t touchDeadY = 0;
};

struct MotionState
{
    int16_t accelerX = 0;
    int16_t accelerY = 0;
    int16_t accelerZ = 0;
    int16_t velocityX = 0;
    int16_t velocityY = 0;
    int16_t velocityZ = 0;
};

class Controller
{
    public:
        Controller(uint32_t mac0, uint32_t mac1, int port): mac0(mac0), mac1(mac1) {}

        static Controller *makeController(uint32_t mac0, uint32_t mac1, int port);

        void requestReport(uint8_t type, uint8_t *buffer, size_t length);
        virtual void processReport(uint8_t *buffer, size_t length) = 0;

        const ControlData *getControlData()  { return &controlData; }
        const TouchData   *getTouchData()    { return &touchData;   }
        const MotionState *getMotionState()  { return &motionState; }
        uint8_t            getBatteryLevel() { return batteryLevel; }

        uint32_t getMac0() { return mac0; }
        uint32_t getMac1() { return mac1; }

    protected:
        ControlData controlData;
        TouchData   touchData;
        MotionState motionState;
        uint8_t     batteryLevel = 0;

        static uint32_t calculateCrc(uint8_t *buffer, size_t length);

    private:
        uint32_t mac0, mac1;
};

#endif // CONTROLLER_H
