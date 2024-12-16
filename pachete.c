#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct {
  int id;
  char* nume;
} cartier;

typedef struct {
  int id;
  int adresa[18];
  int idCartier;
  int strada;
  int numar;
  int prioritate;
  float greutate;
  char* mesaj;
  int codificareMesaj;
} pachet;

typedef struct {
  int id;
  int nrPachete;
  int distribuite[50];
} postas;

void readInput(int* nrC, int* nrP, cartier** cartiere, pachet** pachete); // Cerinta 1.1

void freeAll(int nrC, int nrP, cartier* cartiere, pachet* pachete, postas* postasi); // Utility function, elibereaza memoria alocata dinamic

void processAddress(pachet* target); // Cerinta 1.2

void distributePackage(int nrC, postas** postasi, int nrP, pachet* pachete); // Cerinta 1.3

int condSortPackage(pachet a, pachet b); // Cerinta 1.4

void sortPackages(pachet* pachete, int nrP, int (*cmp)(pachet,pachet)); // Cerinta 1.4

void removeReverse(char* string); // Cerinta 1.5

int calculateCode(pachet p); // Cerinta 1.5

int getPachetPosById(int pachetId, int nrP, pachet* pachete); // Helper function

void postasDoBad(postas* postasi, int idPostas, pachet* pachete, int nrP); // Cerinta 2.6

void alterCodes(int* code, int idPostas); // Cerinta 2.6

int isPrime(int n); // Helper function, verf daca nr este prim 

double calculateScore(postas p, int nrP, pachet* pachete); // Cerinta 2.7

// Outputuri Task 

void outputTask1(int nrC, cartier* cartiere, int nrP, pachet* pachete);

void outputTask2(int nrP, pachet* pachete);

void outputTask3(int nrC, postas* postasi); // comun cu task4

void outputTask5(int nrC, postas* postasi, int nrP, pachet* pachete); // comun cu task6

void outputTask7(int nrC, postas* postasi, int nrP, pachet* pachete);

int main()
{
  //alegerea taskului selectat
  int task;
  scanf("%d\n", &task);

  //Declarare + citire input
  pachet* pachete;
  cartier* cartiere;
  postas* postasi;
  int nrP, nrC;

  readInput(&nrC, &nrP, &cartiere, &pachete);

  //selectarea cerintei / taskului
  // se apeleaza doar functiile asociate cu taskul respectiv
  switch(task) {
    case 1:
      outputTask1(nrC, cartiere, nrP, pachete);
      break;
    case 2:
      outputTask2(nrP, pachete);
      break;
    case 3:
      distributePackage(nrC, &postasi, nrP, pachete); 
      outputTask3(nrC, postasi);
      break;
    case 4:
      sortPackages(pachete, nrP, condSortPackage);
      distributePackage(nrC, &postasi, nrP, pachete); 
      outputTask3(nrC, postasi);
      break;
    case 5:
      sortPackages(pachete, nrP, condSortPackage);
      distributePackage(nrC, &postasi, nrP, pachete);
      outputTask5(nrC, postasi, nrP, pachete);
      break;
    case 6:
      sortPackages(pachete, nrP, condSortPackage);
      distributePackage(nrC, &postasi, nrP, pachete);
      for(int i = 0; i < nrC; i++)
        postasDoBad(postasi, i, pachete, nrP);
      outputTask5(nrC, postasi, nrP, pachete);
      break;
    case 7:
      sortPackages(pachete, nrP, condSortPackage);
      distributePackage(nrC, &postasi, nrP, pachete);
      for(int i = 0; i < nrC; i++)
        postasDoBad(postasi, i, pachete, nrP);
      outputTask7(nrC, postasi, nrP, pachete);
      break;
    default:
      printf("No such task.");
      break;
  }

  freeAll(nrC, nrP, cartiere, pachete, postasi);
  return 0;
}

// Cerinta 1.1: citeste datele de intrare
void readInput(int* nrC, int* nrP, cartier** cartiere, pachet** pachete) {
  // Citire cartiere
  scanf("%d\n", nrC);
  *cartiere = (cartier*)malloc(*nrC * sizeof(cartier)); // alocarea memoriei necesare pt cartiere
  for(int i = 0; i < *nrC; i++) {
    (*cartiere)[i].id = i;
    char buff[1024];
    scanf("%s\n", buff);
    (*cartiere)[i].nume = (char*)malloc(strlen(buff) + 1); // alocarea memoriei necesare pt sirurile de caractere (conform cerintei)
    strcpy((*cartiere)[i].nume, buff);
  }

  //Citire pachete
  scanf("%d\n", nrP);
  *pachete = (pachet*)malloc(*nrP * sizeof(pachet)); // alocarea memoriei necesare pt pachete
  for(int i = 0; i < *nrP; i++) {
    (*pachete)[i].id = i;
    for(int j = 0; j < 18; j++)
      scanf("%d", &(*pachete)[i].adresa[j]);
    scanf("\n%d\n", &(*pachete)[i].prioritate);
    scanf("%f\n", &(*pachete)[i].greutate);
    char buff[101];
    fgets(buff, 100, stdin);
    buff[strlen(buff) - 1]= '\0'; // sterge newline din mesaj, deoarece nu este necesar, afisarea se face cu \n, iar in removeReverse() se sterge oricum
    (*pachete)[i].mesaj = (char*)malloc(strlen(buff) + 1); // alocarea memoriei necesare pt sirurile de caractere (conform cerintei)
    strcpy((*pachete)[i].mesaj, buff);

    //seteaza defaultul pt valori pt a putea fi modificate
    (*pachete)[i].strada = 0;
    (*pachete)[i].idCartier = 0;
    (*pachete)[i].numar = 0;
    (*pachete)[i].codificareMesaj = 0;
    processAddress(&(*pachete)[i]); // alocarea strazii, nr si id cartier in functie de bitii din adresa
  }
}

