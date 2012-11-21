#include <avr/io.h>

/*uint16_t adc []={400, 1278, 2890, 1554, 9876}; */
	uint8_t t=0;
	uint16_t k=1500;
	uint16_t adc[];

void swap(uint16_t *a, uint16_t *b) 
{
    uint16_t temp;
 
    temp = *a;
    *a = *b;
    *b = temp; 
	
	return; 
}

// void median(void)
// {
// 	// 	if(adc[4] < adc[0]) swap(&adc[4], &adc[0]);
// // 	if(adc[4] < adc[1]) swap(&adc[4], &adc[1]);
// // 	
// 	
// if(adc[0] > adc[1]) swap(&adc[0], &adc[1]);
// 
// 	
// if(adc[2] > adc[3]) swap(&adc[2], &adc[3]);
// 
// 	
// if(adc[1] > adc[3])
// {
// 	swap(&adc[0], &adc[2]);
// 	swap(&adc[1], &adc[3]);
// }
// 
// if(adc[4] < adc[1])
// {
// 	if(adc[4] < adc[0])
// 	{
// 		swap(&adc[0], &adc[4]);
// 		swap(&adc[4], &adc[1]);
// 		swap(&adc[4], &adc[3]);
// 	}
// 
// 	else if(adc[4] < adc [3]) swap(&adc[4], &adc[3]);
// 		
// }	
// 
// // if(adc[2] < adc[1]) swap(&adc[2], &adc[1]);
// // if(adc[2] < adc[0])	swap(&adc[2], &adc[0]);
// 
// 
// 	if(adc[2] < adc[0])
// 	{	if(adc[2] < adc[0])
// 		{
// 			swap(&adc[0], &adc[2]);
// 			swap(&adc[1], &adc[2]);  //swap(&adc[1], &adc[2]);
// 		}		
// 	else if(adc[2] > adc[3]) swap(&adc[2], &adc[3]);
// 		}	
// /*if(adc[1] > adc[2]) swap(&adc[1], &adc[2]);*/
// return;
// }


void median(void)
{
	if(adc[0] > adc[1])
{
	swap(&adc[0], &adc[1]);
}

if(adc[2] > adc[3])
{
	swap(&adc[2], &adc[3]);
}

if(adc[1] > adc[3])
{
	swap(&adc[0], &adc[2]);
	swap(&adc[1], &adc[3]);
}

if(adc[4] < adc[1])
{
	if(adc[4] < adc[0])
	{
		swap(&adc[0], &adc[4]);
		swap(&adc[4], &adc[1]);
		swap(&adc[4], &adc[3]);
	}
	else if(adc[4] < adc[3])
	{
		swap(&adc[4], &adc[3]);
	}
}

if(adc[2] < adc[1])
{
	if(adc[2] < adc[0])
	{
		swap(&adc[0], &adc[2]);
		swap(&adc[1], &adc[2]);
	}
	else if(adc[2] > adc[3])
	{
		swap(&adc[2], &adc[3]);
	}
}
}		
