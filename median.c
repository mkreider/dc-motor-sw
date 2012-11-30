#include <avr/io.h>

void swap(uint16_t *a, uint16_t *b) 
{
    uint16_t temp;
 
    temp = *a;
    *a = *b;
    *b = temp; 
	
	return; 
}


void median(const uint16_t* input)
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


	if(*pE <= *pB)    //<
	{
		if (*pE <= *pA)
		{
			swap(pA, pE);
			
		}
		swap(pE, pB);
		swap(pE, pD);
	}	
	else if(*pE < *pD)				//else if
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
	else if(*pC > *pD)				// >=
	{
		swap(pC, pD);
	}
		
return;
}		

 
 uint16_t* new_bubblesort(const uint16_t* input, uint16_t len)
 {
	 uint16_t* sorted = (uint16_t*)input;
	 uint16_t x,y;
	 
	  for ( x=0; x < (len-1); x++)
	 {
		for (y=0; y < (len-x-1); y++)
			if (sorted[y] > sorted[y+1]) swap(&sorted[y], &sorted[y+1]);
	}			
	return sorted;
 }
 
  uint8_t sortCheck(const uint16_t* arrayA, const uint16_t* arrayB, uint16_t len)
 {
	 uint16_t i;
	 
	 for ( i=0; i < len; i++)
	 {
		if(arrayA[i] != arrayB[i]) return 1;
	}			
	return 0;
 }
 