// Elibereaza memoria alocata dinamic structurilor
void freeAll(int nrC, int nrP, cartier* cartiere, pachet* pachete, postas* postasi) {
  for(int i = 0; i < nrC; i++)
    free(cartiere[i].nume);
  free(cartiere);
  free(postasi);

  for(int i = 0; i < nrP; i++)
    free(pachete[i].mesaj);
  free(pachete);
}

void outputTask1(int nrC, cartier* cartiere, int nrP, pachet* pachete) {
  for(int i = 0; i < nrC; i++)
    printf("%d %s\n", cartiere[i].id, cartiere[i].nume);

  for(int i = 0; i < nrP; i++) {
    printf("%d\n", pachete[i].id);
    for(int j = 0; j < 17; j++)
      printf("%d ", pachete[i].adresa[j]);
    printf("%d\n", pachete[i].adresa[17]);
    printf("%d %.3f\n", pachete[i].prioritate, pachete[i].greutate);
    printf("%s\n", pachete[i].mesaj);
  }
}

// extrage din adresa, valorile 2^i * adresa[i] ({0,1})
void processAddress(pachet* target) {
  // extract idCartier
  int pow = 1;
  for(int i = 4; i >= 0; i--) {
    target->idCartier += pow * target->adresa[i];
    pow *= 2;
  }

  // extract strada
  pow = 1;
  for(int i = 9; i >= 5; i--) {
    target->strada += pow * target->adresa[i];
    pow *= 2;
  }

  // extract numar
  pow = 1;
  for(int i = 17; i >= 10; i--) {
    target->numar += pow * target->adresa[i];
    pow *= 2;
  }
}

void distributePackage(int nrC, postas** postasi, int nrP, pachet* pachete) {
  // Initializeaza postasi
  *postasi = (postas*)malloc(nrC * sizeof(postas)); // alocarea memoriei pentru postasi
  for(int i = 0; i < nrC; i++) {
    (*postasi)[i].id = i;
    (*postasi)[i].nrPachete = 0;
  }
  
  // Distribuieste pachete
  for(int i = 0; i < nrP; i++) {
    (*postasi)[pachete[i].idCartier].distribuite[(*postasi)[pachete[i].idCartier].nrPachete] = pachete[i].id;
    (*postasi)[pachete[i].idCartier].nrPachete++;
    removeReverse(pachete[i].mesaj);
    pachete[i].codificareMesaj = calculateCode(pachete[i]);
  }

}

// Functie de conditie sortare: 1: ordonate corect; -1: ordonate incorect; 0: valori egale, in functie de cerinta
int condSortPackage(pachet a, pachet b) {
  if(a.prioritate < b.prioritate)
    return -1;
  if(a.prioritate > b.prioritate)
    return 1;
  if(a.greutate < b.greutate)
    return -1;
  if(a.greutate > b.greutate)
    return 1;
  return 0;
}

// Bubble sort, pt ca e easy de scris (quick and dirty)
void sortPackages(pachet* pachete, int nrP, int (*cmp)(pachet, pachet)) {
  char sorted = 0;
  for(int i = 0; i < nrP - 1 && !sorted; i++) {
    sorted = 1;
    for(int j = 0; j < nrP - i - 1; j++)
      if((*cmp)(pachete[j], pachete[j+1])<0) {
        pachet aux = pachete[j+1];
        pachete[j+1] = pachete[j];
        pachete[j] = aux;
        sorted = 0;
      }
  }
}

// sterge semnele de punctuatie din string si inverseaza cuvintele
// se utilizeaza strtok pe string, si se copiaza intr-o fiecare cuvant
// la fiecare iteratie continutul copiei este mutat la dreapta cu lungimea cuvantului pentru inversare
void removeReverse(char* string) {
  const char punctuation[] = ".,!?: ";
  char* cpy = (char*)malloc(strlen(string) + 1); // alocare spatiu copie
  strcpy(cpy, "");
  char* token = strtok(string, punctuation);
  while(token != NULL)
  {
    strcpy(cpy + strlen(token), cpy); // offset in copie
    strncpy(cpy, token, strlen(token)); // adaugare cuvant in copie
    token = strtok(NULL, punctuation);
  }
  strcpy(string,cpy); // copiere continut final in string
  free(cpy); // eliberare memorie alocata dinamic
} 

