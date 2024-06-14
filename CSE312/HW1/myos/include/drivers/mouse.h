#ifndef __MYOS__DRIVERS__MOUSE_H
#define __MYOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

using namespace myos::common;
using namespace myos::hardwarecommunication;
using namespace myos::drivers;

namespace myos{
    namespace drivers{
        class MouseEventHandler{
            public:
                MouseEventHandler();
                
                virtual void OnActivate();
                virtual void OnMouseDown(uint8_t button);
                virtual void OnMouseUp(uint8_t button);
                virtual void OnMouseMove(int x, int y);
        };


        class MouseDriver : public InterruptHandler, public Driver{
            Port8Bit dataport;
            Port8Bit commandport;

            uint8_t buffer[3];
            uint8_t offset;
            uint8_t buttons;

            MouseEventHandler* handler;

            public:
                MouseDriver(InterruptManager* manager, MouseEventHandler* handler);
                ~MouseDriver();
                virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
                virtual void Activate();
        };

    }
}



#endif