

#include "tlgh.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#define MAX_BUFFER 100

size_t M;
FILE *input, *output;


typedef struct { char *Key, *Value; int Frequency; }TCache;

//return codHash for to know where do insertion
int codHash(void*a)
{
	size_t i, sum = 0;
	char *c = ((TCache*)a)->Key;
	for (i = 0; i < strlen(c); i++)
		sum += c[i];
	return sum % M;
}

//function for free structure
void elibCache(void * p)
{
	free(((TCache*)p)->Key);
	free(((TCache*)p)->Value);
	free((TCache*)p);
}
//compare key
int cmpCacheKey(void *p1, void*p2)
{
	return strcmp(((TCache*)p1)->Key, ((TCache*)p2)->Key);
}
//compare Frequency
int cmpCacheFreq(void* p1, void* p2)
{
	return ((TCache*)p1)->Frequency - ((TCache*)p2)->Frequency;
}

void AfiElCache(void * ae)
{
	TCache *c = (TCache*)ae;
	fprintf(output, "(%s)", c->Value);
}

//do a copy for an element
void* copie(void* el)
{
	TCache* p = (TCache*)el, *rez;
	rez = (TCache*)malloc(sizeof(TCache));
	if (!rez) return NULL;
	rez->Key = strdup(p->Key);
	if (!rez->Key) { free(rez); return NULL; }
	rez->Value = strdup(p->Value);
	if (!rez->Value) { free(rez->Key); free(rez); return NULL; }
	rez->Frequency = p->Frequency;
	return rez;

}
//make set in table hash with key and value
void* set(TH **hashTable, char *Key, char *Value)
{
	TCache* entry;
	entry = (TCache*)malloc(sizeof(TCache));
	if (!entry) return NULL;

	entry->Frequency = 0;
	entry->Key = strdup(Key);
	if (!entry->Key) { free(entry); return NULL; }

	entry->Value = strdup(Value);
	if (!entry->Value) { free(entry->Key); free(entry); return NULL; }
	//insert element in table
	InsTH(*hashTable, (TCache*)entry, sizeof(TCache), cmpCacheKey, cmpCacheFreq, elibCache); 
	free(entry);

	return NULL;
}

char *get(TH** hashTable, char *Key)
{
	int cod = 0; 
	int countInList = 0; // gets the position of our "Key" in its list
	TCache* entry;
	TLG p;

	entry = (TCache*)malloc(sizeof(TCache));
	if (!entry) return NULL;
	entry->Key = strdup(Key); // create a dummy entry, just to use it bellow for our functions
	
	cod = codHash((TCache*)entry); // get the index in the table where "Key" is located
	p = (*hashTable)->v[cod];      

	for (; p != NULL; p = p->urm) // locate the value for "Key" element
	{
		if (!cmpCacheKey(p->info, entry)) // found our value!
		{
			free(entry->Key);
			free(entry);
			entry = (TCache*)copie((TCache*)p->info); // make a new entry, which is like the old one, with increased Frequency
			entry->Frequency++;

			// delete our entry and reinsert it with its new Frequency (inserts it respecting the established rules)
			DistrugeLG(&(*hashTable)->v[cod], countInList, elibCache); 
			InsTH(*hashTable, (TCache*)entry, sizeof(TCache), cmpCacheKey, cmpCacheFreq, elibCache);
			return entry->Value;
		}
		countInList++;
	}
	
	free(entry->Key);
	free(entry);
	return "NULL";
}

void removeCache(TH** hashTable, char *Key)
{
	int cod = 0; 
	TCache* entry;
	int countInList = 0; // gets the position of our "Key" in its list
	TLG p;

	entry = (TCache*)malloc(sizeof(TCache));
	if (!entry) return;
	entry->Key = strdup(Key); // create a dummy entry, just to use it bellow for our functions

	cod = codHash((TCache*)entry); // get the index in the table where "Key" is located
	p = (*hashTable)->v[cod];      

	for (; p != NULL; p = p->urm) // locate the value for "Key" element
	{
		if (!cmpCacheKey(p->info, entry)) // found our value!
		{
			free(entry);	
			DistrugeLG(&(*hashTable)->v[cod], countInList, elibCache); 
			return;
		}
		countInList++;
	}
}

int main(int argc, char** argv)
{
	TH *h = NULL;
	TLG* p;
	char *buffer;
	char *x;
	char *key, *value;
	int index = 0, count = 0;
	

	/**********************************************************/
	M = atoi(argv[1]);
	input = fopen(argv[2],"rt");
	if(input == NULL) return 0;
	output = fopen(argv[3],"wt");
	if(output == NULL) return 0;
	/**********************************************************/

	h = (TH*)IniTH(M, codHash);
	if (!h)	return 0;

	buffer = (char*)malloc(MAX_BUFFER * sizeof(char));
	key = (char*)malloc(200 * sizeof(char));
	value = (char*)malloc(200 * sizeof(char));
	while(fscanf(input,"%s", buffer) != EOF)
	{
		if(!strcmp(buffer, "set"))
		{
			fscanf(input,"%s %s", key, value);
			set(&h, key, value);

			// check for 2*M entries
			count = 0;
			for (p = h->v; p<h->v + h->M; p++)
			{
				count += LungimeLG(p);
			}
			if(count > M * 2)
			{
				h->v = (TLG*)realloc((h->v),(h->M) * 2 * sizeof(TLG));
				if (h->v)
				{
					for (index = M; index < 2 * M; index++)
						h->v[index] = NULL;
					M *= 2;
					h->M *= 2;
				}		
			}
		}
		else if(!strcmp(buffer, "get"))
		{
			fscanf(input,"%s", key);
			x = get(&h, key);
			fprintf(output, "%s\n", x);
			
		}
		else if(!strcmp(buffer, "remove"))
		{
			fscanf(input,"%s", key);
			removeCache(&h, key);
		}
		else if(!strcmp(buffer, "print"))
		{
			AfiTH(h, AfiElCache);
		}
		else if(!strcmp(buffer, "print_list"))
		{
			fscanf(input,"%d", &index);
			if (index < h->M)
				AfiTHIndex(h, AfiElCache, index);
		}
	}

	DistrTH(&h, elibCache);
	free(buffer);
	fclose(input);
	fclose(output);
	
	return 0;
}

