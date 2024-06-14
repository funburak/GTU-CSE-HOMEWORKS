#ifndef __MYOS__DRIVERS__ATA_H
#define __MYOS__DRIVERS__ATA_H

#include <common/types.h>
#include <hardwarecommunication/port.h>

using namespace myos::common;
using namespace myos::hardwarecommunication;

namespace myos{
    namespace drivers{
        class AdvancedTechnologyAttachment{
            protected:
                Port16Bit dataPort;
                Port8Bit errorPort;
                Port8Bit sectorCountPort;
                Port8Bit lbaLowPort;
                Port8Bit lbaMidPort;
                Port8Bit lbaHiPort;
                Port8Bit devicePort;
                Port8Bit commandPort;
                Port8Bit controlPort;

                bool master;
                uint16_t bytesPerSector;
            public:
                AdvancedTechnologyAttachment(uint16_t portBase,bool master);
                ~AdvancedTechnologyAttachment();

                void Identify();
                void Read28(uint32_t sector, uint8_t* data, int count);
                void Write28(uint32_t sector, uint8_t* data, int count);
                void Flush();
            
        };
    }
}


#endif