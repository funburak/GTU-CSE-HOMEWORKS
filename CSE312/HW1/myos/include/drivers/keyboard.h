#ifndef __MYOS__DRIVERS__KEYBOARD_H
#define __MYOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

using namespace myos::common;
using namespace myos::hardwarecommunication;
using namespace myos::drivers;


namespace myos{
    namespace drivers{
        class KeyboardEventHandler{
            public:
                KeyboardEventHandler();
                virtual void OnKeyDown(char);
                virtual void OnKeyUp(char);
        };

        class KeyboardDriver : public InterruptHandler, public Driver{
            Port8Bit dataport;
            Port8Bit commandport;
            KeyboardEventHandler* handler;
            public:
                KeyboardDriver(InterruptManager* manager, KeyboardEventHandler* handler);
                ~KeyboardDriver();
                virtual uint32_t HandleInterrupt(uint32_t esp);
                virtual void Activate();
        };

    }
}


#endif