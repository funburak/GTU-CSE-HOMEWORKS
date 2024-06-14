#include <multitasking.h>

using namespace myos;
using namespace myos::common;

void printf(char* str);
void printfHex(uint8_t);
void printfHex32(uint32_t);
void printNumber(int);

uint32_t Task::nextTaskId = 1;

Task::Task(GlobalDescriptorTable* gdt, void entrypoint(), Priority priority){
    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));

    cpustate->eax = 0;
    cpustate->ebx = 0;
    cpustate->ecx = 0;
    cpustate->edx = 0;

    cpustate->esi = 0;
    cpustate->edi = 0;
    cpustate->ebp = 0;

    // cpustate->gs = 0;
    // cpustate->fs = 0;
    // cpustate->es = 0;
    // cpustate->ds = 0;

    // cpustate->error = 0;

    // cpustate->esp =;

    cpustate->eip = (uint32_t)entrypoint;
    cpustate->cs = gdt->CodeSegmentSelector();
    // cpustate->ss = gdt->DataSegmentSelector();
    cpustate->eflags = 0x202; // 0x202 is the value of the flags register when the CPU is in kernel mode

    this->state = READY;
    this->pid = Task::nextTaskId++;
    this->priority = priority;

}

Task::~Task(){

}

TaskManager::TaskManager(GlobalDescriptorTable* gdt){
    this->gdt = gdt;
    numTasks = 0;
    currentTask = -1;
}

TaskManager::~TaskManager(){

}

bool TaskManager::AddTask(Task* task){
    if(numTasks >= 256){
        return false;
    }
    tasks[numTasks++] = task;
    return true;
}

int TaskManager::getTaskIndex(uint32_t pid){ // Get the index of a task in the process table
    for(int i = 0; i < numTasks; i++){
        if(tasks[i]->pid == pid){
            return i;
        }
    }
    return -1;
}

void TaskManager::PrintProcessTable(){ // Print the process table
    printf("************* PROCESS TABLE *************\n");
    printf("PID      PPID        STATE      PRIORITY\n");
    for(int i=0; i<numTasks; ++i){
        printNumber(tasks[i]->pid);
        printf("         ");
        printNumber(tasks[i]->ppid);
        printf("        ");
        switch(tasks[i]->state){
            case READY:
                if(i == currentTask){
                    printf("RUNNING");
                }
                else{
                    printf("READY");
                }
                break;
            case WAITING:
                printf("WAITING");
                break;
            case TERMINATED:
                printf("TERMINATED");
                break;
        }
        printf("        ");
        switch(tasks[i]->priority){
            case HIGH:
                printf("HIGH\n");
                break;
            case MEDIUM:
                printf("MEDIUM\n");
                break;
            case LOW:
                printf("LOW\n");
                break;
        }
        // printf("\n");
    }
    printf("*****************************************\n");
    // for(int i=0; i<10000000; ++i){
    //     printf("");
    // }
}

CPUState* TaskManager::Schedule(CPUState* cpustate){ // Schedule the next task to run using Round Robin

    if (numTasks <= 0) {
        return cpustate; // No task to schedule.
    }

    if (currentTask >= 0) { 
        tasks[currentTask]->cpustate = cpustate; // Save the CPU state of the current task.
    }
    
    PrintProcessTable(); // Print the process table
    int highestPriority = 4; // Assume lower numbers are higher priority.
    int nextTask = -1;

    // Iterate over all tasks to find the highest-priority READY task.
    for (int i = 0; i < numTasks; i++) {
        int idx = (currentTask + 1 + i) % numTasks; // Round Robin index
        Task* task = tasks[idx];

        // Check if the task is READY and has higher priority than the currently found highest.
        if (task->state == READY && task->priority < highestPriority) {
            highestPriority = task->priority;
            nextTask = idx;
        }

        // Handle tasks in WAITING state.
        if (task->state == WAITING && task->waitpid > 0) {
            int waitpid = getTaskIndex(task->waitpid); // Get the index of the task that the current task is waiting for.
            if (waitpid >= 0 && tasks[waitpid]->state == TERMINATED) {
                task->waitpid = 0; // Reset the waitpid of the current task.
                task->state = READY; // Set the state of the current task to READY.
                if (task->priority < highestPriority) {
                    highestPriority = task->priority;
                    nextTask = idx;
                }
            }
        }
    }

    if (nextTask != -1) {
        currentTask = nextTask; // Set the current task to the highest-priority task found.
    } else if (currentTask == -1 || tasks[currentTask]->state != READY) {
        // Fallback if no READY tasks are found and current task is not eligible.
        for (int i = 0; i < numTasks; i++) {
            if (tasks[i]->state == READY) {
                currentTask = i;
                break;
            }
        }
    }


    return tasks[currentTask]->cpustate; // Return the CPU state of the scheduled task.
}

