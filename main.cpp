#include <iostream>
#include <stdlib.h>
#include "ZedBoard.h"
#include "GPIO.h"
#include <thread>

using namespace std;

int state = 1;

class ZedBoardToGPIO : public ZedBoard {
private:
    GPIO *g1;
    GPIO *g2;
    GPIO *g3;
    GPIO *g4;
    GPIO *g5;


public:
    ZedBoardToGPIO(GPIO *gp1, GPIO *gp2, GPIO *gp3, GPIO *gp4, GPIO *gp5) {
        while (PushButtonGet() != 2 && PushButtonGet() != 3) ;
        if (PushButtonGet() == 2 ){
            cout<<"const_zedtoGPIO";
            g1 = gp1;
            g2 = gp2;
            g3 = gp3;
            g4 = gp4;
            g5 = gp5;
            cout << "pointer" << endl;
        }

    }



    void setpio1(int start_pulse, int end_pulse, int num_periods) {
        g1->GenerateVariablePWM(start_pulse, end_pulse, num_periods);
    }

    void setpio2(int start_pulse, int end_pulse, int num_periods) {
        g2->GenerateVariablePWM(start_pulse, end_pulse, num_periods);
    }

    void setpio3(int start_pulse, int end_pulse, int num_periods) {
        g3->GenerateVariablePWM(start_pulse, end_pulse, num_periods);
    }

    void setpio4(int start_pulse, int end_pulse, int num_periods) {
        g4->GenerateVariablePWM(start_pulse, end_pulse, num_periods);
    }

    void setpio5(int start_pulse, int end_pulse, int num_periods) {
        g5->GenerateVariablePWM(start_pulse, end_pulse, num_periods);
    }

    // first movement
    void gr1() {
        setpio1(600, 2400, 40);//move down
        setpio1(2400, 1000, 40); // grab
        setpio1(1000, 1000, 40);// move up
        setpio1(1000, 2400, 20);// throw

    }

    void wr1() {
        setpio2(1400, 1400, 40);
        setpio2(1400, 1400, 40);
        setpio2(1400, 1600, 40);
        setpio2(1600, 1000, 20);

    }
    void el1() {
        setpio3(1400, 600, 40);
        setpio3(600, 600, 40);
        setpio3(600, 1600, 40);
        setpio3(1600, 600, 20);

    }
    void bi1() {
        setpio4(1400, 1400, 40);
        setpio4(1400, 1100, 40);
        setpio4(1100, 1600, 40);
        setpio4(1600, 600, 20);
    }
    void ba1() {
        setpio5(1300, 900, 40);
        setpio5(900, 900, 40);
        setpio5(900, 1300, 40);
        setpio5(1300, 1300, 20);
    }

    // second movement
    void gr2() {
        setpio1(600, 2400, 50);//move down
        setpio1(2400, 1000, 50); // grab
        setpio1(1000, 1000, 50);// move up
        setpio1(1000, 2400, 20);// throw
        setpio1(2400, 2400, 50);
    }

    void wr2() {
        setpio2(1400, 1400, 50);
        setpio2(1400, 1400, 50);
        setpio2(1400, 1600, 50);
        setpio2(1400, 1000, 20);
        setpio2(1000, 1000, 50);
    }
    void el2() {
        setpio3(1400, 600, 50);
        setpio3(600, 600, 50);
        setpio3(600, 1600, 50);
        setpio3(1400, 600, 20);
        setpio3(600, 600, 50);
    }
    void bi2() {
        setpio4(1400, 1400, 50);
        setpio4(1400, 1100, 50);
        setpio4(1100, 2000, 50);
        setpio4(2000, 600, 20);
        setpio4(600, 600, 50);
    
}
    

    void ba2() {
        setpio5(1300, 1900, 50);
        setpio5(1900, 1900, 50);
        setpio5(1900, 1400, 50);
        setpio5(1400, 1400, 20);
        setpio5(1400, 1400, 50);
    
}


};





int main() {

    GPIO g1(0);
    GPIO g2(12);
    GPIO g3(11);
    GPIO g4(10);
    GPIO g5(13);

    ZedBoardToGPIO z(&g1, &g2, &g3, &g4, &g5);
    ZedBoard zedBoard;

     while (state) {
    if (zedBoard.PushButtonGet() == 3) {
        break;
     }    
    thread i11(&ZedBoardToGPIO::setpio1,z, 600,  600 ,20);
    thread i12(&ZedBoardToGPIO::setpio2,z, 1400, 1400 ,20);
    thread i13(&ZedBoardToGPIO::setpio3,z, 1400, 1400 ,20);
    thread i14(&ZedBoardToGPIO::setpio4,z, 1400, 1400 ,20);
    thread i15(&ZedBoardToGPIO::setpio5,z, 1300, 1300 ,20);

         i11.join();
         i12.join();
         i13.join();
         i14.join();
         i15.join();
     }

    //first move
    thread i111(&ZedBoardToGPIO::gr1,z);
    thread i112(&ZedBoardToGPIO::wr1,z);
    thread i113(&ZedBoardToGPIO::el1,z);
    thread i114(&ZedBoardToGPIO::bi1,z);
    thread i115(&ZedBoardToGPIO::ba1,z);
    i111.join();
    i112.join();
    i113.join();
    i114.join();
    i115.join();

    //second move
    thread i1(&ZedBoardToGPIO::gr2,z);
    thread i2(&ZedBoardToGPIO::wr2,z);
    thread i3(&ZedBoardToGPIO::el2,z);
    thread i4(&ZedBoardToGPIO::bi2,z);
    thread i5(&ZedBoardToGPIO::ba2,z);
    i1.join();
    i2.join();
    i3.join();
    i4.join();
    i5.join();

         while (state) {
    if (zedBoard.PushButtonGet() == 3) {
        break;
     }
    thread ia1(&ZedBoardToGPIO::setpio1,z, 600,  600 ,20);
    thread ia2(&ZedBoardToGPIO::setpio2,z, 1400, 1400 ,20);
    thread ia3(&ZedBoardToGPIO::setpio3,z, 1400, 1400 ,20);
    thread ia4(&ZedBoardToGPIO::setpio4,z, 1400, 1400 ,20);
    thread ia5(&ZedBoardToGPIO::setpio5,z, 1300, 1300 ,20);

         ia1.join();
         ia2.join();
         ia3.join();
         ia4.join();
         ia5.join();
     }


 return 0;
}