// calcularea codificarii mesaj conform cerintei
int calculateCode(pachet p) {
  int code = 0;
  for(int i = 0; i < strlen(p.mesaj); i++)
    code += i * p.mesaj[i];

  code %= (p.numar * p.strada + 1);
  return code;
}

// helper function pentru a obtine indexul unui pachet in array pentru a-l gasi dupa sortare
int getPachetPosById(int pachetId, int nrP, pachet* pachete) {
  for(int i = 0; i < nrP; i++)
    if(pachetId == pachete[i].id)
      return i;

  return 0;
}

// altereaza codificarea mesajului pachetelor corespunzatoare pe care le distribuie postasul
void postasDoBad(postas* postasi, int idPostas, pachet* pachete, int nrP) {
  char sIdPostas[11];
  char sCodPachet[11];
  sprintf(sIdPostas, "%d", idPostas); // convertire in char array pt convenience
  for(int i = 0; i < postasi[idPostas].nrPachete; i++) {
    int pachetIndex = getPachetPosById(postasi[idPostas].distribuite[i], nrP, pachete);
    sprintf(sCodPachet, "%d", pachete[pachetIndex].codificareMesaj); // convertire in char array pt convenience
    // selectarea pachetelor care respecta conditia de modificare a codificarii
    for(int j = 0; j < strlen(sCodPachet); j++)
      if(strchr(sIdPostas, sCodPachet[j])) {
        alterCodes(&pachete[pachetIndex].codificareMesaj, idPostas);
        break;
      }
  }
}

// algoritmul de alterare a codificarii
void alterCodes(int* code, int idPostas) {
  int primeFactors[11];
  int num = 0;

  // edge-cases din cerinta
  if(idPostas == 0 || idPostas == 1)
  {
    primeFactors[0] = idPostas;
    num = 1;
  }
  
  //gasirea factorilor primi din id postas
  for(int i = 2; i <= idPostas && i < 32; i++)
    if(idPostas % i == 0 && isPrime(i))
      primeFactors[num++] = i;

  for(int i = 0; i < num; i++)
    *code ^= (1<<primeFactors[i]); // negarea bitului de pe poz (prime_facotrs); 1^1 = 0; 0^1 = 1; 1^0 = 1; 0^0 = 0;
  return;
}

// helper function pt verf daca un nr este prim
int isPrime(int n) {
  if(n == 0 || n == 1) 
    return 0;

  for(int i = 2; i <= sqrt(n); i++)
    if(n % i == 0)
      return 0;
  return 1;
}

// functie calculeaza scorul unui postas
double calculateScore(postas p, int nrP, pachet* pachete) {
  if(p.nrPachete == 0)
    return 0;
  
  int correctDist = 0;

  int pachetIndex;
  for(int i = 0; i < p.nrPachete; i++) {
    pachetIndex = getPachetPosById(p.distribuite[i], nrP, pachete);
    if(pachete[pachetIndex].codificareMesaj == calculateCode(pachete[pachetIndex])) // verifica daca codul actual este cel corect
      correctDist++;
  }

  return 1.* correctDist / p.nrPachete;
}

void outputTask2(int nrP, pachet* pachete) {
  for(int i = 0; i < nrP; i++) {
    printf("%d\n", pachete[i].id);
    printf("%d %d %d\n", pachete[i].idCartier, pachete[i].strada, pachete[i].numar);
  }
}

void outputTask3(int nrC, postas* postasi) {
  for(int i = 0; i < nrC; i++) {
    printf("%d %d\n", postasi[i].id, postasi[i].nrPachete);
    for(int j = 0; j < postasi[i].nrPachete - 1; j++)
      printf("%d ", postasi[i].distribuite[j]);

    if(postasi[i].nrPachete != 0)
      printf("%d\n", postasi[i].distribuite[postasi[i].nrPachete - 1]);
  }
}

void outputTask5(int nrC, postas* postasi, int nrP, pachet* pachete) {
  for(int i = 0; i < nrC; i++) {
    printf("%d %d\n", postasi[i].id, postasi[i].nrPachete);
    for(int j = 0; j < postasi[i].nrPachete; j++)
      printf("%d %d\n", postasi[i].distribuite[j], pachete[getPachetPosById(postasi[i].distribuite[j], nrP, pachete)].codificareMesaj);
  }
}

void outputTask7(int nrC, postas* postasi, int nrP, pachet* pachete) {
  for(int i = 0; i < nrC; i++)
    printf("%d %.3f\n", postasi[i].id, calculateScore(postasi[i], nrP, pachete));
}
