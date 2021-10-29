//
// Created by Fangji Xu on 11/5/18.
//

#ifndef ZEDBOARD_H
#define ZEDBOARD_H

#include <stdio.h>


class ZedBoard {
private:
    char *pBase;    // virtual address where I/O was mapped
    int fd;            // file descriptor for dev memory
public:
    ZedBoard();       // Default Constructor
    ~ZedBoard();   // Destructor
    int RegisterRead(int offset);
    virtual int PushButtonGet();
};


#endif /* ZedBoard_hpp */
