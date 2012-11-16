/* median.h
Verarbeitung der ADC-Werte aus dem Array "uint16_t adc [5]"

*/

#include <avr/io.h>
#include <stdlib.h>


uint8_t adc[5]={5, 4, 3, 2, 1};
	
void swap(uint8_t *a, uint8_t *b) 
{
    uint8_t temp;
 
    temp = *a;
    *a = *b;
    *b = temp;  
}

uart_putuint16((uint16_t)adc[i])
uart_putc(' ');
		
if(adc[0] > adc[1])
{
	swap(adc[1], adc[2]);
}

if(adc[3] > adc[4])
{
	swap(adc[3], adc[4]);
}

if(adc[2] > adc[4])
{
	swap(adc[1], adc[3]);
	swap(adc[2], adc[4]);
}

if(adc[5] < adc[2])
	if(adc[5] < adc[1])
{
	swap(adc[1], adc[5]);
	swap(adc[5], adc[2]);
	swap(adc[5], adc[4]);
}
	else if(adc[5] < adc [4])
	{
		swap(adc[5], adc[4]);
	}

if(adc[3] < adc[2])
{	if(adc[3] < adc[1])
	{
		swap(adc[1], adc[3]);
		swap(adc[2], adc[3]);
	}		
	else if(adc[3] > adc[4])
	{
		swap(adc[3], adc[4]);
	}
}		
	}

// 	if(a>=b)			//if(adc[1] >= adc[2])
// 	{
// 		swap(a, b);
// 	}	
// 	
// 	if(d>=e)			//if(adc[4] >= adc[5]) usw
// 	{
// 		swap(d, e);
// 	}
// 	
// 	if(b>=e)
// 	{
// 		swap(b, e);
// 		swap(d, a);
// 	}
// 	
// 	if(c>=b)
// 	{
// 		swap(c, b);
// 	}
// 	
// 		else if(d)
		
	
/*
Swapfunktion

void swap(int *a, int *b) 
{
    int temp;
 
    temp = *a;
    *a = *b;
    *b = temp;  
}

1) use 3 comparisons to arrange elements in array such that a[1]<a[2] , a[4]<a[5] and a[1]<a[4]
a) compare a[1] and a[2] and swap if necessary
b) compare a[4] and a[5] and swap if necessary 
c) compare a[1] and a[4].if a[4] is smaller than a[1] , then swap a[1] wid a[4] and a[2] wid a[5]
2)if a[3]>a[2].if a[2]<a[4] median value = min(a[3],a[4]) else median value=min(a[2],a[5]) 
3)if a[3]<a[2].if a[3]>a[4] median value = min(a[3],a[5]) else median value=min(a[2],a[4]) 


*/
