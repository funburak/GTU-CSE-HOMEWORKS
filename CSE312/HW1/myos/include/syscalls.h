#ifndef __MYOS__SYSCALLS_H
#define __MYOS__SYSCALLS_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <multitasking.h>

using namespace myos::common;
using namespace myos::hardwarecommunication;


namespace myos{
    class SyscallHandler : public InterruptHandler{
        private:
            TaskManager* taskManager;

        public:
        
            SyscallHandler(InterruptManager* interruptManager, uint8_t interruptNumber);
            ~SyscallHandler();

            virtual uint32_t HandleInterrupt(uint32_t esp);
    };
    // Asm functions for syscalls
    int getPid(); // Get PID
    void waitpid(uint8_t pid); // Waitpid
    void fork(int* pid); // Fork
    void exit(); // Exit
    int exec(void (*entrypoint)()); // Execve
}




#endif