# TEMA1-PCLP1

Realizat de Simion Ștefan , grupa 314CC.

## Timp de Implementare

Cerinta 1: 8 ore

Cerinta 2: 2 ore

## Explicarea pe scurt a implementării

Am spart unele linii de cod si comentarii pe mai multe linii pentru a respecta
 limita de 80 de caractere impusa in cerinta.

Am ales sa scriu antetele functiilor dupa definirea structurilor. Taskul este
 selectat printr-un ```switch``` statement, unde in cadrul fiecarui ```case```
 se apeleaza functiile aferente taskului respectiv. Pt arrayurile structurilor
 am ales alocarea dinamica, iar eliberarea acestora este facuta, printr-o
 functie helper. Sortarea pachetelor am facut-o prin Bubblesort deoarece este
 foarte usor de scris si nu stiam daca este permisa utilizarea qsort. Logica
 programului este impartita in mai multe functii conform cerintei. In scrierea
 codului am ales utilizarea CamelCase si am incercat ca numele variabilelor si
 a functiilor sa fie cat mai descriptive (pachetIndex, sortPackages(), etc).

### Task 1

Am initializat si citit cartierele si pachetele si le-am afisat conform
 cerintei.

### Task 2

Am extras campurile din binar in decimal, parcurgand fiecare reprezentare
 binara de la dreapta la stanga, facand conversia si le-am afisat conform
 cerintei.

### Task 3

Distribuirea pachetelor este realizata prin parcurgerea tuturor pachetelor
 si punerea id-ului de pachet la postasul corespunzator in functie de id-ul
 cartierului. Apoi afisarea a fost facuta conform cerintei.

### Task 4

Sortarea a fost implementata cu Bubblesort, deoarece este usor de scris
 si este facuta inainte de distribuirea pachetelor. Dupa distribuire
 afisarea este conform cerintei.

### Task 5

Codul este calculat cand se face distributia pachetelor. Afisarea este
 facuta conform cerintei.

### Task 6

Alterarea codurilor se face dupa distribuirea pachetelor. Pentru identificarea
 pachetelor am convertit id-urile in stringuri si dupa aceea utilizand strchr()
 se verifica ce pachete trebuie schimbate. Verificarea de nr prim este realizata
 intr-o functie helper, iar negarea bitilor se realizeaza prin XOR cu 1. Afisarea
 este conform cerintei.

### Task 7

Dupa ce toate operatiile precedente, pentru fiecare postas se calculeaza numarul
 de pachete care nu au codul alterat prin recalcularea codului si compararea
 acestuia cu cel salvat, iar dupa ce se calculeaza scorul pentru fiecare postas
 se afiseaza outputul conform cerintei.
