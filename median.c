#include <avr/io.h>

/*uint16_t adc []={400, 1278, 2890, 1554, 9876}; */
	uint8_t t=0;
	uint16_t k=1500;
	uint16_t input[];

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
	if(input[0] >= input[1])
	{
		swap(&input[0], &input[1]);
	}


	if(input[2] >= input[3])
	{
		swap(&input[2], &input[3]);
	}


	if(input[1] >= input[3])
	{
		swap(&input[0], &input[2]);
		swap(&input[1], &input[3]);
	}


	if(input[4] <= input[1])          //<
	{
		if(input[4] <= input[0])
		{
			swap(&input[0], &input[4]);
			swap(&input[4], &input[1]);
			swap(&input[4], &input[3]);
		}
	}	
		else if(input[4] <= input[3])				//else if
		{
			swap(&input[4], &input[3]);
		}
	


	if(input[2] <= input[1])
	{
		if(input[2] <= input[0])
		{
			swap(&input[0], &input[2]);
			swap(&input[1], &input[2]);
		}
	}	
		else if(input[2] >= input[3])
		{
			swap(&input[2], &input[3]);
		}
	
return;
}		

 
 /*void new_bubblesort(const uint16_t* input, maxIndex)
 {
	 for (int x=0; x < maxIndex; x++)
		for (int y=0; y < maxIndex-x; y++)
			if (input[y] > input[y+1])
			{
				swap(&input[y], &input[y+1]);
			}				
			
	return;
 }
 */