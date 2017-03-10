Network Switches
=========
Vom caracteriza simplist un switch prin:
1. Id - un număr natural
2. Denumire - denumirea switch-ului(șir de caractere alocat dinamic)
3. Adresa IPv4 - un număr pe 32 biți (4 octeți, separați de punct). Ex: 192.168.13.10
4. Mod de funcționare - 2 moduri: mod stivă, mod individual

Pentru a putea fi administrate mai usor, switch-urile se pot grupa în stive. Fiecare stivă
are un singur switch principal. Administrarea switch-urilor se poate face individual sau prin
intermediul switch-ului principal al stivei. Astfel configurarea unui switch se poate realiza prin 
conectarea administratorului de rețea la switch-ul principal din stivă sau prin conectarea directă
la switch-ul ce va fi configurat.

Switch-ul principal dintr-o stivă va fi mereu localizat la baza acesteia, iar restul switch-urilor vor
fi aranjate după id. Astfel switch-ul cu id-ul cel mai mare se va afla mai aproape de baza stivei.
Switch-urile care nu lucrează în modulul stivă vor fi ținute intr-o coadă sortate crescator după IPv4.


**Descrierea operațiilor și a datelor de intrare:**

Pe prima linie a fișierului de intrare se va afla numărul de stive din rețea.
Pe următoarele linii se găsesc operațiile care pot fi aplicate asupra switch-urilor.
Se va citi codul comenzii, iar în funcție de acesta se citește descrierea comenzii ca mai jos.

**add [id] [denumire] [IP] [funcționare] [id_stiva] [principal]**
- Modul de funcționare poate avea valorile:
-SINGLE -> functionează individual
-STACK -> functionează in stivă
- Un switch poate fi principal sau secundar, în funcție de valorile argumentului principal:
-NON_BASE -> switch secundar
-BASE -> switch principal
**Observații:**
1. Dacă switch-ul care va fi adaugat funcționeaza în mod stiva și este switch principal, atunci
switch-ul care este principal înaintea inserării acestuia nu va mai fi principal.
2. Dacă un switch este inserat într-o stivă goală, atunci el va deveni switch principal. 

**del id**
-Switch-ul va fi scos din rețea doar dacă acesta există 

**set [id] [functionare] [id_stiva] [principal]**
1. Dacă _$functionare = modul curent de funcționare_ al switchului atunci nu se
efectuează nicio schimbare.
2. Dacă switch-ul principal este scos din stivă, locul lui este luat de switch-ul cu id-ul cel mai mare din acea stivă.
3. Dacă un switch este inserat în stivă ca switch principal atunci switch-ul care a fost principal până la acel moment își pierde acest rol, iar stiva trebuie refăcută (reordonată). 

**ipmin**
1. Dacă toate switchurile lucrează în mod stivă atunci se va afișa 0.
Ex: În loc de adresa 192.168.1.13 va fi afișat numărul 3232235789 

**show**
1. Se vor afișa pe o linie id-urile switch-urilor din coadă. Stivele se vor afișa în ordinea id-urilor.
Switch-urile se vor afișa de la varful stivei la bază, fiecare pe câte o linie astfel: 
```
    id IPv4 denumire
```

 





