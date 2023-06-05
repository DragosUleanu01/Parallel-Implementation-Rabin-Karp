//Uleanu Dragos -> Rabin-Karp

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

#define d 10

void rabinKarp(char pattern[], char text[], int q)
{
	int m = strlen(pattern); //Lungime Tipar
	int n = strlen(text); //Lungime Text
	int i, j;
	int p = 0; //Valoare conventie tipar;
	int t = 0; //Valoare Conventie text;
	int h = 1;
	int alpha = 0;
	int vector[20];

	//Paralelizam loop-ul for. Variabilele shared sunt utilizate in mai multe threaduri. Variabila J 
	//este folosita de fiecare thread ca o copie.
	
	for (i = 0; i < m - 1; i++)
	{
		h = (h * d) % q;
	}

	//Se calculeaza conventia pentru tipar si text;


	for (i = 0; i < m; i++)
	{
		p = (d * p + pattern[i]) % q;
		t = (d * t + text[i]) % q;
	}

	//Se cauta potriviri;

	#pragma omp parallel for shared(pattern, text, q, m, n, h, p, t) private(i, j)
	for (i = 0; i <= n - m; i++)
	{
		
		if (p == t)
		{
			
			for (j = 0; j < m; j++)
			{
				
				if (text[i + j] != pattern[j])
				{
					break;
				}
			}
		
			if (j == m)
			{
				
				printf("S-a gasit tiparul la pozitia %d \n", i + 1);
			}
		}
		if (i < n - m)
		{
			t = (d * (t - text[i] * h) + text[i + m]) % q;
			if (t < 0)
			{
				t = (t + q);
			}
		}
	}
	
}

int main()
{
	clock_t start, end;
	double executionTime;
	
	start = clock();
	char text[] = "ABCCDDAEFG";
	char pattern[] = "CDD";
	int q = 13;
	rabinKarp(pattern, text, q);

	end = clock();
	executionTime = ((double(end - start)));
	printf("S-a executat in %f", executionTime);
}