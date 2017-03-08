Palindorom
=========
Câte palindroame mai mici decât X se pot scrie ca produs de 2 numere diferite de P cifre?

Un palindrom este un număr care se citește la fel și de la stânga la dreapta și de la dreapta la stânga; exemple: 1, 11, 111, 121, 2222, 2442.

**Input**

Pe prima linie se vor găsi numerele P și X.
```
P X
```
**Output**

Numărul de numere mai mici ca X care sunt palindroame și se pot scrie ca produs de 2 numere de P cifre.

**Detalii implementare:**

   În acest task am folosit mai multe funcții pentru o rulare mai eficientă a programului.
Am folosit următoarele funcții: 
1.	Funcția palindorm – primește un singur parametru și verifică dacă un număr este palindrom și returneaza 1 pentru adevarăt și 0 pentru fals.
2.	Funcția nrCifre – primește un singur parametru și returnează numărul de cifre al unui număr printr-un contor care este mărit  
```
       cât timp a != 0 
       execută a / = 10.
```

3.	Funcția produsPalindrom – primește 2 parametri și  verifică dacă termenii produsului sunt egali cu P citit de la tastaură , termenii produsului i aflam prin căutarea divizorilor al primului parametru și al câtului rezultat. În această funcție verificăm și cazul când divizorul este egal cu câtul și atunci ieșim din buclă , cautând in continuare următori termini.
 In main citim  de la tastatura 2 valori pentru variabilele P si X . Apoi printr-o parcurgere  a tuturor numerelor mai mici decât X găsim numarul total de valori care indeplinesc condiția de mai jos și afisăm numărul găsit.
```
      if(palindrom(i) && produsPalindrom(i, p)) 
```
