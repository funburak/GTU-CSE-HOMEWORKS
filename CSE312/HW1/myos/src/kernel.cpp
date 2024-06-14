#include <common/types.h>
#include <gdt.h>
#include <memorymanagement.h>
#include <hardwarecommunication/interrupts.h>
#include <syscalls.h>
#include <hardwarecommunication/pci.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
#include <drivers/ata.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <multitasking.h>

#include <drivers/amd_am79c973.h>

 // #define GRAPHICSMODE

using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;
using namespace myos::gui;


void printf(char* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i){
        switch(str[i]){
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80){
            x = 0;
            y++;
        }

        if(y >= 25){
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void printfHex(uint8_t key){
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0F];
    foo[1] = hex[key & 0x0F];
    printf(foo);
}

void printfHex32(uint32_t key){
    char buffer[9]; // 8 characters + null terminator for a 32-bit hex number
    buffer[8] = '\0'; // null terminator
    char* hex = "0123456789ABCDEF";
    for (int i = 7; i >= 0; i--) {
        buffer[i] = hex[key & 0x0F];
        key >>= 4;
    }
    printf(buffer);
}

void printNumber(int number){
    char buff[256];
    int n; 
    int i;
        
    // check if the digit is positive or negative
    if (number < 0){
        number *= -1;
        buff[0] = '-';
        i = n = 1;
    }
    else{
        i = n = 0;
    }

    do{
        buff[n] = '0' + (number % 10);
        number /= 10;
        ++n;
    } while (number > 0);

    buff[n] = '\0';
        
    while (i < n / 2){
        int temp = buff[i];
        buff[i] = buff[n - i - 1];
        buff[n - i - 1] = temp;
        ++i;        
    }
    printf((char *) buff);
}

class PrintfKeyboardEventHandler : public KeyboardEventHandler{
    public:
        void OnKeyDown(char c){
            char* foo = " ";
            foo[0] = c;
            printf(foo);
        }
};

class MouseToConsole : public MouseEventHandler{
    int8_t x, y;
public:

    MouseToConsole(){
        uint16_t* VideoMemory = (uint16_t*)0xb8000;
        x = 40;
        y = 12;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF); 
    }

    virtual void OnMouseMove(int xoffset, int yoffset){
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);

        x += xoffset;
        if(x >= 80) x = 79;
        if(x < 0) x = 0;
        y += yoffset;
        if(y >= 25) y = 24;
        if(y < 0) y = 0;

        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                            | (VideoMemory[80*y+x] & 0xF000) >> 4
                            | (VideoMemory[80*y+x] & 0x00FF);
    }

};

void sysprintf(char* str){
    asm("int $0x80" : : "a" (4), "b" (str));
}

void taskA(){
    while(true){
        sysprintf("A");
    }
}

void taskB(){
    while(true){
        sysprintf("B");
    }
}

int long_running_program(int n){
    int result = 0;
    for(int i = 0; i < n; i++){
        for(int j=0; j<n; ++j){
            result += i*j;
        }
    }
    return result;
}

void call_long_running_program(){
    printf("Calling Long Running Program\n");
    int result = long_running_program(10000);
    printf("Result: ");
    printNumber(result);
    printf("\n");
    exit();
}



void collatz(int n){
    printf("Collatz ");
    printNumber(n);
    printf(": ");
    while(n != 1){
        if(n % 2 == 0){
            n = n / 2;
        }else{
            n = 3*n + 1;
        }
        printNumber(n);
        printf(", ");
    }
    printf("\n");
}

void callCollatz(){
    printf("Calling Collatz\n");
    for(int i = 1; i <= 7; i++){
        collatz(i);
    }
    exit();
}

int binarySearch(int low, int high, int arr[], int x){
    if(low > high){
        return -1;
    }
    int mid = (low + high) / 2;
    if(arr[mid] == x){
        return mid;
    }
    else if(arr[mid] > x){
        return binarySearch(low, mid - 1, arr, x);
    }
    else{
        return binarySearch(mid + 1, high, arr, x);
    }
}

