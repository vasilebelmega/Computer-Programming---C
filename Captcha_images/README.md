Captcha Images
=========
Toate taskurile vor procesa o singură imagine. Numele acesteia o să fie citit de pe prima linie din fișierul de intrare. Scopul fiecărui task este crearea unui nou fișier (binar pentru taskurile 1 si 3 si text pentru taskul 2)

Task1
-----
Schimbarea culorii tuturor cifrelor din imagine. Pe langă imaginea cu care o să lucrezi la cele 3 taskuri o sa mai primești 3 numere întregi între 0 si 255 (în formatul BGR) reprezentând noua culoare dorită a cifrelor. Rezolvarea corecta a taskului presupune existența unei imagini noi cu aceleasi cifre, dar colorate dupa regula data.

**Observație**
Cu excepția matricei de pixeli, toate celelalte valori din imaginea inițială (valorile câmpurilor din headere) trebuie sa ramana neschimbate.

**Detalii implementare:**

Pentru rezolvarea acestor taskuri am folosit o matrice de pixeli (care reprezintă imaginea) de înaltimea _height_ și lungimea _width_ , pentru orice modificare pe imagine am folosit această matrice. Am folosit o structura _pixel_ care conține 3 valori _unsigned char_,  aceste valori reprezintă codurile pentru culoarea unui pixel.

Funcția _LoadBitmapFile_ îmi citește matricea de pixeli pentru a putea face modificările.
Rezolvările task-ului 1 constă în înlocuirea tuturor pixelilor de culoare diferită de cea albă  cu culoarea dată ca parametru de intrare.


Task2
-----
Recunoașterea numerelor din imaginea captcha. Numărul format va avea cifrele ordonate de la stânga la dreapta.

**Observatii:**
1. Cifrele pot începe oriunde în imagine (atâta timp cât nu depășesc dimensiunea imaginii).
2. Cifrele nu se vor intersecta și oricare două cifre vor fi separate de cel puțin o linie sau o coloana.
3. Nu vor exista 2 cifre care să înceapă pe aceeași coloană, putând astfel să punem  pentru oricare 2 cifre care se afla la stânga celeilalte;
4. Pentru simplitate, putem considera că fiecare cifră reprezintă un pătrat de pixeli de dimensiune 5 * 5. Deci, nu va aparea următorul caz in fișierele de test:
```
    XXXXX...X.  
    X...X...X.  
    X...X...X.  
    X...X...X.  
    XXXXX...X. 
```
5. Testul de mai sus nu e valid din cauza cifrei unu. Aceasta trebuie reprezentată ca o matrice de 5 * 5 pixeli în care primele 4 coloane să fie albe (lucru care nu se întâmplă).

**Detalii implementare:**
Pentru rezolvarea taskului 2 am folosit următoarele funcții:
1. Funcția _determinaCifra1_ returnează 1 dacă se gasește cifra 1 în matricea de pixeli la poziția dată ca parametru(din poziția stânga sus ) și -1 altfel. Am creat această funcție deoarece cifra 1 are nevoie de teste speciale fiind singura cifra pentru care pixelul din stanga sus este alb.
Pentru determinarea celorlalte cifre folosim funcția _determinaCifra_ și parcurgem matricea coloană cu coloană, iar la întâlnirea unui pixel diferit de alb verificăm dacă se poate reprezenta o cifra cu acest pixel fiind în colțul din stânga sus, altfel returnează -1.
2.În funcția _determinaCifre_ parcurgem matricea, și afișam cifra folosind funcțiile de mai sus.

Task3
-----
 Doresc să fac o statistică a cifrelor care apar și să văd cum ar arată captcha-urile fără anumite cifre. O să primesc o listă de cifre pe care va trebui să le elimin. După eliminarea unei cifre toate celelalte cifre ce se află la dreapta ei vor fi mutate spre stânga în felul urmator:
 * prima cifră de după o cifră eliminată va lua locul cifrei eliminate;
* următoarea cifră va lua locul cifrei recent mutate;
* se va repeta pasul 2 până nu mai rămân cifre;

**Observatie:**
Dimensiunea imaginii precum și celelalte câmpuri din headerele imaginii originale vor rămâne neschimbate și în cadrul acestui task.

**Detalii implementare:**
Pentru rezolvarea task-ului 3 pe lângă funcțiile create până acum am mai folosit următoarele funcții:
- funcția _esteCifraDeEliminat_ verifică dacă o cifră dată ca parametru trebuie eliminată.
- funcția _mutaCifra_ mută o cifră din matricea de pixeli de pe poziția sa inițială pe poziția de unde s-a eliminat o cifra.
- funcția _makeWhite_ face toti pixeli unei cifre din matrice albi.
- funcția _eliminaCifre_ folosește funcțiile de mai sus si prin parcurgerea matricei de pixeli face eliminarea cifrei citită din fișierul de intrare , mutarea celorlalte cifre pe pozitiile celor șterse , și șterge și cifrele cele rămase după mutare.



