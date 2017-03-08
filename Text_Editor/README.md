Text Editor
=========
Task1
-----
Să dă un text format din mai multe linii, ce poate conţine literele mici şi mari ale alfabetului englez, cifre, spațiu, ghilimele simple/duble și caracterele “,” , “!”, “?”. Textul este format din cuvinte, un cuvânt este format din litere și cifre (delimitat la capete de restul de caractere). De exemplu “tr3i doi”unu!” este un text cu 3 cuvinte: “tr3i” , “doi”, “ unu”. Pe acest text se cere să se efectueze următoarele operații:

1. Se dă un cuvânt X, să se determine de câte ori apare X în text;
 2. Se dau două cuvinte X şi Y, să se înlocuiască fiecare apariţie a cuvântului X cu Y. Se va afişa la stdout noul text;
3. Se dă un număr natural strict pozitiv K, să se permute circular fiecare cuvânt din text cu K poziţii la dreapta. De exemplu pentru cuvântul “abcd”, K = 1 avem “dabc”, k = 2 avem “cdab”, k = 5 avem “dabc”. Să va afişa la stdout noul text.

Se citeşte un număr natural N ce reprezintă numărul de linii ale textului. Urmează N linii ce descriu textul asupra căruia să se efectueze operaţiile. În continuare se citește un număr natural M ce reprezintă numărul de operaţii, urmat de M linii, fiecare operaţie pe câte o linie.

**Input**
*Example*
```
3
Ana are mere?
Da, are 7 mere
Si “23” “pere”
3
1 are
2 mere portocale
3 1
```
**Output**
```
2
Ana are portocale?
Da, are 7 portocale
Si “23” “pere”
aAn ear eportocal?
aD, ear 7 eportocal
iS “32” “eper”
```
**Detalii implementare:**

Pentru acest Task folosesc 7 funcții pentru a scădea gradul de dificultate și pentru o coerență mai bună a codului.
  1. Funcția _citireText_ primește ca parametri numărul de linii `N` al textului și metoda de citire a textului. Am folosit aceasta funcție pentru a putea citi un text format din vector de linii.
  2. Funcția _afisareText_ primește ca parametri textul și numărul de linii `N`, și o folosesc pentru a-mi afișa textul.
  3. Folosesc funcția _eliberareMemorie_ pentru a elibera memoria alocată pentru fiecare linie apoi pentru intreg textul , atât pentru vectorul `text` cât și pentru vectorul `operatii`.
 4. Funcția _replaceString_ inlocuiește in text `string1` cu `string`.
În această funcție folosesc mai mulți vectori temporari_(buffer, tmp)de tip(char*)_ pe care fac operații pe parcursul funcției.
Aloc memorie tuturor vectorilor , apoi prin parcurgerea fiecarei lini adaug in vectorul `tmp` fiecare cuvânt din text.
Dacă cuvantul `string1`  nu se gasește pe o linie din text nu fac nicio midificare și trec la linia următoare.
Cât timp se găsește `string1` in `tmp` verific dacă este cuvânt valid (dacă nu are litere sau cifre înainte sau după adică sirul este inclus în alt cuvânt). Dacă cuvântul este valid il înlocuiesc cu `string2`.
5. Funcția _countOccurences_ primește ca parametri`text`_(char**)_, `N`(numărul de linii), `word`_(char*)_. Această funcție numără aparițiile cuvântului `word` în text.
6. Funcția _shiftCuvant_ face shiftarea la dreapta cu `k` poziții pentru un cuvânt. Funcția primește ca parametri `cuvant` și `k`_(int)_ , în această funcție am folosit 2 substringuri pentru fiecare cuvânt în care am salvat ultima parte , adică cea care vine mutată cu k poziții , și în celălalt restul stringului `cuvant` și apoi am făcut concatenare.

Folosind funcția _shiftCuvânt_ cu funcția _shiftText_ parcurgem toate liniile facem shiftare pentru fiecare cuvânt de pe linie.
Și cât timp avem un cuvânt valid (are delimitator în stânga și în dreapta sa  și nu orice alt caracter care nu este delimitator) facem shiftare pe acel cuvânt.
In main , am apelat funcția de _citiretext_ pentru `text` și `operatii` apoi parcurg cu un _for_ toate liniile de la operații , și verific ce operație am de făcut pe text: 1, 2 sau 3. Eliberarea de memorie este realizată prin apelarea funcției _eliberareMemorie_.

