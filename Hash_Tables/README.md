Hash Tables
=========
Pentru implementarea backend-ului unui server DNS se poate utiliza o structură de date ce se pliază foarte bine pe nevoile de mai sus. Această structură pornește de la metoda LRU
_IP=64.233.160.4_

Cache (Least Recently Used Cache) care reține în memorie doar cele mai recent folosite înregistrări. Această structură utilizează o tabelă hash.
Tabela hash este o structură de date optimizată pentru funcția de căutare. Acest lucru se
realizează transformând cheia într-o intrare în tabela hash (folosind o funcție hash). 

Funcția hash trebuie aleasă astfel încât să se minimizeze numărul coliziunilor (valori
diferite care produc aceleasi intrări în tabela hash). Coliziunile apar in mod inerent, deoarece
dimensiunea (numărul de intrări) tabelei hash este fixa, iar obiectele de stocare pot avea lungimi
și continut arbitrare.
În cazul apariției unei coliziuni, valorile se stocheaza pe aceeași poziție (în
aceeași listă). În acest caz, căutarea se va reduce la compararea valorilor efective în cadrul listei
respective. 


**Detalii implementare:**

Structura de date LRUCache va fi reprezentată pe baza unei tabele hash. Aceasta este
formată dintr-un vector cu M elemente – fiecare element fiind reprezentat printr-o listă dublu
înlanțuită circulară generică. Elementele din liste vor fi de forma (Key, Value, Frequency), unde
_Key_ și _Value_ sunt șiruri de caractere alocate dinamic, iar Frequency este o valoare întreaga ce
reprezintă numărul de accesări ale cheii _Key_. 

Funcția hash va calcula restul împarțirii sumei caracterelor ce fac parte din cheia (Key) stocată în tabela hash la numarul maxim de liste ce pot fi stocate în tabela hash (M). Fiecare listă va fi sortată descrescător în funcție de Frequency, în cazul elementelor cu aceeasi valoare pentru Frequency, elementele vor fi sortate alfabetic după _Key_. 

**Operațiile efectuate în tabela hash sunt:**
 * set <Key, Value>
* dacă Key nu există în tabela hash, aceasta va fi adaugată în lista corespunzatoare din
tabela hash având Frequency = 0; în cazul în care cheia Key există în tabela hash,
aceasta nu va mai fi inserata.
*  în cazul in care Key nu există în tabela hash:
     -dacă numărul de elemente din listă corespunzătoare în care trebuie inserat
elemental curent este mai mare sau egal decât M, se va șterge utlimul
element din listă și se va realiza inserarea;
     -dacă numărul total de elemente din tabela hash este mai mare decât M * 2 se
va realoca tabela hash la o nouă dimensiune de M * 2 intrări. În cazul în care
realocarea nu poate fi realizată, tabela hash va ramane nemodificată. 
*  get <Key >
* dacă în tabela hash există elementul cu cheia Key, atunci întoarce valoarea (Value)
corespunzătoare cheii Key, incrementează Frequency și reordonează în mod
corespunzător lista din care face parte cheia Key căutată; dacă cheia Key nu există în
tabela hash, se va întoarce NULL.
* remove <Key>, șterge elementul (Key, Value, Frequency) din tabela hash (în cazul în care aceasta există).
* print 
-afișează toate valorile (Value) din tabela hash;
-pentru fiecare listă nevida se va afica indicele acesteia si toate elementele acesteia, sub forma:
```
         i: (Valoare1) (valoare2) … (valoaren)
```
-elementele listei sunt afișate pe aceeasi linie, separate de un spațiu; indicii listelor sunt numerotați de la 0.
* print_list <index >
 -afișează valorile (Value) din listă cu indicele index, pe o singură linie; indicii listelor sunt numerotați de la 0;
-separarea elementelor afisște se face numai prin spații;
-dacă lista asociată intrării index este vidă se va afișa VIDA. 





