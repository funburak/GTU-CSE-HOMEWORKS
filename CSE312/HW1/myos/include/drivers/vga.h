#ifndef __MYOS__DRIVERS__VGA_H
#define __MYOS__DRIVERS__VGA_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

using namespace myos::common;
using namespace myos::hardwarecommunication;

namespace myos{
    namespace drivers{
        class VideoGraphicsArray{
            protected:
                Port8Bit miscPort;
                Port8Bit crtcIndexPort;
                Port8Bit crtcDataPort;
                Port8Bit sequencerIndexPort;
                Port8Bit sequencerDataPort;
                Port8Bit graphicsControllerIndexPort;
                Port8Bit graphicsControllerDataPort;
                Port8Bit attributeControllerIndexPort;
                Port8Bit attributeControllerReadPort;
                Port8Bit attributeControllerWritePort;
                Port8Bit attributeControllerResetPort;

                void WriteRegisters(uint8_t* registers);
                uint8_t* GetFrameBufferSegment();

                virtual uint8_t GetColorIndex(uint8_t r, uint8_t g, uint8_t b);
            public:
                VideoGraphicsArray();
                ~VideoGraphicsArray();

                virtual bool SupportsMode(uint32_t width, uint32_t height, uint32_t colordepth);
                virtual bool SetMode(uint32_t width, uint32_t height, uint32_t colordepth);
                virtual void PutPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b);
                virtual void PutPixel(int32_t x, int32_t y, uint8_t colorIndex);

                virtual void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);
        };
    }
}









#endif