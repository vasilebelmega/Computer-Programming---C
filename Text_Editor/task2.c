#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_BUFFER 14000
//Folosesc aceasta functie pentru a putea citi un text de la tastatura linie cu linie
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
		textTemp[i] = realloc(textTemp[i], (strlen(textTemp[i]) + 1) * sizeof(char));
		strtok(textTemp[i], "\n");
	}
	return textTemp;
}
//Aceasta functie primeste ca parametri 2 siruri 
int dist(char *sir1, char *sir2)
{
	int L = 0, i;
	char *sirMin, *sirMax;
	//Aflu care este sirul minim si cel maxim (in functie de lungime)
	if(strlen(sir1) < strlen(sir2))
	{
		sirMin = sir1;
		sirMax = sir2;
	}
	else
	{
		sirMin = sir2;
		sirMax = sir1;
	}
	//Parcurg sirul `sirMin` si adaug la distanta modulul diferentelor a fiecarui caracter din siruri in format ASCII
	for (i = 0; i < strlen(sirMin); i++)
		L += abs(sirMin[i] - sirMax[i]);
	//Parcurg sirul `sirMax` incepand de la cel `sirMin` si adaug  la distnta  diferenta dintre carcterul din sirMax si `\0` 
	for (i = strlen(sirMin); i < strlen(sirMax); i++)
		L += sirMax[i];
	return L;
}
/*Aceasta functie primeste ca parametru un `text` char **, numarul de linii, `nr` de linii al listei si numarul de aparitii
al fiecarui cuvant in text*/
char **creareLista(char **text, int N, int *nr, int **nrAparitii)
{	
	char **lista;
	int i, exista, sizeList = N, offset = N + 1;
	*nr = 0;

	lista = (char**)malloc(sizeList * sizeof(char*));
	(*nrAparitii) = (int*)malloc(sizeList * sizeof(int));

	for(i = 0; i < N; i++)
	{	
		int j = 0;
		while (j < strlen(text[i]))
		{
			int x;
			char *tmp = (char*)malloc((strlen(text[i]) + 1) * sizeof(char));
			while (j < strlen(text[i]) && !isalpha(text[i][j]) && !isdigit(text[i][j])) //Parcurgem linia si verificam daca avem cuvant valid
				j++;

			if (j > strlen(text[i]) - 1)
			{
				free(tmp);
				break;
			}
			//copiez intr-un vector temporar fiecare cuvant valid al randului din text si scap de toti separatorii 
			strcpy(tmp, text[i] + j);
			strtok(tmp, " \"\',?!");
			
			exista = 0;
			//parcurg toata lista si verific daca un cuvant a mai aparut in text , apoi cresc `nrAparitii`
			for(x = 0; x < *nr; x++)
			{
				if(strcmp(tmp ,lista[x]) == 0)
				{
					exista = 1;
					(*nrAparitii)[x]++;
					break;
				}
			}
			//daca nu a mai aparut in text  ii aloc memorie noua unui rand in lista si il copiez in zona noua de memorie 
			if(!exista)
			{	
				lista[*nr] = (char*)malloc((strlen(text[i]) + 1) * sizeof(char));	
				strcpy(lista[*nr], tmp);
				(*nrAparitii)[*nr] = 1;
				(*nr)++;
				/*Daca `nr` de linii al listei a ajuns egala cu numarul de linii al textului il tot maresc cat
				 am nevoie pentru a fi sigur ca sunt adaugate toate cuvintele din text , si tot fac realocare de memorie*/ 
				if ((*nr) == sizeList)
				{
					sizeList += offset;
					lista = (char**)realloc(lista, (sizeList + 1) * sizeof(char*));
					(*nrAparitii) = (int*)realloc(*nrAparitii, (sizeList + 1) * sizeof(int));
				}
			}

			j += strlen(tmp);
			free(tmp);
			while (j < strlen(text[i]) && !isalpha(text[i][j]) && !isdigit(text[i][j]))
				j++;
		}
	}

	return lista;
}
/*Aceasta functie primeste ca parametri `list` creata precedent , numarul de lini al textului `N` si nrAparitii*/
void sort(char **list, int N,int **p_nrAparitii)
{
	int i, j, aux;
	char *aux1, *aux2;
	int *nrAparitii= *p_nrAparitii;
	/*Fac sortarea prin metoda slect sort , in caz ca `nrAparitii` din lista al unui cuvant 
	este mai mic ca urmatorul fac sortarea descrescator dupa `nrAparitii`*/ 
	for(i = 0; i < N - 1; i++)
		for(j = i + 1; j < N; j++)
		{	
			if( nrAparitii[i] < nrAparitii[j])
			{	
				aux = nrAparitii[i];
				nrAparitii[i] = nrAparitii[j];
				nrAparitii[j] = aux;
				aux2 = list[i];
				list[i] = list[j];
				list[j] = aux2;
			}
			//Altfel in ordin crescatoarea lexicografic
			else if(nrAparitii[i] == nrAparitii[j])
				if(strcmp(list[i],list[j]) > 0)
				{	
					aux1 = list[i];
					list[i] = list[j];
					list[j] = aux1;
				}
		}
}
//Am facut aceasta functie pentru a calcula gradul de similitudine
int gradSim(char **list1, char **list2, int N, int M, int *nrAparitii1, int *nrAparitii2) 
{
	int i, nr, s = 0;
	if(N < M)
		nr = N;
	else
		nr = M;
	for(i = 0; i < nr; i++)
		s += (nrAparitii1[i] + nrAparitii2[i]) * dist(list1[i], list2[i]);
	return 100 * abs(N - M) + s;
}

int main()
{
	FILE *input = stdin;
	FILE *output = stdout;
	
	char **text1, **text2, **list1, **list2;
	int  N, i, M, j, nr1, nr2, gradSimilitudine = 0;
	int *nrAparitii1, *nrAparitii2;

	text1 = citireText(&N, input);
	text2 = citireText(&M, input);

	list1 = creareLista(text1, N, &nr1, &nrAparitii1);
	list2 = creareLista(text2, M, &nr2, &nrAparitii2);
	sort(list1, nr1, &nrAparitii1);
	sort(list2, nr2, &nrAparitii2);

	gradSimilitudine = gradSim(list1, list2, nr1, nr2, nrAparitii1, nrAparitii2);
	//eliberez memoria pe rand pentru fiecare rand din texte apoi pentru intreg textu , acelasi lucru si pentru lista , nrAparitii
	for (i = 0; i < N; i++)
                free(text1[i]);
        free(text1);
        for (i = 0; i < M; i++)
                free(text2[i]);
        free(text2);
        for (i = 0; i < nr1; i++)
                free(list1[i]);
        free(list1);
        for (i = 0; i < nr2; i++)
                free(list2[i]);
        free(list2);
        free(nrAparitii1);
        free(nrAparitii2);
    //afisare rezultat
	printf("%d", gradSimilitudine);
	return 0;
}
