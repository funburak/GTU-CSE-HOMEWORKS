#ifndef __MYOS__MULTITASKING_H
#define __MYOS__MULTITASKING_H

#include <common/types.h>
#include <gdt.h>

using namespace myos::common;

namespace myos{

    enum TaskState{
        READY,
        WAITING,
        TERMINATED
    };

    enum Priority{
        HIGH,
        MEDIUM,
        LOW
    };

    struct CPUState{
        uint32_t eax; // Accumulator Register
        uint32_t ebx; // Base Register
        uint32_t ecx; // Counter Register
        uint32_t edx; // Data Register

        uint32_t esi; // Source Index
        uint32_t edi; // Destination Index
        uint32_t ebp; // Base Pointer

        // uint32_t gs; // General Storage
        // uint32_t fs; // General Storage
        // uint32_t es; // Extra Segment
        // uint32_t ds; // Data Segment


        uint32_t error; // Error Code

        uint32_t eip; // Instruction Pointer
        uint32_t cs; // Code Segment
        uint32_t eflags; // Flags Register
        uint32_t esp; // Stack Pointer
        uint32_t ss; // Stack Segment
    } __attribute__((packed));


    class Task{
            friend class TaskManager;
        private:
            static uint32_t nextTaskId; // Static variable to keep track of the next task id
            uint32_t pid; // Process ID
            uint32_t ppid; // Parent Process ID
            TaskState state; // Task State
            Priority priority; // Task Priority
            uint32_t waitpid; // Waitpid
            uint8_t stack[4096]; // 4KB
            CPUState* cpustate; // CPU State
        public:
            Task(GlobalDescriptorTable* gdt, void entrypoint(),Priority priority);
            ~Task();

    };
    class TaskManager{
        friend class InterruptHandler;


        private:
            Task* tasks[256]; // Array of tasks
            int numTasks; // Number of tasks
            int currentTask; // Current Task
            GlobalDescriptorTable* gdt; // Global Descriptor Table
            int getTaskIndex(uint32_t pid); // Get Task Index

        protected:
            
        public:
            TaskManager(GlobalDescriptorTable* gdt);
            ~TaskManager();
            bool AddTask(Task* task); 
            CPUState* Schedule(CPUState* cpustate); // Round Robin

            void PrintProcessTable(); // Print the process table
            uint32_t ExecveTask(void entrypoint()); // Execve
            uint32_t getPid(); // Get PID
            uint32_t ForkTask(CPUState* cpustate); // Fork
            bool ExitTask(); // Exit
            bool WaitTask(uint32_t esp); // Waitpid
    };
}

#endif