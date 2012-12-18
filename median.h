#ifndef _MEDIAN_H_
#define _MEDIAN_H_

typedef struct
{
        uint16_t  mem[5];
        uint16_t* pInsPos;

} ringbuffer;


void median(const uint16_t* input);
void swap(uint16_t *a, uint16_t *b);

uint16_t* rbInit(ringbuffer* rBuf);
uint16_t* rbInsert(ringbuffer* rBuf, uint16_t newVal);


   
#endif
