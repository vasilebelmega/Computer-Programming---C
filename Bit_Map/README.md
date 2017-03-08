Bit Map
=========
Avem o matrice cu dimensiunea 8 x 8 codificată sub forma unui număr pe 64 de biți.
În matrice avem elemente codificate cu bit-ul 1 și celule libere, codificate cu bit-ul 0.

Dacă un element este mutat într-o celulă în care se află alt element, vor disparea ambele elemente. Mutările făcute sunt codificate sub forma unui număr pe 12 biți, astfel:
1. Primii 6 biti reprezintă poziția în care elementul va fi schimbat în matrice: primii 3 biți reprezintă linia, iar următorii 3 biți reprezintă coloana.
2. Ultimii 6 biți reprezintă poziția curentă a elementului în matrice: primii 3 biți reprezintă linia, iar următorii 3 biți reprezintă coloana.

**Input**

Pe prima linie se va găsi un număr pe 64 de biți reprezentând configurația inițială a matricei. Pe următoarea linie se va afla un număr N reprezentând numărul de mutări. Pe următoarele N linii se vor afla numere întregi reprezentând codificările mutărilor.
```
ConfigurațieMatrice
N
mutare1
mutare2
.
.
.
mutareN
```
**Output**

Configurația finală a matricei după ce au fost aplicate cele N mutări. Aceasta este tot un număr pe 64 de biți.
```
ConfigurațieFinală
```
**Detalii implementare:**

Acest task este rezolvat în cea mai mare parte prin operațiile pe biți.
În acest task am folosit o singură funcție _bitPosition_ care ne poziționeaza pe bitul care ne interesează într-un număr în baza 2 pe 64 biți.

 Programul primește ca date de intrare 2 valori , pe prima linie _ConfiguratieMatrice_ initială și pe a doua linie numărul de mutări.
Pentru rezolvarea programului , in main folosim un singur _for_ care citeste toate mutările , le codifică și face mutările respective.

Codificarea mutărilor am realizat-o prin prin operatorul _&_ . Pentru fiecare codificare a perechilor de 3 biți am shiftat după fiecare pas cu 3 biți.
 Dupa ne poziționam pe _bitul Final_ și cel _Initial_ folosind funcția _bitPosition_.
 
Următorul pas este de a verifica dacă pe poziția inițială avem un element (adică 1) și dacă poziția inițială și cea finală sunt aceleași. Dacă aceste condiți sunt adevărate folosim _continue_.
  Pe _else_ următorul pas este de a dezactiva bitul de pe poziția inițiala apoi de a pune 1 pe poziția finală dacă pe _bitFinal_ este _0_ , daca este _1_, il facem _0_.
  Afișarea se face pe ecran  pentru configurația finală in zecimal. 

