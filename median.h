#ifndef _MEDIAN_H_
#define _MEDIAN_H_

#include "median.h"

typedef struct
{
        uint16_t  mem[5];
        uint16_t* pInsPos;

} ringbuffer;


uint16_t median(const uint16_t* input);
void swap(uint16_t *a, uint16_t *b);

ringbuffer* rbInit(ringbuffer* rBuf);
ringbuffer* rbInsert(ringbuffer* rBuf, uint16_t newVal);


   
#endif
