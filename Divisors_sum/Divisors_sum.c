#include <stdio.h>
    /* Returns 1 if divisors sum of `a` equals `b`, 0 otherwise */
    int sumDiv(int a, int b) 
    {
    	int i, s = 0;
    	for( i = 1; i <= a / 2; i++)
    	{
			if (a % i == 0)
    			s = s + i;
    		if(s > b)
    			break;
    	}
    	return s == b;
    }
    
    /* Reads an int value `k` and prints pairs of numbers less than `k` that verify `sumDiv` property */
    int main()
    {
    	int k, a, b;
    
    	scanf("%d",&k); 
    	for (a = 1; a < k; a++)
    	{
    		int j, sumDiva=0;
    		for(j = 1; j <= a / 2; j++)
    			if(a % j == 0)
    			sumDiva += j;
		
    	    for (b = a + 1; b < k; b++)
    	    {
				if(sumDiva < b)
					break;
    	    	if (sumDiva == b && sumDiv(b, a))
    	    		printf("(%d,%d)\n", a, b);
    
		   }   
		}
    return 0;	    
	}
    
