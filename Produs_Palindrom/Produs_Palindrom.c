#include <stdio.h>
	//functia verifica daca un numar este palindrom
	int palindrom(int a)
	{
		int x = 0, b;
		b = a;
                if (a == 0) return 1;
		while(a)
		{
			x = x * 10 + a % 10;
			a = a / 10;
		}
		if(x == b)
			return 1;
		else
			return 0;
	}

	//functia returneaza numarul de cifre al unui numar
	int nrCifre(int a)
	{
		int contor = 0;
		if (a == 0) return 1;
		while(a)
		{
			a = a / 10;
			contor++;
		}
		return contor;
	}
	
	/*functia verifica daca numarul de cifre ai termenilor produsilor 
	egali cu p */
	int produsPalindrom(int a, int p)
	{
		if (a == 0) {
			if (p == 1) return 1;
			else return 0;
		}
		int d, c;
		for(d = 1; d <= a / 2; d++)
		{	
			if(a % d == 0)
			{
				c = a / d;
			       //verifica daca termenii produsului sunt diferiti
				if(c == d)
					break;
				if((nrCifre(d) == p) && (nrCifre(c) == p))
				{	
					return 1;
				}
			}
		}
		return 0;
	}
	
	int main()
	{	
		int x, i, p,contor = 0;

		scanf("%d %d", &p, &x);
		
		for( i = 0; i < x; i++)
		{
			if(palindrom(i) && produsPalindrom(i, p))
				contor++;
		}
		printf("%d\n", contor);
		return 0;
	}
