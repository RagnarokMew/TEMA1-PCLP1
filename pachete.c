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

void removeReverse(char* string); // Cerinta 1.5 #!NOTE: tested should work remove when done

void calculateCode(pachet* p); // Cerinta 1.5

// #!WARN: nush cum ar trb sa functioneze asta, modifica doar pachetele sale, toate pachetele etc
void postasDoBad(postas* p); // Cerinta 2.6

void alterCodes(int* code, int idPostas); // Cerinta 2.6

int isPrime(int n); // Helper function, verf daca nr este prim 

//#!WARN: nush cum ar trb sa implementez asta tbh, like cred ca ar trb sa trimit si toate
double calculateScore(postas p); // Cerinta 2.7

// Outputuri Task 

void outputTask1(int nrC, cartier* cartiere, int nrP, pachet* pachete);

void outputTask2(int nrP, pachet* pachete);

void outputTask3();

void outputTask4();

void outputTask5();

void outputTask6();

void outputTask7();

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

  distributePackage(nrC, &postasi, nrP, pachete);//!WARN: Nush daca asta trb aici dar pun sa nu plang dupa;

  //selectarea cerintei / taskului
  switch(task) {
    case 1:
      //!TODO
      outputTask1(nrC, cartiere, nrP, pachete);
      break;
    case 2:
      //!TODO
      break;
    case 3:
      //!TODO
      break;
    case 4:
      //!TODO
      break;
    case 5:
      //!TODO
      break;
    case 6:
      //!TODO
      break;
    case 7:
      //!TODO
      break;
    default:
      printf("No such task.");
      break;
  }

  freeAll(nrC, nrP, cartiere, pachete, postasi);
  return 0;
}

// Cerinta 1.1: citeste datele de intrare
void readInput(int* nrC, int* nrP, cartier** cartiere, pachet** pachete) { //#!WARN TODO: FIX SEGFAULT when reading;
  // Citire cartiere
  scanf("%d\n", nrC);
  *cartiere = (cartier*)malloc(*nrC * sizeof(cartier));
  for(int i = 0; i < *nrC; i++) {
    (*cartiere)[i].id = i;
    char buff[1024];
    scanf("%s\n", buff);
    (*cartiere)[i].nume = (char*)malloc(strlen(buff) + 1);
    strcpy((*cartiere)[i].nume, buff);
  }

  //Citire pachete
  scanf("%d\n", nrP);
  *pachete = (pachet*)malloc(*nrP * sizeof(pachet));
  for(int i = 0; i < *nrP; i++) {
    (*pachete)[i].id = i;
    for(int j = 0; j < 18; j++)
      scanf("%d", &(*pachete)[i].adresa[j]);
    scanf("\n%d\n", &(*pachete)[i].prioritate);
    scanf("%f\n", &(*pachete)[i].greutate);
    char buff[101];
    fgets(buff, 100, stdin);
    buff[strlen(buff) - 1]= '\0'; //#!WARN: This might actually not be good because msg might need to have endl
    (*pachete)[i].mesaj = (char*)malloc(strlen(buff) + 1);
    strcpy((*pachete)[i].mesaj, buff);

    //seteaza defaultul pt valori pt a putea fi modificate
    (*pachete)[i].strada = 0;
    (*pachete)[i].idCartier = 0;
    (*pachete)[i].numar = 0;
    (*pachete)[i].codificareMesaj = 0;
    processAddress(&(*pachete)[i]);
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
  *postasi = (postas*)malloc(nrC * sizeof(postas));
  for(int i = 0; i < nrC; i++) {
    (*postasi)[i].id = i;
    (*postasi)[i].nrPachete = 0;
  }
  
  // Distribuieste pachete
  for(int i = 0; i < nrP; i++) {
    (*postasi)[pachete[i].idCartier].distribuite[(*postasi)[pachete[i].idCartier].nrPachete] = pachete[i].id;
    (*postasi)[pachete[i].strada].nrPachete++;
  }
}

// Functie de conditie: 1: ordonate corect; -1: ordonate incorect; 0: valori egale 
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

void sortPackages(pachet* pachete, int nrP, int (*cmp)(pachet,pachet)) {
  // bubblesort bc quick and dirty
  for(int i = 0; i < nrP - 1; i++)
    for(int j = 0; j < nrP - i - 1; j++)
      if((*cmp)(pachete[i], pachete[j])<0) {
        pachet aux = pachete[i];
        pachete[i] = pachete[j];
        pachete[j] = aux;
      }
}

void removeReverse(char* string) {
  const char punctuation[] = ".,!?: ";
  char* cpy = (char*)malloc(strlen(string) + 1);
  strcpy(cpy, "");
  char* token = strtok(string, punctuation);
  while(token != NULL)
  {
    strcpy(cpy + strlen(token), cpy);
    strncpy(cpy, token, strlen(token));
    token = strtok(NULL, punctuation);
  }
  strcpy(string,cpy);
  free(cpy);
} 

void calculateCode(pachet* p) {
  for(int i = 0; i < strlen(p->mesaj); i++)
    p->codificareMesaj += i + p->mesaj[i];

  p->codificareMesaj %= (p->numar + p->strada + 1);
}

// #!WARN: nush cum ar trb sa functioneze asta, modifica doar pachetele sale, toate pachetele etc
void postasDoBad(postas* p); //Cerinta 2.6

void alterCodes(int* code, int idPostas) {
  int prime_factors[11];
  int num = 0;

  //edgecases, apoi skip la alterarea codurilor
  if(idPostas == 0 || idPostas == 1)
  {
    prime_factors[0] = idPostas;
    num = 1;
    goto startalter;
  }
  
  //gasirea factorilor
  for(int i = 2; i <= sqrt(idPostas) && i < 32; i++)
    if(idPostas % i == 0 && isPrime(i))
      prime_factors[num++] = i;

  startalter:
    for(int i = 0; i < num; i++)
      *code ^= (1<<prime_factors[i]); // negarea bitului de pe poz; 1^1 = 0; 0^1 = 1; 1^0 = 1; 0^0 = 0;
  return;
}

int isPrime(int n) {
  if(n == 0 || n == 1 || (n != 2 && (n & 1) == 1) ) //cond pt care un nr nu e prim + verf imp cu bitwise 1 bc I can 
    return 0;

  for(int i = 2; i <= sqrt(n); i++)
    if(n % i == 0)
      return 0;
  return 1;
}

//#!TODO implement the function
double calculateScore(postas p) {
  if(p.nrPachete == 0)
    return 0;
  
  int correct_dist = 0;

  //#!NOTE: Implementation goes here
  return 1.* correct_dist / p.nrPachete;
}

void outputTask2(int nrP, pachet* pachete) {
  for(int i = 0; i < nrP; i++) {
    printf("%d\n", pachete[i].id);
    printf("%d %d %d\n", pachete[i].idCartier, pachete[i].strada, pachete[i].numar);
  }
}

void outputTask3();

void outputTask4();

void outputTask5();

void outputTask6();

void outputTask7();
