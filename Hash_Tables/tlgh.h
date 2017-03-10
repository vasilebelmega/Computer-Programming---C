


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


typedef struct celulag
{
	void* info;           /* adresa informatie */
	struct celulag *urm, *prec;   /* adresa urmatoarei celule */
} TCelulaG, *TLG, **ALG;


typedef int(*TFElem)(void*);     /* functie prelucrare element */
typedef int(*TFCmp)(void*, void*); /* functie de comparare doua elemente */

typedef void(*TF)(void*);     /* functie afisare/eliberare un element */

typedef int(*TFHash)(void*);

typedef struct
{
	size_t M;
	TFHash fh;
	TLG *v;
} TH;

int InsLG(ALG, void*, size_t, TFCmp fCmp, TFCmp fFreqCmp);

void DistrugeLG(ALG, size_t index, TF fe); /* eliminare celula si element */

void Distruge(ALG aL, TF fe); /* distruge lista */

size_t LungimeLG(ALG);   /* numarul de elemente din lista */

						 /* afiseaza elementele din lista, folosind o functie de tip TFAfi */
void Afisare(ALG, TF);
void* copie(void* el);
TH* IniTH(size_t M, TFHash fh);
void DistrTH(TH**aa, TF fe);
void AfiTH(TH*a, TF afiEl);
void *ExistaTH(TH*a, void*ae, TFCmp f);
int InsTH(TH*a, void*ae, size_t d, TFCmp f, TFCmp fFreq, TF free_elem);
int ExtrTH(TH*a, void*ae, TFCmp f);
void AfiTHIndex(TH*ahIndex, TF afiEl, int index);
