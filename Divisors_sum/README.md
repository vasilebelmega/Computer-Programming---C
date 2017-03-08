Suma divizorilor
===============

Considerând proprietatea:
```
SumDiv(a)=b și SumDiv(b)=a 
unde
SumDiv(X)= suma divizorilor lui X care sunt mai mici ca X
```
creaza o listă cu toate perechile de numere cu această proprietate, mai mici decât K.

**Input**
Pe prima linie se va găsi numărul K.
```
K
```
**Output**
Output-ul va fi constituit din N linii pe care se vor găsi perechile (ai,bi), ai<bi sortate în ordinea crescătoare a numărului ai, iar în caz de egalitate în ordinea crescătoare a numărului bi.
```
(a0, b0)
(a1, b1)
(a2, b2)
.
.
.
(aN, bN)
```
**Detalii implementare:**

 Pentru acest exercițiu am folosit o functie cu 2 parametri ce returnează _True_ dacă suma divizorilor primului parametru este egal cu al 2-lea parametru.
 
  In main citesc o valoare K de la tastaură apoi parcurg toate numerele de la 1 la K pentru a găsi toate perechile de numere care verifica funcția sumDiv.

  Pe ecran vor fi afisate toate perechile care respecta condiția
```
SumDiv(a)=b și SumDiv(b)=a.
```