uint32_t TaskManager::ExecveTask(void entrypoint()){ // Execute a new task
    tasks[currentTask]->state = READY; // Set the state of the current task to READY
    tasks[currentTask]->cpustate = (CPUState*)(tasks[currentTask]->stack + 4096 - sizeof(CPUState)); // Set the CPU state of the current task to the top of the stack

    tasks[currentTask]->cpustate->eax = 0; // Set the eax register of the CPU state of the current task to 0
    tasks[currentTask]->cpustate->ebx = 0; // Set the ebx register of the CPU state of the current task to 0
    tasks[currentTask]->cpustate->ecx = tasks[currentTask]->pid; // Set the ecx register of the CPU state of the current task to the PID of the current task
    tasks[currentTask]->cpustate->edx = 0; // Set the edx register of the CPU state of the current task to 0

    tasks[currentTask]->cpustate->esi = 0; // Set the esi register of the CPU state of the current task to 0
    tasks[currentTask]->cpustate->edi = 0; // Set the edi register of the CPU state of the current task to 0
    tasks[currentTask]->cpustate->ebp = 0; // Set the ebp register of the CPU state of the current task to 0

    tasks[currentTask]->cpustate->eip = (uint32_t)entrypoint; // Set the eip register of the CPU state of the current task to the entry point of the new task
    tasks[currentTask]->cpustate->cs = gdt->CodeSegmentSelector(); // Set the cs register of the CPU state of the current task to the code segment selector of the GDT
    tasks[currentTask]->cpustate->eflags = 0x202; // 0x202 is the value of the flags register when the CPU is in kernel mode
    return (uint32_t)tasks[currentTask]->cpustate; // Return the CPU state of the current task
}

uint32_t TaskManager::getPid(){ // Get the PID of the current task
    return tasks[currentTask]->pid;
}

uint32_t TaskManager::ForkTask(CPUState* cpustate){ // Fork the current task
    if(numTasks >= 256){
        return 0;
    }
    

    typedef void (*EntryPointType)();  // Define a function pointer type
    EntryPointType entrypoint = (EntryPointType)cpustate->eip;  // Cast to the function pointer type
    tasks[numTasks] = new Task(gdt, entrypoint, tasks[currentTask]->priority);

    for(int i = 0; i < sizeof(tasks[currentTask]->stack); i++){ // Copy the stack of the current task to the stack of the new task
        tasks[numTasks]->stack[i] = tasks[currentTask]->stack[i];
    }

    uint32_t currentTaskOffset = (uint32_t)cpustate - (uint32_t)tasks[currentTask]->stack; // Calculate the offset of the CPU state of the current task
    tasks[numTasks]->cpustate = (CPUState*)(((uint32_t)tasks[numTasks]->stack) + currentTaskOffset); // Set the CPU state of the new task to the offset of the CPU state of the current task

    tasks[numTasks]->state = READY; // Set the state of the new task to READY
    tasks[numTasks]->ppid = tasks[currentTask]->pid; // Set the PPID of the new task to the PID of the current task
    //tasks[numTasks]->pid = Task::nextTaskId; // Set the PID of the new task to the next task ID
    tasks[numTasks]->priority = tasks[currentTask]->priority; // Set the priority of the new task to the priority of the current task

    tasks[numTasks]->cpustate->ecx = 0; // Set the ecx register of the CPU state of the new task to 0
    
    numTasks++; // Increment the number of tasks

    printf("Forked task PID: ");
    printNumber(tasks[numTasks-1]->pid);
    printf("\n");

    return tasks[numTasks-1]->pid; // Return the PID of the new task
}

bool TaskManager::ExitTask(){
    tasks[currentTask]->state = TERMINATED; // Set the state of the current task to TERMINATED
    return true;
}

bool TaskManager::WaitTask(uint32_t esp){ // Wait for a task to finish
    CPUState* cpustate = (CPUState*) esp; // Get the CPU state of the current task
    uint32_t pid = cpustate->ebx; // Get the PID of the task to wait for

    int taskIndex = getTaskIndex(pid); // Get the index of the task to wait for
    if(taskIndex == -1){
        printf("Task not found\n");
        return false;
    }

    if(numTasks <= taskIndex || tasks[taskIndex]->state == TERMINATED){ // If the task to wait for has terminated
        printf("Task already terminated\n");
        return true;
    }

    tasks[currentTask]->cpustate = cpustate; // Set the CPU state of the current task to the CPU state of the task to wait for
    tasks[currentTask]->waitpid = pid; // Set the waitpid of the current task to the PID of the task to wait for
    tasks[currentTask]->state = WAITING; // Set the state of the current task to WAITING

    printf("Waiting for task\n");

    return true;
}