void callBinarySearch(){
    printf("Calling Binary Search ");
    int arr[] = {10, 20, 80, 30, 60, 50, 100, 110, 130, 170};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Input array: [");
    for(int i = 0; i < n; i++){
        printNumber(arr[i]);
        if(i != n-1)
            printf(", ");
    }
    printf("]");
    printf("\n");
    int x = 110;
    printf("Search for: ");
    printNumber(x);
    printf("\n");
    int index = -1;
    index = binarySearch(0, n-1, arr, x);
    printf("Output: ");
    printNumber(index);
    printf("\n");
    exit();
}


int linearSearch(int arr[], int x, int n){
    for(int i = 0; i < n; i++){
        if(arr[i] == x){
            return i;
        }
    }
    return -1;
}

void callLinearSearch(){
    printf("Calling Linear Search\n");
    int arr[] = {10, 20, 80, 30, 60, 50, 110, 100, 130, 170};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Input array: [");
    for(int i = 0; i < n; i++){
        printNumber(arr[i]);
        if(i != n-1)
            printf(", ");
    }
    printf("]: ");
    printf("\n");
    int x = 175;
    printf("Search for: ");
    printNumber(x);
    printf("\n");
    int index = -1;
    index = linearSearch(arr, x, n);
    printf("Output: ");
    printNumber(index);
    printf("\n");
    exit();
}

void singlefork(){
    int pid = getPid();
    fork(&pid);
    // printf("After fork: ");
    // printNumber(pid);
    // printf("\n");
    if(pid == 0){
        // printf("Child PID: ");
        // printNumber(getPid());
        // printf("\n");
        exec(callCollatz);
    }
    else{
        // printf("Parent PID: ");
        // printNumber(getPid());
        // printf("\n");
        exit();
    }
    while(1);
}


void lifecyclePartA(){
    int pid = getPid();
    fork(&pid);
    printf("After fork1: ");
    printNumber(pid);
    printf("\n");
    if(pid == 0){
        // printf("Child PID: ");
        // printNumber(getPid());
        // printf("\n");
        exec(callCollatz);
    }
    else{
        // printf("Parent PID: ");
        // printNumber(getPid());
        // printf("\n");
        int pid2 = getPid();
        fork(&pid2);
        printf("After fork2: ");
        printNumber(pid2);
        printf("\n");
        if(pid2 == 0){
            // printf("Child PID: ");
            // printNumber(getPid());
            // printf("\n");
            exec(callCollatz);
        }
        else{
            // printf("Parent PID: ");
            // printNumber(getPid());
            // printf("\n");
            int pid3 = getPid();
            fork(&pid3);
            printf("After fork3: ");
            printNumber(pid3);
            printf("\n");
            if(pid3 == 0){
                // printf("Child PID: ");
                // printNumber(getPid());
                // printf("\n");
                exec(callCollatz);
            }
            else{
                // printf("Parent PID: ");
                // printNumber(getPid());
                // printf("\n");
                int pid4 = getPid();
                fork(&pid4);
                printf("After fork4: ");
                printNumber(pid4);
                printf("\n");
                if (pid4 == 0) {
                    // printf("Child PID: ");
                    // printNumber(getPid());
                    // printf("\n");
                    exec(call_long_running_program);
                }
                else {
                    // printf("Parent PID: ");
                    // printNumber(getPid());
                    // printf("\n");
                    int pid5 = getPid();
                    fork(&pid5);
                    printf("After fork5: ");
                    printNumber(pid5);
                    printf("\n");
                    if (pid5 == 0) {
                        // printf("Child PID: ");
                        // printNumber(getPid());
                        // printf("\n");
                        exec(call_long_running_program);
                    }
                    else {
                        // printf("Parent PID: ");
                        // printNumber(getPid());
                        // printf("\n");
                        int pid6 = getPid();
                        fork(&pid6);
                        printf("After fork6: ");
                        printNumber(pid6);
                        printf("\n");
                        if (pid6 == 0) {
                            // printf("Child PID: ");
                            // printNumber(getPid());
                            // printf("\n");
                            exec(call_long_running_program);
                        }
                        else {
                            // printf("Parent PID: ");
                            // printNumber(getPid());
                            // printf("\n");
                            while(1);
                            // waitpid(pid6);
                            // exit();
                        }
                    }
                }
            }
        }
    }
    while(1);
}

int32_t rand(int min, int max) {
    uint64_t counter;
    int32_t num;
    asm("rdtsc": "=A"(counter)); // Read the Time Stamp Counter

    counter = counter * 1103515245 + 12345;
    num = (int)(counter / 65536) % (max - min);
    if (num < 0)
        num += max;
    return num + min;
}

void firstStrategyPartB(){
    int forkCount = 10;
    int processCount = 4;

    void (*processes[processCount])() = {callCollatz, call_long_running_program, callBinarySearch, callLinearSearch};

    int randomProcess = rand(0, processCount);
    // printf("Random Process: ");
    // printNumber(randomProcess);
    // printf("\n");

    for(int i = 0; i < forkCount; i++){
        int pid = getPid();
        fork(&pid);
        // printf("After fork: ");
        // printNumber(pid);
        // printf("\n");
        if(pid == 0){
            exec(processes[randomProcess]);
        }
    }
    while(1);
}

void secondStrategyPartB(){
    int forkCount = 3;
    int processCount = 4;

    void (*processes[processCount])() = {callCollatz, call_long_running_program, callBinarySearch, callLinearSearch};
    
    // Select two different programs
    int program1 = rand(0, processCount);
    int program2;
    do{
        program2 = rand(0, processCount);
    }while(program1 == program2);

    void (*selectedProcesses[2])() = {processes[program1], processes[program2]};

    for(int i=0; i<forkCount; i++){
        int pid = getPid();
        fork(&pid);
        if(pid == 0){
            exec(selectedProcesses[0]);
        }
    }

    for(int i=0; i<forkCount; i++){
        int pid2 = getPid();
        fork(&pid2);
        if(pid2 == 0){
            exec(selectedProcesses[1]);
        }
    }
    while(1);
}

void initTask(){
    printf("Init Task Started\n");
    while(true);
}

void thirdStrategyPartB(){
    int pid = -1;
    fork(&pid);
    if(pid == 0){
        exec(callCollatz);
    }
    else{
        int pid2 = -1;
        fork(&pid2);
        if(pid2 == 0){
            exec(call_long_running_program);
        }
        else{
            int pid3 = -1;
            fork(&pid3);
            if(pid3 == 0){
                exec(callBinarySearch);
            }
            else{
                int pid4 = -1;
                fork(&pid4);
                if(pid4 == 0){
                    exec(callLinearSearch);
                }
                else{
                    while(1);
                }
            }
        }
    }
}


typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors(){
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}


extern "C" void kernelMain(const void* multiboot_structure, uint32_t /*multiboot_magic*/){
    printf("Welcome to My OS\n");
    GlobalDescriptorTable gdt;
    TaskManager taskManager(&gdt);


    // Task task1(&gdt, taskA, myos::Priority::HIGH);
    // taskManager.AddTask(&task1);
    // Task task2(&gdt, taskB);
    // taskManager.AddTask(&task2);

    // Task partA(&gdt, lifecyclePartA, myos::Priority::MEDIUM);
    // taskManager.AddTask(&partA);

    // Task partBFirst(&gdt, firstStrategyPartB, myos::Priority::LOW);
    // taskManager.AddTask(&partBFirst);

    // Task partBSecond(&gdt, secondStrategyPartB, myos::Priority::LOW);
    // taskManager.AddTask(&partBSecond);

    // Task taskInit(&gdt, initTask, myos::Priority::LOW);
    // taskManager.AddTask(&taskInit);

    // Task partCSecond(&gdt, thirdStrategyPartB, myos::Priority::LOW);
    // taskManager.AddTask(&partCSecond);

    Task singlefork1(&gdt, singlefork, myos::Priority::LOW);
    taskManager.AddTask(&singlefork1);


    InterruptManager interrupts(0x20, &gdt, &taskManager);
    SyscallHandler syscalls(&interrupts, 0x80);

    #ifdef GRAPHICSMODE
        Desktop desktop(320, 200, 0x00, 0x00, 0xA8);
    #endif
    
    DriverManager drvManager;

        #ifdef GRAPHICSMODE
            KeyboardDriver keyboard(&interrupts, &desktop);
        #else
            PrintfKeyboardEventHandler kbhandler;
            KeyboardDriver keyboard(&interrupts, &kbhandler);
        #endif
        drvManager.AddDriver(&keyboard);

        #ifdef GRAPHICSMODE
            MouseDriver mouse(&interrupts, &desktop);
        #else
            MouseToConsole mousehandler;
            MouseDriver mouse(&interrupts, &mousehandler);
        #endif
        drvManager.AddDriver(&mouse);

        // PeripheralComponentInterconnectController PCIController;
        // PCIController.SelectDrivers(&drvManager, &interrupts);

        // VideoGraphicsArray vga;

    drvManager.ActivateAll();

    #ifdef GRAPHICSMODE
        vga.SetMode(320,200,8);
        Window win1(&desktop, 10,10,20,20, 0xA8,0x00,0x00);
        desktop.AddChild(&win1);
        Window win2(&desktop, 40,15,30,30, 0x00,0xA8,0x00);
        desktop.AddChild(&win2);
    #endif

    interrupts.Activate();

    while(1){
        #ifdef GRAPHICSMODE
            desktop.Draw(&vga);
        #endif
    }
}