Task2
-----
Se dau 2 texte formate din N respectiv M linii. Textele se citesc astfel: un număr natural N, urmat de N linii ce reprezintă primul text, după care un număr natural M, urmat de M linii ce descriu al doilea text. Să se determine gradul de similitudine dintre cele 2 texte. Gradul de similitudine dintre 2 texte se determină după următorul algoritm:

pentru fiecare text se determină cuvintele distincte din el şi se sortează descrescător cuvintele după numărul de apariţii, iar in caz de egalitate crescător după cuvânt. Se obţin două liste de cuvinte, prima ce conţine NR1 cuvinte, a doua conţine NR2 cuvinte. Pe noi ne interesează primele NR=minNR1, NR2 cuvinte.
se determină gradul de similitudine după următoarea formulă:
```
sim(text1,text2)=100∗|NR1–NR2|+∑i=0NR−1(count(list1[i])+count(list2[i]))∗dist(list1[i],list2[i])
```
Prin count(word) se înţelege numărul de apariţii ale cuvantului “word”.

Distanţa dist dintre 2 cuvinte este suma modulelor diferențelor codurilor ASCII ale caracterelor de pe poziții identice dintre cele 2 cuvinte. De exemplu dist (“ana”, “bun” ) = abs(‘a’ – ‘b’) + abs (‘n’ – ‘u’) + abs(‘a’ – ‘ n’) = 1 + 7 + 13 = 21. Dacă lungimea celor 2 cuvinte nu este aceeaşi atunci cuvântul mai scurt se completează cu caracterul null (codul ASCII 0). Spre exemplu dist(“4e”, “aeV”) = abs(‘4’ – ‘a’) + abs(‘e’ – ‘e’) + abs(‘\0’ – ‘V’) = 45 + 0 + 86 = 131.

**Input**
*Example*
```
1
unu!unu?doi 3
2
unu doi
doi
```
**Output**
```
806
```
**Detalii implementare:**
Pentru acest task folosesc 5 funcții.
1. Funcția _citireText_ primește ca parametri numărul de linii `N` al textului și metoda de citire a textului . Am folosit această funcție pentru a putea citi un text format din vector de linii.
Folosesc această funcție pentru a citi ambele texte.
2. Funcția _dist_ primește ca parametri 2 șiruri  , și distanta dintre cele 2 șiruri. Aflu care este șirul minim și cel maxim (in funcție de lungime). Parcurg șirul `sirMin` și adaug la distanta modulul diferențelor a fiecărui caracter din șiruri in format ASCII. Parcurg șirul `sirMax` începând de la cel `sirMin` și adaug  la distanță  diferența dintre carcterul din sirMax si `\0`.
3. Funcția _creareLista_ primește ca parametru un `text` _(char **)_, numărul de linii, `nr` de linii al listei și numărul de apariții al fiecărui cuvânt în text. Parcurgem fiecare linie din text și verificăm dacă avem cuvânt valid. Copiez într-un vector temporar fiecare cuvânt valid al rândului din text și scap de toți separatorii, apoi parcurg toată lista și verific dacă un cuvânt a mai apărut în text , apoi cresc `nrAparitii`.
Dacă nu a mai apărut în text  îi aloc memorie nouă unui rând în listă și îl copiez în zona nouă de memorie.
4. Funcția de sortare primește ca parametri `list`_(char**)_, `N` numărul de linii și `nrAparitii`. Sortarea o fac prin metoda _select sort_ dacă numărul de apariții al unui cuvant este mai mare decât următorul, rămâne așa lista, dacă nu fac interschimbarea și pentru numărul de apariții cât și pentru cuvânt. Tratez și cazul în care `nrAparitii` sunt egale și fac ordonarea crescător lexicografic.
5.  Cu funcția _gradSim_ calculez gradul de similitudine dintre cele 2 liste create de mine pe baza textelor din input. Funcția returneaza un întreg.
