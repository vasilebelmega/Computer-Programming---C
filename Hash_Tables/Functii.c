

#include "tlgh.h"

extern FILE* output;

int InsLG(ALG aL, void* ae, size_t d, TFCmp fCmp, TFCmp fFreqCmp)
{
	TLG q, p = *aL;
	TLG aux = (TLG)malloc(sizeof(TCelulaG));
	if (!aux) return 0;
	aux->info = malloc(d);
	if (!aux->info)
	{
		free(aux); return 0;
	}
	memcpy(aux->info, ae, d);
 
	if (LungimeLG(aL) == 0) // empty list, just insert it
	{
		aux->urm = NULL;
		aux->prec = NULL;
		*aL = aux;
		return 1;
	}
	else for (; p!= NULL; p = p->urm)  // now we are triyng to insert "aux" where it belongs
	{
		if (fFreqCmp(aux->info, p->info) > 0)   
		{
			if (p == *aL) // insert before first if "aux" is has the highest frequency
			{
				aux->urm = *aL;
				aux->prec = NULL;
				if (*aL)
					aux->urm->prec = aux;
				*aL = aux;
			}
			else  //"aux" has the highest frequency, insert in front of current position (p)
			{
				aux->urm = p;
				if (p->prec)
					p->prec->urm = aux;
				aux->prec = p->prec;
				p->prec = aux;
			}
			return 1; 
		}
		else if (fFreqCmp(aux->info, p->info) == 0) // same frequency, now order alphabeticaly here
		{
			for (; p != NULL && fFreqCmp(aux->info, p->info) == 0 && fCmp(aux->info, p->info) > 0; p = p ->urm)
				q = p; // save in q before p gets NULL
			
			if (p == NULL) // reached the end of the list, just insert it here
			{
				aux->urm = NULL;
				aux->prec = q;
				q->urm = aux;
			}
			else // insert "aux" before "p" 
			{
				aux->urm = p;
				if (p->prec)
					p->prec->urm = aux;
				aux->prec = p->prec;
				p->prec = aux;
				if (p == *aL)
					*aL = aux;
			}
			return 1;
		}
		q = p; // save in q before p gets NULL
	}

	if (p == NULL) // reached the end of the list, just insert it here
	{
		aux->urm = NULL;
		aux->prec = q;
		q->urm = aux;
	}

	return 1;
}

void DistrugeLG(ALG aL, size_t index, TF free_elem) /* eliminare celula si element */
{
	TLG aux = *aL;     /* adresa celulei eliminate */
	if (index == 0)    // if first element is being deleted, move aL to the next one
		*aL = aux->urm;
	while (index)
	{
		aux = aux->urm;
		index--;
	}

	if (!aux) return; /* lista vida */	

	if (aux->prec != NULL)
	{
		aux->prec->urm = aux->urm;
		if (aux->urm != NULL)
		{
			aux->urm->prec = aux->prec;
		}
	}
	else if (aux->urm != NULL)
	{
		aux->urm->prec = NULL;
	}
	else
	{
		*aL = NULL;
	}

	free_elem(aux->info);  /* elib.spatiul ocupat de element*/
	free(aux);   /* elibereaza spatiul ocupat de celula */
}

void Distruge(ALG aL, TF free_elem) /* distruge lista */
{
	while (*aL != NULL)
		DistrugeLG(aL, 0, free_elem);
}

size_t LungimeLG(ALG a)      /* numarul de elemente din lista */
{
	size_t lg = 0;
	TLG p = *a;
	for (; p != NULL; p = p->urm) lg++;  /* parcurge lista, numarand celulele */
	return lg;
}

void Afisare(ALG aL, TF afiEL)
{
	if (!*aL) { fprintf(output, "Lista vida\n"); return; }
	fprintf(output, "Lista: ");
	for (; *aL; aL = &(*aL)->urm)
		afiEL((*aL)->info);
	fprintf(output, "\n");
}

/********************** HASTABLE FUNCTIONS *******************/

TH* IniTH(size_t M, TFHash fh)
{
	TH*h = (TH*)calloc(sizeof(TH), 1);
	if (!h)
	{
		fprintf(output, "eroare alocare hash\n");
		return NULL;
	}
	h->v = (TLG*)calloc(M, sizeof(TLG));
	if (!h->v)
	{
		fprintf(output, "eroare alocare vector de pointeri TLG in hash\n");
		free(h);
		return NULL;
	}
	h->M = M;
	h->fh = fh;
	return h;
}

void DistrTH(TH** ah, TF fe)
{
	TLG*p, el, aux;

	//am folosit parcurgere cu pointeri ca sa o aveti si pe aceasta
	for (p = (*ah)->v; p<(*ah)->v + (*ah)->M; p++)
	{
		//daca exista elemente corespunzatoare acestui hash
		//eliberam info din celula si apoi eliberam celula
		for (el = *p; el != NULL;)
		{
			aux = el;
			el = el->urm;
			fe(aux->info);
			free(aux);
		}
	}
	free((*ah)->v);
	free(*ah);
	*ah = NULL;
}

void AfiTH(TH*ah, TF afiEl)
{
	TLG*p, el;
	for (p = ah->v; p<ah->v + ah->M; p++)
	{
		if (*p)
		{
			fprintf(output, "%ld:", p - ah->v);
			for (el = *p; el != NULL; el = el->urm)
			{
				fprintf(output, " ");
				afiEl(el->info);
			}
			fprintf(output, "\n");
		}
	}

}

void AfiTHIndex(TH*ah, TF afiEl, int index)
{
	TLG*p = ah->v + index, el;
	if (*p)
	{
		fprintf(output, "%ld:", p - ah->v);
		for (el = *p; el != NULL; el = el->urm)
		{
			fprintf(output, " ");
			afiEl(el->info);
		}
		fprintf(output, "\n");
	}
	else
	{
		fprintf(output, "%d: VIDA\n", index);
	}
}

//daca elementul exista intoarcem 0
//altfel incercam sa-l inseram si intoarcem rezultatul inserarii
int InsTH(TH*a, void*ae, size_t d, TFCmp f, TFCmp fFreqCmp, TF free_elem)
{
	int cod = a->fh(ae), rez;
	TLG el;

	for (el = a->v[cod]; el != NULL; el = el->urm)
	{
		if (!f(el->info, ae))
			return 0;
	}
	if (LungimeLG(&a->v[cod]) >= a->M)
		DistrugeLG(&a->v[cod], a->M - 1, free_elem);
	rez = InsLG(a->v + cod, ae, d, f, fFreqCmp); //reminder: a->v+cod <=> &a->v[cod]
	return rez;
}



