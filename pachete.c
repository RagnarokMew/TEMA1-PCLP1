#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void freeAll(int nrC, int nrP, cartier* cartiere, pachet* pachete, postas* postasi); // Utility func

void outputCerinta1(int nrC, cartier* cartiere, int nrP, pachet* pachete); // Cerinta 1

void processAddress(pachet* target); // Cerinta 1.2

void distributePackage(int nrC, postas** postasi, int nrP, pachet* pachete); // Cerinta 1.3

int condSortPackage(pachet a, pachet b); // Cerinta 1.4

void sortPackages(pachet* pachete, int nrP, int (*cmp)(pachet,pachet)); // Cerinta 1.4

void removeReverse(char* string); // Cerinta 1.5

void calculateCode(pachet* p); // Cerinta 1.5

int main()
{
  //alegerea taskului selectat
  int task;
  scanf("%d", &task);

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
      outputCerinta1(nrC, cartiere, nrP, pachete);
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
void readInput(int* nrC, int* nrP, cartier** cartiere, pachet** pachete) {
  // Citire cartiere
  scanf("%d", nrC);
  *cartiere = (cartier*)malloc(*nrC * sizeof(cartier));
  for(int i = 0; i < *nrC; i++) {
    (*cartiere)[i].id = i;
    char buff[1024];
    scanf("%s", buff);
    (*cartiere)[i].nume = (char*)malloc(strlen(buff) + 1);
    strcpy((*cartiere)[i].nume, buff);
  }

  //Citire pachete
  scanf("%d", nrP);
  *pachete = (pachet*)malloc(*nrP * sizeof(pachet));
  for(int i = 0; i < *nrP; i++) {
    (*pachete)[i].id = i;
    for(int j = 0; j < 18; j++)
      scanf("%d", &(*pachete)[i].adresa[j]);
    scanf("%d", &(*pachete)[i].prioritate);
    scanf("%f", &(*pachete)[i].greutate);
    char buff[1024];
    fgets(buff, 1024, stdin);
    buff[strlen(buff) - 1]= '\0'; //#!WARN: This might actually not be good because msg might need to have endl
    (*pachete)[i].mesaj = (char*)malloc(strlen(buff) + 1);
    strcpy((*pachete)[i].mesaj, buff);

    //seteaza defaultul pt valori pt a putea fi modificate
    (*pachete)[i].strada = 0;
    (*pachete)[i].idCartier = 0;
    (*pachete)[i].numar = 0;
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

void outputCerinta1(int nrC, cartier* cartiere, int nrP, pachet* pachete) {
  for(int i = 0; i < nrC; i++)
    printf("%d %s\n", cartiere[i].id, cartiere[i].nume);

  for(int i = 0; i < nrP; i++) {
    printf("%d\n", pachete[i].id);
    for(int j = 0; j < 18; j++)
      printf("%d ", pachete[i].adresa[j]);
    printf("\n%.3f\n", pachete[i].greutate);
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
  for(int i = 9; i >= 5; i++) {
    target->strada += pow * target->adresa[i];
    pow *= 2;
  }

  // extract numar
  pow = 1;
  for(int i = 17; i >= 10; i++) {
    target->numar += pow * target->adresa[i];
    pow *= 2;
  }
}

void distributePackage(int nrC, postas** postasi, int nrP, pachet* pachete) {
  // Initializeaza postasi
  *postasi = (postas*)malloc(nrC * sizeof(postas));
  for(int i = 0; i < nrC; i++) {
    (*postasi)[i].id = 0;
    (*postasi)[i].nrPachete = 0;
  }
  
  // Distribuieste pachete
  for(int i = 0; i < nrP; i++) {
    (*postasi)[pachete[i].strada].distribuite[(*postasi)[pachete[i].strada].nrPachete] = pachete[i].id;
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
    strcpy(cpy, token);
    token = strtok(NULL, punctuation);
  }
} 

void calculateCode(pachet* p) {

} 
