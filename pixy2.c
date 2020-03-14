#include "pixy2.h"

char *getSignature(uint8_t b){
    if(b == 0x01){
        return "RED";
    }
    else if(b == 0x02){
        return "GREEN";
    }
    else if(b == 0x03){
        return "BLUE";
    }
    else{
        return "NONE";
    }
}

uint16_t getCenter(uint8_t upperB, uint8_t lowerB){
    uint16_t ret = 0x0000;
    ret = ((ret|upperB)<<4 | lowerB);
    

    
    return ret;
}

int isCenter(uint16_t x, uint16_t width){
    int l1 = x - width/2;
    int l2 = X_MAX - x - width/2;
    if(abs(l2-l1)<THRESHOLD){
        return 1;
    }
    else{
        return 0;
    }
}

int getDistance(uint16_t width){
    int temp = (width*35)/200;
    return 35-temp;
}



void debugPIXY(uint8_t *data){
    char pixy[3];
    int i = 0;
    for(i = 0; i < 20; i++){
        sprintf(pixy,"%d ",data[i]);
        UARTSendString(pixy);
    }
    UARTSendString("\r\n");
}