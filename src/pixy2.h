#ifndef PIXY2_H    /* Guard against multiple inclusion */
#define PIXY2_H

#include "stdint.h"
#include "stdio.h"
#include "app.h"

#define GET_BLOCK_CMD_LENGTH 6
#define GET_VERSION_CMD_LENGTH 4
#define PAYLOAD_LENGTH_BYTE 3
#define SIGNATURE_BYTE 6
#define CENTERX_UPPER_BYTE 9
#define CENTERX_LOWER_BYTE 8
#define CENTERY_UPPER_BYTE 11
#define CENTERY_LOWER_BYTE 10
#define OBJECT_WIDTH_UPPER_BYTE 13
#define OBJECT_WIDTH_LOWER_BYTE 12
#define OBJECT_HEIGHT_UPPER_BYTE 15
#define OBJECT_HEIGHT_LOWER_BYTE 14
#define X_MAX 315
#define Y_MAX 207
#define THRESHOLD 20


static uint8_t blockRequest[] =
{
    0xae,  // first byte of no_checksum_sync (little endian -> least-significant byte first)
    0xc1,  // second byte of no_checksum_sync
    0x20,
    0x02,
    0x07,  
    0x01  
};

static uint8_t turnOnLamp[] =
{
    0xae,  // first byte of no_checksum_sync (little endian -> least-significant byte first)
    0xc1,  // second byte of no_checksum_sync
    0x16,
    0x02,
    0x01,  
    0x00 
};

char *getSignature(uint8_t b);

uint16_t getCenter(uint8_t upperB, uint8_t lowerB);

int isCenter(uint16_t x, uint16_t y);

int getDistance(uint16_t width);
    
#endif /* _EXAMPLE_FILE_NAME_H */