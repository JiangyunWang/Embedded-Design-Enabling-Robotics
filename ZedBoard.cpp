#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "ZedBoard.h"

using namespace std;

// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;
// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;

const int gpio_pbtnu_offset = 0x174; // Offset for up push button


ZedBoard::ZedBoard(void) {
    fd = open( "/dev/mem", O_RDWR);
    pBase = (char *) mmap( NULL,
                           gpio_size,
                           PROT_READ | PROT_WRITE, MAP_SHARED,
                           fd,
                           gpio_address);
}

ZedBoard::~ZedBoard(void) {
    munmap(pBase, gpio_size);
    close(fd);
}


int ZedBoard::RegisterRead(int offset){
    return * (int *) (pBase + offset);
}

int ZedBoard::PushButtonGet(){
    int value = 0;
    int offset = gpio_pbtnu_offset;
    if (RegisterRead(offset)) {
        value = 2;
    } else if (RegisterRead(offset+4)) {
        value = 3;

    }
    return value;
}

