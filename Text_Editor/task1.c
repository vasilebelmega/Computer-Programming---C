#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER 14000

char **citireText(int *N, FILE *input)
{
	char **textTemp;
	int i;
	fscanf(input, "%d\n", N);
	textTemp = (char**)malloc(*N * sizeof(char*));

	for (i = 0; i < *N; i++)
	{
		textTemp[i] = (char*)malloc(MAX_BUFFER * sizeof(char));
		fgets(textTemp[i], MAX_BUFFER, input);
		textTemp[i] = realloc(textTemp[i], strlen(textTemp[i]) * sizeof(char) + 1);
		strtok(textTemp[i], "\n");
	}
	return textTemp;
}

void afisareText(char **text, int N)
{
	int i;
	printf("%d\n", N);
	for (i = 0; i < N; i++)
		printf("%s\n", text[i]);
}

void eliberareMemorie(char **text, char **operatii, int N, int M)
{
	int i;
	for (i = 0; i < N; i++)
		free(text[i]);
	free(text);
	for (i = 0; i < M; i++)
		free(operatii[i]);
	free(operatii);
}

void replaceString(char **text, int N, char *string1, char *string2)
{
	int i, x;
	for (i = 0; i < N; i++)
	{	
		int  k = strlen(text[i]) * 100;
		if( k > MAX_BUFFER)
			k = MAX_BUFFER;
		char *buffer = (char*)malloc (k * sizeof(char));
		char *tmp = (char*)malloc(strlen(text[i]) * sizeof(char) + 1);
		char *aux = tmp;
		memset(buffer, '\0', k);
		strcpy(tmp, text[i]);

		if (!strstr(text[i], string1)) // daca nu avem cuvantul string1 in text[i], lasam linia exact cum era
			continue;

		while (tmp = strstr(tmp, string1))
		{
			char prec = *(tmp - 1);
			char next = *(tmp + strlen(string1));
			int precIsValid = !isascii(prec) || (isascii(prec) && !isalpha(prec) && !isdigit(prec));
			int nextIsValid = !isascii(next) || (isascii(next) && !isalpha(next) && !isdigit(next));
			if (precIsValid && nextIsValid)
			{
				char *p = (char*)malloc((tmp - aux) * sizeof(char) + 1);
				strncpy(p, aux, tmp - aux);
				p[tmp - aux] = '\0';
				sprintf(buffer, "%s%s", buffer, p);
				sprintf(buffer, "%s%s", buffer, string2);
				free(p);
			}

			tmp += strlen(string1);
			if (precIsValid && nextIsValid)
				aux = tmp;
		}

		// adaug si ce a mai ramas dupa ultima inlocuire a cuvantului 1
		sprintf(buffer, "%s%s", buffer, aux);
		buffer = (char*)realloc(buffer, strlen(buffer) * sizeof(char) + 1);
		text[i] = (char*)realloc(text[i], strnlen(buffer, MAX_BUFFER) * sizeof(char) + 1);
		strcpy(text[i], buffer);
		free(buffer);
		free(tmp);
	}
}

int countOccurences(char **text, int N, char *word)
{
	int contor = 0, i;
	for (i = 0; i < N; i++)
	{
		char *tmp;
		tmp = (char*)malloc(strlen(text[i]) * sizeof(char) + 1);
		strcpy(tmp, text[i]);
		while (tmp = strstr(tmp, word))
		{
			char prec = *(tmp - 1);
			char next = *(tmp + strlen(word));
			int precIsValid = !isascii(prec) || (isascii(prec) && !isalpha(prec) && !isdigit(prec));
			int nextIsValid = !isascii(next) || (isascii(next) && !isalpha(next) && !isdigit(next));
			if (precIsValid && nextIsValid)
				contor++;

			tmp += strlen(word);
		}
		free(tmp);
	}
	return contor;
}

void shiftCuvant(char *cuvant, int k)
{
	char *sir1;
	char *sir2;
	k = k % strlen(cuvant);
	sir1 = cuvant + (strlen(cuvant) - k);
	sir2 = (char*)malloc(MAX_BUFFER * sizeof(char));

	strncpy(sir2, cuvant, strlen(cuvant) - k);
	sir2[strlen(cuvant) - k] = '\0';

	sprintf(cuvant, "%s%s", sir1, sir2); 
	free(sir2);
}

void shiftText(char **text, int N, int k)
{
	int i = 0;
	for (i = 0; i < N; i++)
	{
		int j = 0;
		while (j < strlen(text[i]))
		{
			int x = 0;
			char *tmp = (char*)malloc(strlen(text[i]) * sizeof(char) + 1);
			while (j < strlen(text[i]) && !isalpha(text[i][j]) && !isdigit(text[i][j]))
				j++;

			if (j >= strlen(text[i]) - 1)
			{
				free(tmp);
				break;
			}

			strcpy(tmp, text[i] + j);
			strtok(tmp, " \"\',?!"); 
			shiftCuvant(tmp, k);

			while (x < strlen(tmp))
			{
				text[i][j] = tmp[x];
				x++;
				j++;
			}
			
			while (j < strlen(text[i]) && !isalpha(text[i][j]) && !isdigit(text[i][j]))
				j++;
 
			free(tmp);
		}
	}
}

int main()
{
	FILE *input = stdin;
	FILE *output = stdout;
	char **text, **operatii;
	int  N, i, M, j;

	text = citireText(&N, input);
	operatii = citireText(&M, input);

	for (i = 0; i < M; i++)
	{
		if (operatii[i][0] == '1')
		{
			fprintf(output, "%d\n", countOccurences(text, N, operatii[i] + 2));
		}
		else if (operatii[i][0] == '2')
		{
			char *cuvant1 = strtok(operatii[i] + 2, " ");
			char *cuvant2 = strtok(operatii[i] + 2 + strlen(cuvant1) + 1," \"\',!?");
			replaceString(text, N, cuvant1, cuvant2);
			for (j = 0; j < N; j++)
				if (text[j][0] == 10)
					fprintf(output, "%s", text[j]);
				else 
					fprintf(output, "%s\n", text[j]);
		}
		else if (operatii[i][0] == '3')
		{
			int k = atoi(operatii[i] + 2);
			shiftText(text, N, k);
			for (j = 0; j < N; j++)
				if (text[j][0] == 10)
					fprintf(output, "%s", text[j]);
				else 
					fprintf(output, "%s\n", text[j]);
		}
	}

	eliberareMemorie(text, operatii, N, M);

	return 0;
}
