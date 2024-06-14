#include <syscalls.h>

using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;

void printf(char* str);
void printNumber(int);

SyscallHandler::SyscallHandler(InterruptManager* interruptManager, uint8_t interruptNumber)
: InterruptHandler(interruptManager, interruptNumber+interruptManager->HardwareInterruptOffset()){
}

SyscallHandler::~SyscallHandler(){

}

int myos::getPid(){ // Get PID
    int ret;
    asm("int $0x80" : "=c" (ret) : "a" (20));
    return ret;
}

void myos::waitpid(uint8_t pid){ // Waitpid
    asm("int $0x80" : : "a" (7), "b" (pid));
}

void myos::fork(int* pid){ // Fork
    asm ("int $0x80" : "=c" (*pid) : "a" (2));
}

void myos::exit(){ // Exit
    asm("int $0x80" : : "a" (1));
}

int myos::exec(void (*entrypoint)()){ // Execve
    int ret;
    asm("int $0x80" : "=c" (ret) : "a" (11), "b" ((uint32_t)entrypoint));
    return ret;
}


uint32_t SyscallHandler::HandleInterrupt(uint32_t esp){ // Handle Interrupt
    CPUState* cpu = (CPUState*) esp; // Cast the esp to a CPUState

    switch(cpu->eax){ // Switch on the syscall number
        case 1: // Exit
            if(InterruptHandler::Exit()){
                return InterruptHandler::HandleInterrupt(esp);
            }
            break;
        case 2: // Fork
            cpu->ecx = InterruptHandler::Fork(cpu);
            return InterruptHandler::HandleInterrupt(esp);
            break;
        case 7: // Waitpid
            if(InterruptHandler::WaitPid(esp)){
                return InterruptHandler::HandleInterrupt(esp);
            }
            break;
        case 11: // Execve
            esp = InterruptHandler::Execve(cpu->ebx);
            break;
        case 20: // Get PID
            cpu->ecx = InterruptHandler::GetPid();
            break;
        default:
            break; 
    }
    return esp;
}
