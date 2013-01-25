/**
 * @file median.c
 *
 *
 * @brief Median filter function to smooth ADC samples
 */

/*
 * Copyright (c) YYYY Author.
 *
 */

#include <avr/io.h>
#include "median.h"

void swap(uint16_t *a, uint16_t *b) 
{
    uint16_t temp;
 
    temp = *a;
    *a = *b;
    *b = temp; 
	
	return; 
}


uint16_t median(const uint16_t* input)
{
	uint16_t* pA = (uint16_t*)&input[0];
	uint16_t* pB = (uint16_t*)&input[1];
	uint16_t* pC = (uint16_t*)&input[2];
	uint16_t* pD = (uint16_t*)&input[3];
	uint16_t* pE = (uint16_t*)&input[4];
	
	if(*pA > *pB)
	{
		swap(pA, pB);
	}


	if(*pC > *pD)
	{
		swap(pC, pD);
	}


	if(*pB > *pD)
	{
		swap(pA, pC);
		swap(pB, pD);
	}


	if(*pE <= *pB)    
	{
		if (*pE <= *pA)
		{
			swap(pA, pE);
			
		}
		swap(pE, pB);
		swap(pE, pD);
	}	
	else if(*pE < *pD)				
	{
		swap(pE, pD);
	}
	


	if(*pC < *pB)
	{	
		if (*pC <= *pA)
		{
			swap(pA, pC);
			
		}
		swap(pB, pC);			
	}	
	else if(*pC > *pD)			
	{
		swap(pC, pD);
	}
	
	//return middle value of 5	
	return *pC;
}


ringbuffer* rbInit(ringbuffer* rBuf)
{
        uint8_t i;
        for(i=0; i<5; i++) rBuf->mem[i] = 0;
        rBuf->pInsPos = &rBuf->mem[0];

        return rBuf;
}


ringbuffer* rbInsert(ringbuffer* rBuf, uint16_t newVal)
{
        *rBuf->pInsPos = newVal;
        if(rBuf->pInsPos - &rBuf->mem[0] == 4)  rBuf->pInsPos = &rBuf->mem[0];
        else                            		rBuf->pInsPos++;

        return rBuf;
}
 
